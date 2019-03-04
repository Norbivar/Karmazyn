# CMakeList.txt : CMake project for Karmazyn, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	SET(Project_BUILD_DEBUG true)
else() #if(CMAKE_BUILD_TYPE STREQUAL "Release")
	SET(Project_BUILD_DEBUG false)
endif()

IF(WIN32 AND NOT Project_BUILD_DEBUG)
	SET(GUI_TYPE WIN32)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
ENDIF(WIN32)

IF (APPLE)
	SET(GUI_TYPE MACOSX_BUNDLE)
ENDIF (APPLE)
# Add source to this project's executable.

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost REQUIRED COMPONENTS filesystem) 

set(SFML_DIR "./CMake/")
set(SFML_STATIC_LIBRARIES FALSE)
find_package(SFML REQUIRED)

file(GLOB_RECURSE Karmazyn_SRC
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
add_executable(Karmazyn ${GUI_TYPE} ${Karmazyn_SRC} ${Libs_SRC})

include_directories(BEFORE ${Boost_INCLUDE_DIRS} ${SFML_INCLUDE_DIRS} "../Libs/" ".") 

if(${Project_BUILD_DEBUG})
 target_link_libraries(Karmazyn ${Boost_LIBRARIES} ${SFML_ALL_LIBS_DEBUG})
else()
 target_link_libraries(Karmazyn ${Boost_LIBRARIES} ${SFML_ALL_LIBS_RELEASE})
endif()

# This seems not to work, sadly
#target_link_libraries(Karmazyn ${Boost_LIBRARIES} 
#	optimized ${SFML_ALL_LIBS_RELEASE} 
#	debug ${SFML_ALL_LIBS_DEBUG}
#)

message("Compile options: REL: ${CMAKE_CXX_FLAGS_RELEASE} | DEB: ${CMAKE_CXX_FLAGS_DEBUG}")