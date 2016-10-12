cmake_minimum_required(VERSION 3.6)
project(hello_world)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
	main.cpp
	utils.h
	Renderer.cpp Renderer.h
	Window.cpp Window.h
	Texture.cpp Texture.h
	utils.cpp
	TtfFont.cpp TtfFont.h
	Surface.cpp Surface.h
	tetris/Grid.cpp tetris/Grid.h
	tetris/Cell.cpp tetris/Cell.h
	tetris/RotationType.h
	tetris/Shapes.cpp tetris/Shapes.h
	Random.h tetris/Game.cpp tetris/Game.h)

add_executable(hello_world ${SOURCE_FILES})

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)

INCLUDE_DIRECTORIES(
		${SDL2_INCLUDE_DIRS}
		${SDL2IMAGE_INCLUDE_DIRS}
		${SDL2MIXER_INCLUDE_DIRS}
		${SDL2TTF_INCLUDE_DIRS}
)

TARGET_LINK_LIBRARIES(
		${PROJECT_NAME}
		${SDL2_LIBRARIES}
		${SDL2IMAGE_LIBRARIES}
		${SDL2MIXER_LIBRARIES}
		${SDL2TTF_LIBRARIES}
)