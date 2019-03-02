# CMakeList.txt : CMake project for Karmazyn, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

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
add_executable(Karmazyn ${Karmazyn_SRC} ${Libs_SRC})

include_directories(BEFORE ${Boost_INCLUDE_DIRS} ${SFML_INCLUDE_DIRS} "../Libs/" ".") 

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
 target_link_libraries(Karmazyn ${Boost_LIBRARIES} ${SFML_ALL_LIBS_DEBUG})
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
 target_link_libraries(Karmazyn ${Boost_LIBRARIES} ${SFML_ALL_LIBS_RELEASE})
endif()

# This seems not to work, sadly
#target_link_libraries(Karmazyn ${Boost_LIBRARIES} 
#	optimized ${SFML_ALL_LIBS_RELEASE} 
#	debug ${SFML_ALL_LIBS_DEBUG}
#)

message("Compile options: REL: ${CMAKE_CXX_FLAGS_RELEASE} | DEB: ${CMAKE_CXX_FLAGS_DEBUG}")