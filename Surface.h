//
// Created by sol on 10/4/16.
//

#ifndef HELLO_WORLD_SURFACE_H
#define HELLO_WORLD_SURFACE_H

#include <SDL_surface.h>
#include "utils.h"
#include "Texture.h"
#include "Renderer.h"

namespace SDL {

class Surface : private utils::NonCopyable {
private:
		SDL_Surface* surface_;

public:
		static std::unique_ptr<Surface> create_from_img(const std::string& path);

		Surface(SDL_Surface* surface_);
		~Surface();

		void fill(const utils::Color& c);
		void set_color_key(const utils::Color& c);

		int width() const {return surface_->w;}

		int height() const {return surface_->h;}

		std::unique_ptr<Texture> create_texture(Renderer& renderer);
};

}

#endif //HELLO_WORLD_SURFACE_H
