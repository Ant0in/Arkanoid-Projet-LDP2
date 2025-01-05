#pragma once

#include "common.hpp"
#include "racket.hpp"
#include "solid_shapes.hpp"


class Laser {
   private:
    SolidRectangle _hitbox;
    float          _speed;

   public:
    Laser(const Position2D& pos          = DEFAULT_SPAWN_POSITION,
          float             laser_width  = LASER_WIDTH,
          float             laser_height = LASER_HEIGHT,
          float             laser_speed  = LASER_SPEED)
        : _hitbox{SolidRectangle(pos, laser_width, laser_height)}, _speed{laser_speed} {
    }

    ~Laser() = default;

    SolidRectangle&       getHitbox();
    const SolidRectangle& getHitbox() const;

    Position2D getPosition() const;
    void       setPosition(const Position2D& p);
    float      getSpeed();
    Position2D calculateNewPosition();

    void spawnLaser(Racket* r);
    bool operator==(Laser* other);
};