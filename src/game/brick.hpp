#pragma once

#include "../physics/solid_shapes.hpp"
#include "../common.hpp"
#include "bonus.hpp"
#include <iostream>

class BonusInterface;

class Brick{
    private:
        Position2D position;
        float width, height;
        BrickType btype;
        BonusInterface* bonus;
        SolidRectangle hitbox;
        int hp;
    public:
        Brick(const Position2D& position, float width, float height, const BrickType& btype, BonusInterface* bonus = nullptr): position{position}, width{width}, height{height}, btype{btype}, bonus{bonus}, hitbox{SolidRectangle(position, width, height)}, hp{getBrickHpByType(btype)}{};
        ~Brick() = default;
        
        static int getBrickHpByType(const BrickType& btype);

        SolidRectangle& getHitbox();
        const SolidRectangle& getHitbox() const;

        Position2D getPosition() const;
        void setPosition(const Position2D& pos);

        float getHeight() const;
        float getWidth() const;

        void setHeight(float h);
        void setWidth(float w);

        BrickType getBrickType() const;
        
        int getHP() const;
        void setHP(int v);

        BonusInterface* getBonus() const;
        void setBonus(BonusInterface* b);

        bool doesBrickContainBonus() const;

        Position2D getCenterPosition() const;

        void makeBrickLoseHP(int loss);

        bool isBroken() const;

        int getBrickValue();

        bool operator==(Brick* other) const;
};