# CMakeList.txt : CMake project for Karmazyn, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

MACRO(ADD_MSVC_PRECOMPILED_HEADER PrecompiledHeader PrecompiledSource SourcesVar)
  IF(MSVC)
	list(FILTER ${SourcesVar} EXCLUDE REGEX ".*${PrecompiledSource}") #avoid cyclic dependnecy (precompile with itself)

    GET_FILENAME_COMPONENT(PrecompiledBasename ${PrecompiledHeader} NAME_WE)
    SET(PrecompiledBinary "${CMAKE_CURRENT_BINARY_DIR}/${PrecompiledBasename}.pch")
    SET(Sources ${${SourcesVar}})


    SET_SOURCE_FILES_PROPERTIES(${PrecompiledSource}
                                PROPERTIES COMPILE_FLAGS "/Yc\"${PrecompiledHeader}\" /Fp\"${PrecompiledBinary}\""
                                           OBJECT_OUTPUTS "${PrecompiledBinary}")
    SET_SOURCE_FILES_PROPERTIES(${Sources}
                                PROPERTIES COMPILE_FLAGS "/Yu\"${PrecompiledHeader}\" /FI\"${PrecompiledHeader}\" /Fp\"${PrecompiledBinary}\""
                                           OBJECT_DEPENDS "${PrecompiledBinary}")  
    # Add precompiled header to SourcesVar
    LIST(APPEND ${SourcesVar} ${PrecompiledSource})
  ENDIF(MSVC)
ENDMACRO(ADD_MSVC_PRECOMPILED_HEADER)

##############################################################################################################################################################

SET(DEBUG_INFO true)
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	SET(Project_BUILD_DEBUG true)
else() #if(CMAKE_BUILD_TYPE STREQUAL "Release")
	SET(Project_BUILD_DEBUG false)
endif()

IF(WIN32 AND NOT Project_BUILD_DEBUG)
	SET(GUI_TYPE WIN32) # disables console window if set -> primarly for release build
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
ENDIF(WIN32)

IF (APPLE)
	SET(GUI_TYPE MACOSX_BUNDLE)
ENDIF (APPLE)
# Add source to this project's executable.

set(Boost_USE_STATIC_LIBS ON) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost REQUIRED COMPONENTS filesystem date_time regex) 

set(SFML_DIR "../CMake/")
set(SFML_STATIC_LIBRARIES FALSE)
find_package(SFML REQUIRED)

set(CEGUI_DIR "../CMake/")
set(CEGUI_STATIC_LIBRARIES FALSE) # TODO: implement static CEGUI
find_package(CEGUI REQUIRED)

file(GLOB_RECURSE All_SRC
    "*.h"
    "*.hpp"
    "*.cpp"
)

file(GLOB_RECURSE Libs_SRC
    "../Libs/*.h"
    "../Libs/*.hpp"
    "../Libs/*.cpp"
)
message("Building with GUI_TYPE: ${GUI_TYPE}")
ADD_MSVC_PRECOMPILED_HEADER("stdafx.h" "stdafx.cpp" All_SRC)
add_executable(Karmazyn ${GUI_TYPE} ${All_SRC} ${Libs_SRC})

include_directories(BEFORE ${Boost_INCLUDE_DIRS} ${SFML_INCLUDE_DIRS} ${CEGUI_INCLUDE_DIRS} ".." ".") 

if(${Project_BUILD_DEBUG})
 target_link_libraries(Karmazyn ${Boost_LIBRARIES} ${SFML_ALL_LIBS_DEBUG}   ${CEGUI_ALL_LIBS_DEBUG})
else()
 target_link_libraries(Karmazyn ${Boost_LIBRARIES} ${SFML_ALL_LIBS_RELEASE} ${CEGUI_ALL_LIBS_RELEASE})
endif()

# This seems not to work, sadly
#target_link_libraries(Karmazyn ${Boost_LIBRARIES} 
#	optimized ${SFML_ALL_LIBS_RELEASE} 
#	debug ${SFML_ALL_LIBS_DEBUG}
#)
if("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
	if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC") # TODO: create the equivalent for other compilers?
		SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} /DEBUG:FULL /OPT:REF /OPT:ICF")
		message("ADDING DEBUG INFORMATION: ${CMAKE_EXE_LINKER_FLAGS}")
	endif()
endif()
message("Compile options: REL: ${CMAKE_CXX_FLAGS_RELEASE} | DEB: ${CMAKE_CXX_FLAGS_DEBUG}")
