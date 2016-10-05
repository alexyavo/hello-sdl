//
// Created by sol on 10/2/16.
//

#include <memory>
#include <stdexcept>
#include <SDL_image.h>
#include "Texture.h"
#include "Renderer.h"

namespace SDL {

Texture::~Texture() {
	SDL_DestroyTexture(texture_);
}

Texture::Texture(SDL_Texture* texture_, const int width_, const int height_)
				: texture_(texture_), width_(width_), height_(height_) {
	ThrowIfNull(texture_);
}

}


