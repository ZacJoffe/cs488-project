#pragma once

#include <string>

struct ImageLoader {
    ImageLoader();
    unsigned char * load(const std::string & filename, int * x, int * y, int * n) const;
    void free(unsigned char * data);
};

