#pragma once

#include "Templates/SignalReceiver.hpp"
#include "Shaders/Shader.hpp"
#include "Entity/Hitbox.hpp"
#include "AttributesParser.hpp"
#include "Globals.hpp"

using namespace Globals;
using namespace signals;

class Entity : public SignalReceiver {
    protected:
        int error;

        Coord coords;
        Shader shader;
        Hitbox hitbox;
        AttributesParser attributesParser;

        float width = 0.0f;
        long lastUpdateTime;

        Coord velocity;

    public:
        Entity();
        int getErrorCode();

        void activateShader();
        void draw(Coord);

        void setCoords(Coord);
        Coord getCoords();
        void translate(Coord);

        Hitbox getHitbox();
};