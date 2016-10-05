//
// Created by sol on 10/2/16.
//

#ifndef HELLO_WORLD_TEXTURE_H
#define HELLO_WORLD_TEXTURE_H


#include <SDL_system.h>
#include <memory>
#include "utils.h"

namespace SDL {

class Texture : private utils::NonCopyable {
private:
		SDL_Texture* texture_;
		const int width_;
		const int height_;

public:
		Texture(SDL_Texture* texture_, const int width_, const int height_);
		~Texture();

		SDL_Texture* get_underlying() {return texture_;}

		int width() const {return width_;}
		int height() const {return height_;}
};

}

#endif //HELLO_WORLD_TEXTURE_H
