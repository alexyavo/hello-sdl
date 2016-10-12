//
// Created by sol on 10/11/16.
//

#include "Shapes.h"
#include "Grid.h"

namespace Tetris {

Shape::Shape(Grid& grid) : grid_(grid), falling_(false) {
	// TODO y is large to avoid collisions on creation
	cells_[0] = Cell(Point2D(grid.outline().topLeft.x + (( Grid::Width / 2 ) * Cell::size ),
													 grid.outline().topLeft.y + 3 * Cell::size));
}

void Shape::render(SDL::Renderer& renderer) {
	for (Cell& cell : cells_) {
		renderer.draw(cell);
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

	for (Cell& cell : cells_) {
		if (is_cell_colliding(Cell(Point2D(cell.topLeft.x + Cell::size,
																			 cell.topLeft.y)))) {
			return false;
		}
	}

	for (Cell& cell : cells_) {
		cell.topLeft.x += Cell::size;
	}

	return true;
}

bool Shape::shift_left() {
	if (is_falling()) {
		return false;
	}

	for (Cell& cell : cells_) {
		if (is_cell_colliding(Cell(Point2D(cell.topLeft.x - Cell::size,
																			 cell.topLeft.y)))) {
			return false;
		}
	}

	for (Cell& cell : cells_) {
		cell.topLeft.x -= Cell::size;
	}

	return true;
}

bool Shape::shift_down() {
	for (Cell& cell : cells_) {
		if (is_cell_colliding(Cell(Point2D(cell.topLeft.x,
																			 cell.topLeft.y + Cell::size)))) {
			return false;
		}
	}

	for (Cell& cell : cells_) {
		cell.topLeft.y += Cell::size;
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
	for (Cell& cell : cells_) {
		if (is_cell_colliding(cell)) {
			return true;
		}
	}

	return false;
}

bool Shape::is_cell_colliding(const Cell& cell) {
	if (is_rect_contained(grid_.outline(), cell) == false) {
		return true;
	}
	if (grid_.is_cell_dead(cell)) {
		return true;
	}

	return false;
}

int Shape::suicide() {
	for (Cell& cell : cells_) {
		grid_.kill_cell(cell);
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
			cells_[1] = cells_[0].right();
			cells_[2] = cells_[0].up();
			cells_[3] = cells_[2].up();
			break;

		case RotationType::R90:
			cells_[1] = cells_[0].up();
			cells_[2] = cells_[0].left();
			cells_[3] = cells_[2].left();
			break;

		case RotationType::R180:
			cells_[1] = cells_[0].left();
			cells_[2] = cells_[0].down();
			cells_[3] = cells_[2].down();
			break;

		case RotationType::R270:
			cells_[1] = cells_[0].down();
			cells_[2] = cells_[0].right();
			cells_[3] = cells_[2].right();
			break;
	}
}

Shape_O::Shape_O(Grid& grid) : Shape(grid) {
}

void Shape_O::do_rotation(RotationType rotation) {
	cells_[1] = cells_[0].right();
	cells_[2] = cells_[0].down();
	cells_[3] = cells_[2].right();
}

Shape_I::Shape_I(Grid& grid) : Shape(grid) {
}

void Shape_I::do_rotation(RotationType rotation) {
	switch (rotation) {
		case RotationType::NONE:
			cells_[1] = cells_[0].up();
			cells_[2] = cells_[0].down();
			cells_[3] = cells_[2].down();
			break;

		case RotationType::R90:
			cells_[1] = cells_[0].left();
			cells_[2] = cells_[0].right();
			cells_[3] = cells_[2].right();
			break;

		case RotationType::R180:
			cells_[1] = cells_[0].up();
			cells_[2] = cells_[1].up();
			cells_[3] = cells_[0].down();
			break;

		case RotationType::R270:
			cells_[1] = cells_[0].right();
			cells_[2] = cells_[0].left();
			cells_[3] = cells_[2].left();
			break;
	}
}

Shape_J::Shape_J(Grid& grid) : Shape(grid) {

}

void Shape_J::do_rotation(RotationType rotation) {
	switch (rotation) {
		case RotationType::NONE:
			cells_[1] = cells_[0].up();
			cells_[2] = cells_[1].up();
			cells_[3] = cells_[0].left();
			break;

		case RotationType::R90:
			cells_[1] = cells_[0].left();
			cells_[2] = cells_[1].left();
			cells_[3] = cells_[0].down();
			break;

		case RotationType::R180:
			cells_[1] = cells_[0].down();
			cells_[2] = cells_[1].down();
			cells_[3] = cells_[0].right();
			break;

		case RotationType::R270:
			cells_[1] = cells_[0].up();
			cells_[2] = cells_[0].right();
			cells_[3] = cells_[2].right();
			break;
	}
}

Shape_S::Shape_S(Grid& grid) : Shape(grid) {

}

void Shape_S::do_rotation(RotationType rotation) {
	switch (rotation) {
		case RotationType::NONE:
			cells_[1] = cells_[0].right();
			cells_[2] = cells_[0].down();
			cells_[3] = cells_[2].left();
			break;

		case RotationType::R90:
			cells_[1] = cells_[0].up();
			cells_[2] = cells_[0].right();
			cells_[3] = cells_[2].down();
			break;

		case RotationType::R180:
			cells_[1] = cells_[0].left();
			cells_[2] = cells_[0].up();
			cells_[3] = cells_[2].right();
			break;

		case RotationType::R270:
			cells_[1] = cells_[0].down();
			cells_[2] = cells_[0].left();
			cells_[3] = cells_[2].up();
			break;
	}
}

Shape_Z::Shape_Z(Grid& grid) : Shape(grid) {

}

void Shape_Z::do_rotation(RotationType rotation) {
	switch (rotation) {
		case RotationType::NONE:
			cells_[1] = cells_[0].left();
			cells_[2] = cells_[0].down();
			cells_[3] = cells_[2].right();
			break;

		case RotationType::R90:
			cells_[1] = cells_[0].up();
			cells_[2] = cells_[0].left();
			cells_[3] = cells_[2].down();
			break;

		case RotationType::R180:
			cells_[1] = cells_[0].right();
			cells_[2] = cells_[0].up();
			cells_[3] = cells_[2].left();
			break;

		case RotationType::R270:
			cells_[1] = cells_[0].down();
			cells_[2] = cells_[0].right();
			cells_[3] = cells_[2].up();
			break;
	}
}

Shape_T::Shape_T(Grid& grid) : Shape(grid) {

}

void Shape_T::do_rotation(RotationType rotation) {
	switch (rotation) {
		case RotationType::NONE:
			cells_[1] = cells_[0].down();
			cells_[2] = cells_[0].left();
			cells_[3] = cells_[0].right();
			break;

		case RotationType::R90:
			cells_[1] = cells_[0].up();
			cells_[2] = cells_[0].down();
			cells_[3] = cells_[0].right();
			break;

		case RotationType::R180:
			cells_[1] = cells_[0].up();
			cells_[2] = cells_[0].left();
			cells_[3] = cells_[0].right();
			break;

		case RotationType::R270:
			cells_[1] = cells_[0].down();
			cells_[2] = cells_[0].left();
			cells_[3] = cells_[0].up();
			break;
	}
}

}