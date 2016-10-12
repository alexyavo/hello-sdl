//
// Created by sol on 10/11/16.
//

#ifndef HELLO_WORLD_SHAPES_H
#define HELLO_WORLD_SHAPES_H

#include "Cell.h"
#include "RotationType.h"
#include "Renderer.h"

namespace Tetris {

using utils::Point2D;

enum ShapeType : uint16_t {
		L,
		O,
		I,
		J,
		S,
		T,
		Z
};

class Grid;

class Shape {
protected:
		Grid& grid_;
		std::array<Cell, 4> cells_;
		RotationType        rotation_;
		bool falling_;

public:
		// TODO this factory method moved to Grid class
		// Need this because I want to have rotated shape
		// on construction, but the rotate method is virtual.
		template<typename T>
		static std::unique_ptr<Shape>
		create(Grid& grid, RotationType rotation = RotationType::NONE) {
			auto newShape(utils::make_unique<T>(grid));
			newShape->set_rotation(rotation);
			return std::move(newShape);
		}

protected:
		Shape(Grid& grid);

public:
		virtual ~Shape() {}

		void render(SDL::Renderer& renderer);


		// All movement methods return 'true' if movement has occurred
		// (i.e. it didn't cause a collision with the grid), 'false' if
		// movement has been canceled due to collision.
		bool rotate_clockwise();
		bool rotate_counterclockwise();
		bool set_rotation(RotationType rotation);

		bool shift_right();
		bool shift_left();
		bool shift_down();

		int suicide(); // returns # of rows killed as a result

		bool is_falling();
		void mark_falling();

protected:
		// rotation logic depends on form of the concrete shape
		virtual void do_rotation(RotationType rotation) = 0;

private:
		bool is_colliding(); // returns true if shape is currently in collision with the grid
		bool is_cell_colliding(const Cell& cell);
};

// TODO make all shape ctors protected/private. Right now I can't seem to get the friend
// thing working.

class Shape_L : public Shape {
public:
		Shape_L(Grid& grid);
		virtual void do_rotation(RotationType rotation) override;
};

class Shape_O : public Shape {
public:
		Shape_O(Grid& grid);

		virtual void do_rotation(RotationType rotation) override;
};

class Shape_I : public Shape {
public:
		Shape_I(Grid& grid);
		virtual void do_rotation(RotationType rotation) override;
};

class Shape_J : public Shape {
public:
		Shape_J(Grid& grid);
		virtual void do_rotation(RotationType rotation) override;
};

class Shape_S : public Shape {
public:
		Shape_S(Grid& grid);
		virtual void do_rotation(RotationType rotation) override;
};

class Shape_Z : public Shape {
public:
		Shape_Z(Grid& grid);
		virtual void do_rotation(RotationType rotation) override;
};

class Shape_T : public Shape {
public:
		Shape_T(Grid& grid);
		virtual void do_rotation(RotationType rotation) override;
};

}

#endif //HELLO_WORLD_SHAPES_H
