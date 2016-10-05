//
// Created by sol on 10/2/16.
//

#ifndef HELLO_WORLD_RENDERER_H
#define HELLO_WORLD_RENDERER_H


#include <SDL_system.h>
#include <memory>
#include <string>
#include "utils.h"

namespace SDL {

using std::string;
using utils::Point2D;
using utils::Color;
using utils::Rectangle;
using utils::Line;

class Texture;

class Renderer : private utils::NonCopyable {
private:
		SDL_Renderer* renderer_;

public:
		Renderer(SDL_Renderer* renderer);
		~Renderer();

		void clear();
		void present();

		void set_viewport(const Rectangle& viewport);
		void set_drawcolor(const Color& c);

		void draw(const Rectangle& rect, const bool filled = false);
		void draw(const Line& line);
		void draw(const Point2D& point);

		void render_copy(Texture& texture, const utils::Point2D& at);

		// TODO this is ugly as fuck
		SDL_Renderer* get_underlying() {return renderer_;}
};

}

#endif //HELLO_WORLD_RENDERER_H
