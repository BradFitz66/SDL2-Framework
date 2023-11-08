cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(SDL2_Test VERSION 1.0.0 LANGUAGES CXX)
#Use C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

include(cmake/3rdparty.cmake)
include(FindPkgConfig)


#Define different linker flags for debug and release
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(CMAKE_EXE_LINKER_FLAGS "-mwindows -Wl,-subsystem,console")
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
	set(CMAKE_EXE_LINKER_FLAGS "-mwindows -Wl,-subsystem,windows -O3")
else()
	set(CMAKE_BUILD_TYPE "Debug")
	set(CMAKE_EXE_LINKER_FLAGS "-mwindows -Wl,-subsystem,console")
endif()

set(CMAKE_EXE_LINKER_FLAGS "-mwindows -Wl,-subsystem,console")

#Add entire src directory recursively (both .cpp and .h files)c
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.hpp")

add_executable(${PROJECT_NAME} ${SOURCES})

find_package(TMXLITE REQUIRED)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)


INCLUDE_DIRECTORIES(
    ${TMXLITE_INCLUDE_DIR}
	${SDL2_INCLUDE_DIRS} 
	${SDL2IMAGE_INCLUDE_DIRS}
	${IMGUI_INCLUDE_DIRS}
)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} 
	${TMXLITE_LIBRARIES}
	${SDL2_LIBRARIES} 
	${SDL2IMAGE_LIBRARIES}
	${IMGUI_LIBRARIES}
)

