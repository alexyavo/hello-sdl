//
// Created by sol on 10/2/16.
//

#include <SDL_system.h>
#include "Window.h"
#include "Renderer.h"

namespace SDL {

Window::Window(const string& name, int width, int height) {
	SDLThrowIfNull(window_ = SDL_CreateWindow(name.c_str(),
																						SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
																						width, height, SDL_WINDOW_SHOWN));
}

Window::~Window() {
	SDL_DestroyWindow(window_);
}

shared_ptr<Renderer> Window::create_renderer() {
	return make_shared<Renderer>(
					SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
}

}