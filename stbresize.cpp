#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <cstdlib>
#include <iostream>

int main(int argc, char** argv)
{
    if (argc != 5) {
        std::cout << "usage: resize in.png out.png width height\n";
        return 1;
    }

    int w,h,c;
    unsigned char* img = stbi_load(argv[1], &w, &h, &c, 0);
    if (!img) return 1;

    int nw = atoi(argv[3]);
    int nh = atoi(argv[4]);

    unsigned char* out = (unsigned char*)malloc(nw * nh * c);

    stbir_resize_uint8(img, w, h, 0,
                       out, nw, nh, 0, c);

    stbi_write_png(argv[2], nw, nh, c, out, nw * c);

    stbi_image_free(img);
    free(out);
}