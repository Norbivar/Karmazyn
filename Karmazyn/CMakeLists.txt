# CMakeList.txt : CMake project for Karmazyn, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

include(../CMake/UsedMacros.cmake)

##############################################################################################################################################################

SET(DEBUG_INFO true COMMENT "Turns on debug information. Essentially it's the same as RelWithDebugInfo.")
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
set(CEGUI_STATIC_LIBRARIES FALSE)
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
add_executable(Karmazyn ${All_SRC} ${Libs_SRC})


#### Windows specific settings:
if (WIN32)
    ADD_MSVC_PRECOMPILED_HEADER("stdafx.h" "stdafx.cpp" All_SRC)
    #string(REPLACE "/MDd" "/MTd" CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
    #string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})

    if(NOT BUILD_DEBUG)
        SET_PROPERTY(TARGET Karmazyn PROPERTY WIN32_EXECUTABLE TRUE) # disables console window if set -> primarly for release build
	    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
    endif()

    if("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
        SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} /DEBUG:FULL /OPT:REF /OPT:ICF")
    endif()
    if(NOT CEGUI_STATIC_LIBRARIES)
        foreach(cegui_dll ${CEGUI_ALL_DLL})
            add_custom_command(TARGET Karmazyn POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    "${cegui_dll}" 
                    $<TARGET_FILE_DIR:Karmazyn>)
        endforeach()
    endif()
    if(NOT SFML_STATIC_LIBRARIES)
        foreach(sfml_dll ${SFML_ALL_DLL})
            add_custom_command(TARGET Karmazyn POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    "${sfml_dll}" 
                    $<TARGET_FILE_DIR:Karmazyn>)
        endforeach()
    endif()
elseif (UNIX)

elseif (APPLE)
    SET_PROPERTY(TARGET Karmazyn PROPERTY MACOSX_BUNDLE TRUE)
ENDIF (WIN32)

include_directories(BEFORE ${Boost_INCLUDE_DIRS} ${SFML_INCLUDE_DIRS} ${CEGUI_INCLUDE_DIRS} ".." ".") 
target_link_libraries(Karmazyn ${SFML_ALL_LIBS} ${CEGUI_DEP_LIBS} ${CEGUI_ALL_LIBS} ${Boost_LIBRARIES})

