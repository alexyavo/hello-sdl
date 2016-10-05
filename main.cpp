#include <SDL.h>

#include <string>
#include <stdexcept>
#include <iostream>
#include <cstdint>
#include <memory>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <sstream>

#include "utils.h"
#include "Window.h"
#include "Renderer.h"
#include "Texture.h"
#include "TtfFont.h"

//Screen dimension constants
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
const char* ASSETS_DIR = "/home/sol/.tmp/assets/";

using std::logic_error;
using std::shared_ptr;

using namespace utils;

namespace SDL {

class Initializer {
public:
		Initializer() {
			SDL_Init(SDL_INIT_VIDEO);
			if (SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1") != SDL_TRUE) {
				LOG_WARN << "Linear texture filtering is not enabled";
			}

			int imgFlags      = IMG_INIT_PNG;
			int imgInitResult = IMG_Init(imgFlags);
			if (imgInitResult == 0 || imgInitResult != imgFlags) {
				throw logic_error(IMG_GetError());
			}

			if (TTF_Init() == -1) {
				throw logic_error(TTF_GetError());
			}
		}

		~Initializer() {
			TTF_Quit();
			IMG_Quit();
			SDL_Quit();
		}
};

}

Rectangle get_centered_rect(int containerWidth, int containerHeight,
														int rectWidth, int rectHeight) {
	return {{ ( containerWidth / 2 ) - ( rectWidth / 2 ),
						( containerHeight / 2 ) - ( rectHeight / 2 ) },
					rectWidth,
					rectHeight };
}

int main(int argc, char* args[]) {
	SDL::Initializer init;

	try {
		SDL::Window               window("sdl test", SCREEN_WIDTH, SCREEN_HEIGHT);
		shared_ptr<SDL::Renderer> renderer(window.create_renderer());
		SDL::TtfFont              defaultFont("/home/sol/.tmp/assets/default.ttf", 16);

		const Uint32 ticksPerFrame = 1000 / 60;
		uint32_t nframes = 0;
		while (true) {
			Uint32 startTime = SDL_GetTicks();

			SDL_Event e;
			while (SDL_PollEvent(&e) != 0) {
				switch (e.type) {
					case SDL_QUIT:
						return 0;
				}
			}

			renderer->set_drawcolor(Color::WHITE);
			renderer->clear();

			const int cellSize        = 20;
			const int gridWidthCells  = 10;
			const int gridHeightCells = 20;

			Rectangle grid = get_centered_rect(SCREEN_WIDTH, SCREEN_HEIGHT,
																				 gridWidthCells * cellSize, gridHeightCells * cellSize);
			renderer->set_drawcolor(Color::BLACK);
			renderer->draw(grid);

			Uint32 endTime = SDL_GetTicks();
			int32_t sleepDelta = ticksPerFrame - (endTime - startTime);
			if (sleepDelta > 0) {
				SDL_Delay(sleepDelta);
			}

			double avgFps = nframes / (SDL_GetTicks() / 1000.f);
			std::stringstream avgFpsText;
			avgFpsText << avgFps << " avg FPS";
			renderer->render_copy(
							*defaultFont.render_solid(avgFpsText.str(), Color::BLACK)->createTexture(*renderer),
							{ 0, 0 });


			renderer->present();
			++nframes;
		}


		//SDL_Delay(2000);


//		SDL::FilledRectangle({ 0xFF, 0x00, 0x00 }, 0xFF,
//												 { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4 },
//												 SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2)
//						.renderWith(*renderer);
//
//		SDL::OutlinedRectangle({ 0x00, 0xFF, 0x00 }, 0xFF,
//													 { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6 },
//													 SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3)
//						.renderWith(*renderer);
//
//		SDL::Line({0x00, 0x00, 0xFF}, 0xFF,
//							{ 0, SCREEN_HEIGHT / 2 }, { SCREEN_WIDTH, SCREEN_HEIGHT / 2 })
//						.renderWith(*renderer);
//
//
//		renderer->present();
//		SDL_Delay(5000);
//
//		// ----------------------------------------------------------------------------
//

//
//
//		utils::Color colorKey(0x00, 0xFF, 0xFF);
//		SDL::Texture playerTexture(renderer->loadTextureFromFile("/home/sol/.tmp/assets/player2.png",
//																														 &colorKey));
//		SDL::Texture bgTexture(renderer->loadTextureFromFile("/home/sol/.tmp/assets/background.png",
//																												 &colorKey));
//
//
//		{
//			renderer->set_viewport({ SCREEN_WIDTH / 3 * 2, 0 }, SCREEN_WIDTH / 3, SCREEN_HEIGHT);
//			bgTexture.renderAt({ 0, 0 });
//		}
//
//		{
//			renderer->set_viewport({ 0, 0 }, SCREEN_WIDTH / 3 * 2, SCREEN_HEIGHT);
//			playerTexture.renderAt({ 240, 190 });
//		}
//

	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}


	return 0;
}