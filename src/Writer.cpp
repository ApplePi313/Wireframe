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

void Writer::write(const char* msg) {
    // error = FT_Set_Char_Size(
    //         face,    /* handle to face object         */
    //         0,       /* char_width in 1/64 of points  */
    //         16*64,   /* char_height in 1/64 of points */
    //         300,     /* horizontal device resolution  */
    //         300 );   /* vertical device resolution    */

    // for (const char* p = msg; *p; p++) {
    //     glyph_index = FT_Get_Char_Index( face, *p );
    //     error = FT_Load_Glyph(
    //       face,          /* handle to face object */
    //       glyph_index,   /* glyph index           */
    //       load_flags );  /* load flags, see below */

    //     error = FT_Render_Glyph(face->glyph,   /* glyph slot  */
    //                             FT_RENDER_MODE_NORMAL ); /* render mode */
    // }
}