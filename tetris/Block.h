//
// Created by sol on 10/11/16.
//

#ifndef HELLO_WORLD_CELL_H
#define HELLO_WORLD_CELL_H

#include "../utils.h"

namespace Tetris {

class Block : public utils::Rectangle {
public:
		static constexpr int size = 20;

public:
		Block(int x, int y);
		Block(const Block& other);
		Block(const utils::Point2D& pos = { 0, 0 });

		Block left();
		Block right();
		Block up();
		Block down();
};

}


#endif //HELLO_WORLD_CELL_H
