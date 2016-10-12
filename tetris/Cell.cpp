//
// Created by sol on 10/11/16.
//

#include "Cell.h"

namespace Tetris {

using namespace utils;

Cell::Cell(const Point2D& topLeft) : Rectangle(topLeft, Cell::size, Cell::size) {

}

Cell Cell::left() {
	return Point2D(this->topLeft.x - Cell::size, this->topLeft.y);
}

Cell Cell::right() {
	return Point2D(this->topLeft.x + Cell::size, this->topLeft.y);
}

Cell Cell::up() {
	return Point2D(this->topLeft.x, this->topLeft.y - Cell::size);
}

Cell Cell::down() {
	return Point2D(this->topLeft.x, this->topLeft.y + Cell::size);
}

Cell::Cell(const Cell& other) : Cell(other.topLeft) {

}

}