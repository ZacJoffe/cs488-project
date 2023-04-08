#include "ImageLoader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "include/stb/stb_image.h"

ImageLoader & ImageLoader::getInstance() {
    static ImageLoader instance;
    return instance;
}

unsigned char * ImageLoader::load(const std::string & filename, int * x, int * y, int * n) const {
    return stbi_load(filename.c_str(), x, y, n, 0);
}

void ImageLoader::setFlipVertically(bool flip) const {
    stbi_set_flip_vertically_on_load(flip);
}

void ImageLoader::free(unsigned char * data) const {
    stbi_image_free(data);
}

ImageLoader::ImageLoader() {}

