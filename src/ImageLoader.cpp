#include "ImageLoader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "include/stb/stb_image.h"

ImageLoader::ImageLoader() {}

unsigned char * ImageLoader::load(const std::string & filename, int * x, int * y, int * n) const {
    // force stbi to load image with origin coordinate being on bottom left of image
    stbi_set_flip_vertically_on_load(1);
    return stbi_load(filename.c_str(), x, y, n, 0);
}

void ImageLoader::free(unsigned char * data) {
    stbi_image_free(data);
}

