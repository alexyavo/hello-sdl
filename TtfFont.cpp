//
// Created by sol on 10/4/16.
//

#include "TtfFont.h"

#include <stdexcept>

namespace SDL {


TtfFont::TtfFont(const std::string& path, int ptSize) {
	font_ = TTF_OpenFont(path.c_str(), ptSize);
	if (font_ == NULL) {
		throw std::logic_error(TTF_GetError());
	}
}

TtfFont::~TtfFont() {
	TTF_CloseFont(font_);
}

std::unique_ptr<Surface> TtfFont::render_solid(const std::string& text, const Color& color) {
	SDL_Surface* s = TTF_RenderText_Solid(font_, text.c_str(), convert(color) );
	if (s == nullptr) {
		throw std::logic_error(TTF_GetError());
	}

	return utils::make_unique<Surface>(s);
}

}