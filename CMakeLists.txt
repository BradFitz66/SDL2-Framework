cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(SDL2_Test VERSION 1.0.0 LANGUAGES CXX)
include(cmake/3rdparty.cmake)


INCLUDE(FindPkgConfig)


#Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-mwindows -Wl,-subsystem,console")

#Add entire src directory recursively (both .cpp and .h files)c
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.hpp")

add_executable(${PROJECT_NAME} ${SOURCES})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

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

