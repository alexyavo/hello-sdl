//
// Created by sol on 10/11/16.
//

#include "Block.h"

namespace Tetris {

using namespace utils;

Block::Block(const Point2D& pos) : Rectangle(pos, Block::size, Block::size) {

}

Block Block::left() {
	return { this->pos.x - Block::size, this->pos.y };
}

Block Block::right() {
	return { this->pos.x + Block::size, this->pos.y };
}

Block Block::up() {
	return { this->pos.x, this->pos.y - Block::size };
}

Block Block::down() {
	return { this->pos.x, this->pos.y + Block::size };
}

Block::Block(const Block& other) : Block(other.pos) {

}

Block::Block(int x, int y) : Block(Point2D(x, y)) {

}

}