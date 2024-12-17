#pragma once

#include "solid_shapes.hpp"
#include "common.hpp"
#include <iostream>

class Brick{
    private:
        Position2D position;
        float width, height;
        BrickType btype;
        SolidRectangle hitbox;
        int hp;
    public:
        Brick(const Position2D& position, float width, float height, BrickType btype): position{position}, width{width}, height{height}, btype{btype}, hitbox{SolidRectangle(position, width, height)}, hp{attributeBrickHpByType(btype)}{};

        static int attributeBrickHpByType(BrickType btype);

        Position2D getPosition() const;
        void setPosition(const Position2D& pos);

        float getHeight() const;
        float getWidth() const;

        void setHeight(float h);
        void setWidth(float w);

        BrickType getBrickType() const;
        
        int getHP() const;
        void setHP(int v);

        SolidRectangle& getHitbox();
        const SolidRectangle& getHitbox() const;

        void moveToCoordinates(const Position2D& coord);

        void makeBrickLoseHP(int loss);

        bool isBroken() const;

        int getBrickValue();

        bool operator==(const Brick& other) const;
};