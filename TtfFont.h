//
// Created by sol on 10/4/16.
//

#ifndef HELLO_WORLD_TTFFONT_H
#define HELLO_WORLD_TTFFONT_H


#include <SDL_ttf.h>
#include <string>
#include "utils.h"
#include "Surface.h"

namespace SDL {


class TtfFont : private utils::NonCopyable {
private:
		TTF_Font* font_;

public:
		TtfFont(const std::string& path, int ptSize);
		~TtfFont();

		std::unique_ptr<Surface> render_solid(const std::string& text, const Color& color);

		TTF_Font* get_underlying() {return font_;}
};

}

#endif //HELLO_WORLD_TTFFONT_H
