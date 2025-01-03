#pragma once

#include "../physics/solid_shapes.hpp"
#include "../common.hpp"
#include <tuple>

class Ball{

    private:
        
        SolidCircle _hitbox;
        float _speed;
        float _x_velocity;
        float _y_velocity;
        bool _is_alive;

    public:

        Ball(const Position2D& center, float radius = BALL_RADIUS, float speed = BALL_SPEED):
            _hitbox{SolidCircle(center, radius)},
            _speed{speed},
            _x_velocity{0.0},
            _y_velocity{1.0},
            _is_alive{true} {}

        ~Ball() = default;

        Position2D getCenterPosition() const;
        void setCenterPosition(const Position2D& pos);

        float getRadius() const;
        void setRadius(float r);

        SolidCircle& getHitbox();
        const SolidCircle& getHitbox() const;

        std::tuple<float, float> getVelocity() const;
        void setVelocity(float xv = 0.0, float yv = 0.0);

        float getSpeed() const;
        void setSpeed(float s);

        bool isAlive() const;
        void setAlive(bool flag);

        Position2D calculateNewPosition();

        bool operator==(Ball* other) const;
};