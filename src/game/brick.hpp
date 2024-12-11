#include "solid_shapes.hpp"
#include "common.hpp"
#include <iostream>

class Brick{
    private:
        Position2D position;
        float width, height;
        BrickType btype;
        SolidCircle hitbox;
        int hp;
    public:
        Brick(Position2D position, float width, float height, BrickType btype);

        static int attributeBrickHpByType(BrickType btype);

        Position2D getPosition();
        void setPosition(Position2D pos);

        float getHeight();
        float getWidth();

        void setHeight(float h);
        void setWidth(float w);

        BrickType getBrickType();
        
        int getHP();
        void setHP(int v);

        SolidRectangle getHitbox();

        void moveToCoordinates(Position2D coord);

        void makeBrickLooseHP(int loss);

        bool isBroken();

        int getBrickValue();

        bool operator==(Brick other);
};