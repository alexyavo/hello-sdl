//
// Created by sol on 10/4/16.
//

#include "utils.h"

namespace utils {

Color Color::BLACK = { 0x00, 0x00, 0x00 };
Color Color::WHITE = { 0xFF, 0xFF, 0xFF };

Color::Color(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t alpha)
				: r(r), g(g), b(b), alpha(alpha) {}

Line::Line(const Point2D& point1, const Point2D point2) : point1(point1), point2(point2) {}

Rectangle::Rectangle(const Point2D& topLeft, const int width, const int height)
				: topLeft(topLeft), width(width), height(height) {}

Rectangle::Rectangle(const Rectangle& other) : Rectangle(other.topLeft, other.width, other.height) {

}

Rectangle& Rectangle::operator=(const Rectangle& other) {
	topLeft = other.topLeft;
	width   = other.width;
	height  = other.height;
	return *this;
}

Rectangle::Rectangle() : Rectangle(Point2D(), 0, 0) {
}

Square::Square(const Point2D& topLeft, const int sideLength) : Rectangle(topLeft, sideLength,
																																				 sideLength) {

}

Rectangle
get_centered_rect(int containerWidth, int containerHeight, int rectWidth, int rectHeight) {
	return {{ ( containerWidth / 2 ) - ( rectWidth / 2 ),
						( containerHeight / 2 ) - ( rectHeight / 2 ) },
					rectWidth,
					rectHeight };
}

bool is_rect_contained(const Rectangle& container, const Rectangle& containee) {
	return container.topLeft.x <= containee.topLeft.x &&
				 container.topLeft.y <= containee.topLeft.y &&
				 ( containee.topLeft.x + containee.width ) <= ( container.topLeft.x + container.width ) &&
				 ( containee.topLeft.y + containee.height ) <= ( container.topLeft.y + container.height );
}

}

namespace SDL {

SDL_Rect convert(const utils::Rectangle& rect) {
	return { rect.topLeft.x, rect.topLeft.y, rect.width, rect.height };
}

SDL_Color convert(const utils::Color& color) {
	return { EXPAND_COLOR(color), color.alpha };
}

}

