//
// Created by sol on 10/4/16.
//

#include <stdexcept>
#include <SDL_image.h>
#include "Surface.h"

namespace SDL {

Surface::Surface(SDL_Surface* surface_) : surface_(surface_) {
	if (surface_ == nullptr) {
		throw std::logic_error("Surface ptr cannot be null");
	}
}

Surface::~Surface() {
	SDL_FreeSurface(surface_);
}

void Surface::fill(const utils::Color& c) {
	SDLThrowOnErr(SDL_FillRect(surface_, nullptr, SDL_MapRGB(surface_->format, EXPAND_COLOR(c))));
}

std::unique_ptr<Surface> Surface::create_from_img(const std::string& path) {
	SDL_Surface* s = IMG_Load(path.c_str());
	if (s == nullptr) {
		throw std::logic_error(IMG_GetError());
	}

	return utils::make_unique<Surface>(s);
}

void Surface::set_color_key(const utils::Color& c) {
	SDLThrowOnErr(SDL_SetColorKey(surface_, SDL_TRUE, SDL_MapRGB(surface_->format, EXPAND_COLOR(c))));
}

std::unique_ptr<Texture> Surface::create_texture(Renderer& renderer) {
	SDL_Texture* t = SDL_CreateTextureFromSurface(renderer.get_underlying(), surface_);
	SDLThrowIfNull(t);
	return utils::make_unique<Texture>(t, width(), height());
}

}
