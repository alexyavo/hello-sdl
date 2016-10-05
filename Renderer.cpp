//
// Created by sol on 10/2/16.
//

#include <SDL_image.h>
#include <stdexcept>
#include "Renderer.h"
#include "Texture.h"

namespace SDL {

using std::logic_error;

SDL::Renderer::Renderer(SDL_Renderer* renderer) : renderer_(renderer) {
	ThrowIfNull(renderer_);
}

SDL::Renderer::~Renderer() {
	SDL_DestroyRenderer(renderer_);
}

void SDL::Renderer::clear() {
	SDLThrowOnErr(SDL_RenderClear(renderer_));
}

void SDL::Renderer::present() {
	SDL_RenderPresent(renderer_);
}

void Renderer::set_viewport(const Rectangle& viewport) {
	SDL_Rect r = convert(viewport);
	SDLThrowOnErr(SDL_RenderSetViewport(renderer_, &r));
}

void Renderer::set_drawcolor(const Color& c) {
	SDLThrowOnErr(SDL_SetRenderDrawColor(renderer_, EXPAND_COLOR(c), c.alpha));
}

void Renderer::draw(const Rectangle& rect, const bool filled) {
	SDL_Rect r = convert(rect);
	SDLThrowOnErr(( filled ? SDL_RenderFillRect : SDL_RenderDrawRect )(renderer_, &r));
}

void Renderer::draw(const Line& line) {
	SDLThrowOnErr(
					SDL_RenderDrawLine(renderer_, EXPAND_POINT2D(line.point1), EXPAND_POINT2D(line.point2)));
}

void Renderer::draw(const Point2D& point) {
	SDLThrowOnErr(SDL_RenderDrawPoint(renderer_, EXPAND_POINT2D(point)));
}

void Renderer::render_copy(Texture& texture, const utils::Point2D& at) {
	SDL_Rect r = { EXPAND_POINT2D(at), texture.width(), texture.height() };
	SDLThrowOnErr(SDL_RenderCopy(renderer_, texture.get_underlying(), NULL, &r));
}

}