//
// Created by sol on 10/11/16.
//

#ifndef HELLO_WORLD_CELL_H
#define HELLO_WORLD_CELL_H

#include "../utils.h"

namespace Tetris {

class Cell : public utils::Rectangle {
public:
		static constexpr int size = 20;

public:
		Cell(const Cell& other);
		Cell(const utils::Point2D& topLeft = { 0, 0 });
		Cell left();
		Cell right();
		Cell up();
		Cell down();
};

}


#endif //HELLO_WORLD_CELL_H
