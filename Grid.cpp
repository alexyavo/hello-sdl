//
// Created by sol on 10/11/16.
//

#include "Grid.h"
#include "Cell.h"

namespace Tetris {

using namespace utils;

Grid::Grid(int screenWidth, int screenHeight) {
	outline_ = get_centered_rect(screenWidth, screenHeight,
															 Grid::Width * Cell::size,
															 Grid::Height * Cell::size);
	// Align grid to cell size
	outline_.topLeft.x -= outline_.topLeft.x % Cell::size;
	outline_.topLeft.y -= outline_.topLeft.y % Cell::size;

	for (int i = 0; i < Grid::Width; ++i) {
		for (int j = 0; j < Grid::Height; ++j) {
			deadCells_[i][j] = false;
		}
	}
}

void Grid::render(SDL::Renderer& renderer) {
	renderer.draw(outline_);

	for (int i = 0; i < Grid::Width; ++i) {
		for (int j = 0; j < Grid::Height; ++j) {
			if (deadCells_[i][j]) {
				utils::Rectangle cell({ outline_.topLeft.x + i * Cell::size,
																outline_.topLeft.y + j * Cell::size },
															Cell::size, Cell::size);
				renderer.draw(cell, true);
			}
		}
	}
}

bool Grid::is_cell_dead(const Cell& cell) {
	return
					deadCells_
					[( cell.topLeft.x - outline_.topLeft.x ) / Cell::size]
					[( cell.topLeft.y - outline_.topLeft.y ) / Cell::size];
}

void Grid::kill_cell(const Cell& cell) {
	deadCells_
	[( cell.topLeft.x - outline_.topLeft.x ) / Cell::size]
	[( cell.topLeft.y - outline_.topLeft.y ) / Cell::size] = true;
}

int Grid::clear_dead_rows() {
	int clearedRowsCount = 0;

	for (int j = Grid::Height - 1; j >= 0; --j) {
		bool rowIsFull = true;

		for (int i = 0; i < Grid::Width; ++i) {
			if (deadCells_[i][j] == false) {
				rowIsFull = false;
				break;
			}
		}

		if (rowIsFull) {
			++clearedRowsCount;

			for (int i = 0; i < Grid::Width; ++i) {
				deadCells_[i][j] = false;
			}

			for (int j2 = j; j2 > 0; --j2) {
				for (int i = 0; i < Grid::Width; ++i) {
					deadCells_[i][j2] = deadCells_[i][j2 - 1];
				}
			}

			++j; // repeat check for now after collapsing
		}
	}

	return clearedRowsCount;
}

// TODO cmon man, wtf
std::unique_ptr<Shape> Grid::spawn_shape() {
	RotationType r;
	switch (rand_.uni(4)) {
		case 0:
			r = RotationType::NONE;
			break;
		case 1:
			r = RotationType::R90;
			break;
		case 2:
			r = RotationType::R180;
			break;
		case 3:
			r = RotationType::R270;
			break;
		default:
			r = RotationType::NONE;
			break;
	}

	switch (rand_.uni(7)) {
		case 0:
			return Shape::create<Shape_T>(*this, r);
		case 1:
			return Shape::create<Shape_O>(*this, r);
		case 2:
			return Shape::create<Shape_L>(*this, r);
		case 3:
			return Shape::create<Shape_Z>(*this, r);
		case 4:
			return Shape::create<Shape_S>(*this, r);
		case 5:
			return Shape::create<Shape_J>(*this, r);
		case 6:
			return Shape::create<Shape_I>(*this, r);
		default:
			1/0;
	}
}

}