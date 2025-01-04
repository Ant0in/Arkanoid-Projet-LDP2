#pragma once

#include "../common.hpp"
#include "../physics/solid_shapes.hpp"
#include "racket.hpp"

class Laser {
   private:
    SolidRectangle _hitbox;

   public:
    Laser(const Position2D& pos) : _hitbox{SolidRectangle(pos, LASER_THICKNESS, LASER_LENGTH)} {
    }

    ~Laser() = default;

    SolidRectangle&       getHitbox();
    const SolidRectangle& getHitbox() const;

    Position2D getPosition() const;
    void       setPosition(const Position2D& p);

    void spawnLaser(const Racket& r);
};