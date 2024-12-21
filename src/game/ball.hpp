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
        bool is_alive;
    public:
        Ball(const Position2D& center, float radius, float speed = 1.0): center{center}, radius{radius}, speed{speed}, hitbox{SolidCircle(center, radius)}, x_velocity{0.0}, y_velocity{1.0}, is_alive{true}{}
        ~Ball() = default;

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

        bool isAlive() const;
        void setAlive(bool flag);

        Position2D calculateNewPosition();

        bool operator==(const Ball& other) const;
};