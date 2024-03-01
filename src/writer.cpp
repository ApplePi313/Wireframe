#include "Writer.hpp"

Writer::Writer() {
    if(FT_Init_FreeType(&ft)) {
        fprintf(stderr, "Could not init freetype library\n");
        return;
    }

    if(FT_New_Face(ft, "./src/Fonts/Iosevka-Regular.ttf", 0, &face)) {
        fprintf(stderr, "Could not open font\n");
        return;
    }
}
