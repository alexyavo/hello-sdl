//
// Created by sol on 10/11/16.
//

#include "Shapes.h"
#include "Grid.h"

namespace Tetris {

Shape::Shape(Grid& grid) : grid_(grid), falling_(false) {
	// TODO y is large to avoid collisions on creation
	blocks_[0] = { grid.outline().pos.x + (( Grid::Width / 2 ) * Block::size ),
								 grid.outline().pos.y + 3 * Block::size };
}

void Shape::render(SDL::Renderer& renderer) {
	for (Block& block : blocks_) {
		renderer.draw(block);
	}
}

bool Shape::rotate_clockwise() {
	switch (rotation_) {
		case NONE:
			return set_rotation(RotationType::R90);
		case R90:
			return set_rotation(RotationType::R180);
		case R180:
			return set_rotation(RotationType::R270);
		case R270:
			return set_rotation(RotationType::NONE);
	}
}

bool Shape::rotate_counterclockwise() {
	switch (rotation_) {
		case NONE:
			return set_rotation(RotationType::R270);
		case R90:
			return set_rotation(RotationType::NONE);
		case R180:
			return set_rotation(RotationType::R90);
		case R270:
			return set_rotation(RotationType::R180);
	}
}

bool Shape::shift_right() {
	if (is_falling()) {
		return false;
	}

	for (Block& block : blocks_) {
		if (is_block_colliding({ block.pos.x + Block::size, block.pos.y })) {
			return false;
		}
	}

	for (Block& block : blocks_) {
		block.pos.x += Block::size;
	}

	return true;
}

bool Shape::shift_left() {
	if (is_falling()) {
		return false;
	}

	for (Block& block : blocks_) {
		if (is_block_colliding({ block.pos.x - Block::size, block.pos.y })) {
			return false;
		}
	}

	for (Block& block : blocks_) {
		block.pos.x -= Block::size;
	}

	return true;
}

bool Shape::shift_down() {
	for (Block& block : blocks_) {
		if (is_block_colliding({ block.pos.x, block.pos.y + Block::size })) {
			return false;
		}
	}

	for (Block& block : blocks_) {
		block.pos.y += Block::size;
	}

	return true;
}

// TODO make sure that rotations don't cause collisions
bool Shape::set_rotation(RotationType rotation) {
	do_rotation(rotation);

	if (is_colliding()) {
		// revert
		do_rotation(rotation_);
		return false;
	}
	else {
		rotation_ = rotation;
		return true;
	}
}

bool Shape::is_colliding() {
	for (Block& block : blocks_) {
		if (is_block_colliding(block)) {
			return true;
		}
	}

	return false;
}

bool Shape::is_block_colliding(const Block& block) {
	if (is_rect_contained(grid_.outline(), block) == false) {
		return true;
	}
	if (grid_.is_block_dead(block)) {
		return true;
	}

	return false;
}

int Shape::suicide() {
	for (Block& block : blocks_) {
		grid_.kill_block(block);
	}

	return grid_.clear_dead_rows();
}

bool Shape::is_falling() {
	return falling_;
}

void Shape::mark_falling() {
	falling_ = true;
}

Shape_L::Shape_L(Grid& grid) : Shape(grid) {
}

void Shape_L::do_rotation(RotationType rotation) {
	switch (rotation) {
		case RotationType::NONE:
			blocks_[1] = blocks_[0].right();
			blocks_[2] = blocks_[0].up();
			blocks_[3] = blocks_[2].up();
			break;

		case RotationType::R90:
			blocks_[1] = blocks_[0].up();
			blocks_[2] = blocks_[0].left();
			blocks_[3] = blocks_[2].left();
			break;

		case RotationType::R180:
			blocks_[1] = blocks_[0].left();
			blocks_[2] = blocks_[0].down();
			blocks_[3] = blocks_[2].down();
			break;

		case RotationType::R270:
			blocks_[1] = blocks_[0].down();
			blocks_[2] = blocks_[0].right();
			blocks_[3] = blocks_[2].right();
			break;
	}
}

Shape_O::Shape_O(Grid& grid) : Shape(grid) {
}

void Shape_O::do_rotation(RotationType rotation) {
	blocks_[1] = blocks_[0].right();
	blocks_[2] = blocks_[0].down();
	blocks_[3] = blocks_[2].right();
}

Shape_I::Shape_I(Grid& grid) : Shape(grid) {
}

void Shape_I::do_rotation(RotationType rotation) {
	switch (rotation) {
		case RotationType::NONE:
			blocks_[1] = blocks_[0].up();
			blocks_[2] = blocks_[0].down();
			blocks_[3] = blocks_[2].down();
			break;

		case RotationType::R90:
			blocks_[1] = blocks_[0].left();
			blocks_[2] = blocks_[0].right();
			blocks_[3] = blocks_[2].right();
			break;

		case RotationType::R180:
			blocks_[1] = blocks_[0].up();
			blocks_[2] = blocks_[1].up();
			blocks_[3] = blocks_[0].down();
			break;

		case RotationType::R270:
			blocks_[1] = blocks_[0].right();
			blocks_[2] = blocks_[0].left();
			blocks_[3] = blocks_[2].left();
			break;
	}
}

Shape_J::Shape_J(Grid& grid) : Shape(grid) {

}

void Shape_J::do_rotation(RotationType rotation) {
	switch (rotation) {
		case RotationType::NONE:
			blocks_[1] = blocks_[0].up();
			blocks_[2] = blocks_[1].up();
			blocks_[3] = blocks_[0].left();
			break;

		case RotationType::R90:
			blocks_[1] = blocks_[0].left();
			blocks_[2] = blocks_[1].left();
			blocks_[3] = blocks_[0].down();
			break;

		case RotationType::R180:
			blocks_[1] = blocks_[0].down();
			blocks_[2] = blocks_[1].down();
			blocks_[3] = blocks_[0].right();
			break;

		case RotationType::R270:
			blocks_[1] = blocks_[0].up();
			blocks_[2] = blocks_[0].right();
			blocks_[3] = blocks_[2].right();
			break;
	}
}

Shape_S::Shape_S(Grid& grid) : Shape(grid) {

}

void Shape_S::do_rotation(RotationType rotation) {
	switch (rotation) {
		case RotationType::NONE:
			blocks_[1] = blocks_[0].right();
			blocks_[2] = blocks_[0].down();
			blocks_[3] = blocks_[2].left();
			break;

		case RotationType::R90:
			blocks_[1] = blocks_[0].up();
			blocks_[2] = blocks_[0].right();
			blocks_[3] = blocks_[2].down();
			break;

		case RotationType::R180:
			blocks_[1] = blocks_[0].left();
			blocks_[2] = blocks_[0].up();
			blocks_[3] = blocks_[2].right();
			break;

		case RotationType::R270:
			blocks_[1] = blocks_[0].down();
			blocks_[2] = blocks_[0].left();
			blocks_[3] = blocks_[2].up();
			break;
	}
}

Shape_Z::Shape_Z(Grid& grid) : Shape(grid) {

}

void Shape_Z::do_rotation(RotationType rotation) {
	switch (rotation) {
		case RotationType::NONE:
			blocks_[1] = blocks_[0].left();
			blocks_[2] = blocks_[0].down();
			blocks_[3] = blocks_[2].right();
			break;

		case RotationType::R90:
			blocks_[1] = blocks_[0].up();
			blocks_[2] = blocks_[0].left();
			blocks_[3] = blocks_[2].down();
			break;

		case RotationType::R180:
			blocks_[1] = blocks_[0].right();
			blocks_[2] = blocks_[0].up();
			blocks_[3] = blocks_[2].left();
			break;

		case RotationType::R270:
			blocks_[1] = blocks_[0].down();
			blocks_[2] = blocks_[0].right();
			blocks_[3] = blocks_[2].up();
			break;
	}
}

Shape_T::Shape_T(Grid& grid) : Shape(grid) {

}

void Shape_T::do_rotation(RotationType rotation) {
	switch (rotation) {
		case RotationType::NONE:
			blocks_[1] = blocks_[0].down();
			blocks_[2] = blocks_[0].left();
			blocks_[3] = blocks_[0].right();
			break;

		case RotationType::R90:
			blocks_[1] = blocks_[0].up();
			blocks_[2] = blocks_[0].down();
			blocks_[3] = blocks_[0].right();
			break;

		case RotationType::R180:
			blocks_[1] = blocks_[0].up();
			blocks_[2] = blocks_[0].left();
			blocks_[3] = blocks_[0].right();
			break;

		case RotationType::R270:
			blocks_[1] = blocks_[0].down();
			blocks_[2] = blocks_[0].left();
			blocks_[3] = blocks_[0].up();
			break;
	}
}

}