#pragma once
#include <iostream>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Writer {
    FT_Library ft;
    FT_Face face;

    public:
        Writer();
};