cmake_minimum_required(VERSION 3.16)
project(NanoPC)
enable_testing()

INCLUDE(FindPkgConfig)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Boost COMPONENTS program_options unit_test_framework REQUIRED)
#find_package(Lua 5.3 REQUIRED)
#include_directories(${LUA_INCLUDE_DIR})


option(USE_SDL_LIBRARY "Do you want to use an sdl2 library?" OFF)
#option(USE_SDL_LIBRARY "Do you want to use an sdl2 library?" ON)

IF(USE_SDL_LIBRARY)
    find_package(SDL2 REQUIRED)
    #find_package(SDL2_image REQUIRED)
    PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
    PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)
    include_directories(${SDL2_INCLUDE_DIRS})
    message(STATUS "INFO: Selected SDL GUI")
ELSE(USE_SDL_LIBRARY)
    message(STATUS "INFO: Selected console user interface")
ENDIF(USE_SDL_LIBRARY)

set(CURSES_NEED_WIDE TRUE)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

find_package(Doxygen)
IF(DOXYGEN_FOUND)
	set(DOXYGEN_GENERATE_HTML YES)
	set(DOXYGEN_PROJECT_NAME $(PROJECT_NAME))
	set(DOXYGEN_OUTPUT_LANGUAGE "Russian")
	message(STATUS "source dir: " ${PROJECT_SOURCE_DIR})
	doxygen_add_docs(doxygen ${PROJECT_SOURCE_DIR})
ELSE(DOXYGEN_FOUND)
    message(STATUS "WARNING: Doxygen not found - Reference manual will not be created")
ENDIF(DOXYGEN_FOUND)

message(STATUS "project name: " ${PROJECT_NAME})
file (GLOB SOURCE src/*.cpp)

include_directories("headers")

add_executable(${PROJECT_NAME} ${SOURCE})
target_link_libraries(${PROJECT_NAME} 
                    ${LUA_LIBRARIES}
                    ${CURSES_LIBRARY}
                    ${Boost_LIBRARIES} 
                    ${SDL2TTF_LIBRARIES} 
                    ${SDL2_LIBRARIES} 
                    ${SDL2IMAGE_LIBRARIES}
                    )

file (GLOB TESTS_SOURCES test/*.cpp)
set (TEST test_${PROJECT_NAME})
add_executable (${TEST} ${TESTS_SOURCES} src/core.cpp)
target_link_libraries (${TEST} ${Boost_LIBRARIES})
add_test(NAME test1 COMMAND ${TEST})
