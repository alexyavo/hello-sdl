//
// Created by sol on 10/2/16.
//

#ifndef HELLO_WORLD_WINDOW_H
#define HELLO_WORLD_WINDOW_H


#include <string>
#include "utils.h"

namespace SDL {

using std::string;
using std::shared_ptr;
using std::make_shared;
using utils::Color;

class Renderer;

class Window {
private:
		SDL_Window* window_;

public:
		Window(const string& name, int width, int height);
		~Window();

		shared_ptr<Renderer> create_renderer();
};

}

#endif //HELLO_WORLD_WINDOW_H
