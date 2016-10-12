//
// Created by sol on 10/11/16.
//

#ifndef HELLO_WORLD_GRID_H
#define HELLO_WORLD_GRID_H

#include <cstdint>
#include <vector>
#include "utils.h"
#include "Renderer.h"
#include "Cell.h"
#include "Shapes.h"
#include "Random.h"

namespace Tetris {

class Grid {

public:
		// In terms of #cells
		static constexpr int Width  = 10;
		static constexpr int Height = 22; // TODO make it 20, with 2 hidden rows

private:
		utils::Rectangle outline_;
		bool             deadCells_[Grid::Width][Grid::Height];
		utils::Random rand_;

public:
		Grid(int screenWidth, int screenHeight);
		void render(SDL::Renderer& renderer);

		utils::Rectangle outline() const { return outline_; }

		bool is_cell_dead(const Cell& cell);
		void kill_cell(const Cell& cell);
		int clear_dead_rows(); // TODO hack, should be part of kill_cell but it would move the grid

		std::unique_ptr<Shape> spawn_shape();
};

}


#endif //HELLO_WORLD_GRID_H
