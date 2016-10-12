//
// Created by sol on 10/11/16.
//

#ifndef HELLO_WORLD_ROTATIONTYPE_H
#define HELLO_WORLD_ROTATIONTYPE_H

#include <cstdint>

namespace Tetris {

enum RotationType : uint8_t {
		NONE,
		R90,
		R180,
		R270, // aka -90
};

}

#endif //HELLO_WORLD_ROTATIONTYPE_H
