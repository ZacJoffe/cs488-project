#include "Rng.h"

bool Rng::s_instantiated = false;

Rng::Rng() {
    if (!s_instantiated) {
        std::srand(std::time(nullptr));
    }

    s_instantiated = true;
}

double Rng::operator()() const {
    return std::rand() / static_cast<double>(RAND_MAX);
}

