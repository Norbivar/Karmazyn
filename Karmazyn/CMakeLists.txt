# CMakeList.txt : CMake project for Karmazyn, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost REQUIRED COMPONENTS filesystem) 

set(SFML_DIR ".")
set(SFML_STATIC_LIBRARIES FALSE)
find_package(SFML REQUIRED)

file(GLOB Karmazyn_SRC
    "*.h"
	"*.hpp"
    "*.cpp"
)
add_executable(Karmazyn ${Karmazyn_SRC} "../Libs/Logger.cpp" "../Libs/Logger.h")

include_directories(BEFORE ${Boost_INCLUDE_DIRS} ${SFML_INCLUDE_DIRS} "../Libs/") 
target_link_libraries(Karmazyn ${Boost_LIBRARIES} ${SFML_LIBRARIES})