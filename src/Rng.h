#pragma once

#include <cstdlib>
#include <ctime>

class Rng {
public:
    Rng();
    double operator()() const; // returns double between 0 and 1

private:
    static bool s_instantiated;
};

