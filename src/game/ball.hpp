#pragma once

#include "solid_shapes.hpp"
#include "common.hpp"
#include <tuple>

class Ball{
    private:
        Position2D center;
        float radius;
        SolidCircle hitbox;

        float speed;
        float x_velocity;
        float y_velocity;
    public:
        Ball(Position2D center, float radius, float speed);

        Position2D getCenterPosition() const;
        void setCenterPosition(Position2D pos);

        float getRadius() const;
        void setRadius(float r);

        SolidCircle& getHitbox();
        const SolidCircle& getHitbox() const;

        std::tuple<float, float> getVelocity() const;
        void setVelocity(float xv = 0.0, float yv = 0.0);

        float getSpeed() const;
        void setSpeed(float s);

        void moveToCoordinates(const Position2D& coord);
};