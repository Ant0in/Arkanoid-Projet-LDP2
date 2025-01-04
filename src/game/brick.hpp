#pragma once

#include <iostream>

#include "../common.hpp"
#include "../physics/solid_shapes.hpp"
#include "bonus.hpp"


class BonusInterface;

class Brick {
   private:
    BrickType _btype;
    BonusInterface* _bonus;
    SolidRectangle _hitbox;
    int _hp;

   public:
    Brick(const Position2D& position, float width, float height, const BrickType& btype,
          BonusInterface* bonus = nullptr)
        : _btype{btype},
          _bonus{bonus},
          _hitbox{SolidRectangle(position, width, height)},
          _hp{getBrickHpByType(btype)} {};

    ~Brick();

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