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

        Position2D getCenterPosition();
        void setCenterPosition(Position2D pos);

        float getRadius();
        void setRadius(float r);

        SolidCircle getHitbox();

        std::tuple<float, float> getVelocity();
        void setVelocity(float xv = 0.0, float yv = 0.0);

        float getSpeed();
        void setSpeed(float s);

        void moveToCoordinates(Position2D coord);
};