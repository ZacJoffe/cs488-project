#pragma once

#include <string>

class ImageLoader {
public:
    static ImageLoader & getInstance();
    ImageLoader(ImageLoader const &) = delete;
    void operator=(ImageLoader const &) = delete;

    void setFlipVertically(bool flip) const;
    unsigned char * load(const std::string & filename, int * x, int * y, int * n) const;
    void free(unsigned char * data) const;

private:
    ImageLoader();
};

