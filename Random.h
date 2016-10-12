//
// Created by sol on 10/11/16.
//

#ifndef HELLO_WORLD_RANDOM_H
#define HELLO_WORLD_RANDOM_H

#include <random>

namespace utils {

class Random {
private:
		std::random_device device_;
		std::default_random_engine engine_;

public:
		Random() {
			engine_ = std::default_random_engine(device_());
		}

		int uni(int n) {
			std::uniform_int_distribution<int> uniform_dist(0, n - 1);
			return uniform_dist(engine_);
		}
};

}

#endif //HELLO_WORLD_RANDOM_H
