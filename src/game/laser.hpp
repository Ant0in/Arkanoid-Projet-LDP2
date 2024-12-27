#pragma once

#include "racket.hpp"
#include "../physics/solid_shapes.hpp"
#include "../common.hpp"

class Laser{
    private:
        Position2D pos;
        SolidRectangle hitbox;

    public:
        Laser(const Position2D& pos): pos{pos}, hitbox{SolidRectangle(pos, LASER_THICKNESS, LASER_LENGTH)}{}
        ~Laser() = default;

        SolidRectangle& getHitbox();
        const SolidRectangle& getHitbox() const;

        Position2D getPosition() const;
        void setPosition(const Position2D& p);

        void spawnLaser(const Racket& r);
};