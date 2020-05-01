# CMakeList.txt : CMake project for Karmazyn, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

include(../CMake/UsedMacros.cmake)

##############################################################################################################################################################

SET(DEBUG_INFO true)
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)
SET(BUILD_DEBUG false)
if(CMAKE_BUILD_TYPE STREQUAL "Debug") 
    SET(BUILD_DEBUG true)
endif()


####### Build configuration INDEPENDENT things:
set(Boost_USE_STATIC_LIBS ON) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost REQUIRED COMPONENTS filesystem date_time regex) 

set(SFML_DIR "../CMake/")
set(SFML_DEBUG FALSE) 
set(SFML_STATIC_LIBRARIES FALSE)
find_package(SFML REQUIRED)

set(CEGUI_DIR "../CMake/")
set(CEGUI_DEBUG FALSE) 
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

###########################################################################

#### Windows specific settings:
if (WIN32)
    ADD_MSVC_PRECOMPILED_HEADER("stdafx.h" "stdafx.cpp" All_SRC)
    if(NOT BUILD_DEBUG)
        SET(GUI_TYPE WIN32) # disables console window if set -> primarly for release build
	    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
    endif()

    if("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
        SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} /DEBUG:FULL /OPT:REF /OPT:ICF")
    endif()
elseif (UNIX)

elseif (APPLE)
	SET(GUI_TYPE MACOSX_BUNDLE)
ENDIF (WIN32)

include_directories(BEFORE ${Boost_INCLUDE_DIRS} ${SFML_INCLUDE_DIRS} ${CEGUI_INCLUDE_DIRS} ".." ".") 
add_executable(Karmazyn ${GUI_TYPE} ${All_SRC} ${Libs_SRC})
target_link_libraries(Karmazyn ${Boost_LIBRARIES} ${SFML_ALL_LIBS} ${CEGUI_ALL_LIBS})