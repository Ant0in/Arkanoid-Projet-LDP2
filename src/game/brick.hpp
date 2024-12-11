#include "solid_shapes.hpp"
#include "common.hpp"

class Brick{
    private:
        Position2D position;
        float width, height;
        BrickType btype;
        SolidCircle hitbox;
        float hp;

};