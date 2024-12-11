#include "ball.hpp"

class Ball{
    private:
        Position2D center;
        float radius;
        SolidCircle hitbox = SolidCircle(center, radius);

        float speed;
        float x_velocity = 0.0;
        float y_velocity = 1.0;
    public:
        Ball(Position2D center, float radius, float speed): center{center}, radius{radius}, speed{speed}{}
        
        Position2D getCenterPosition() {return center;}
        void setCenterPosition(Position2D pos) {center = pos;}

        float getRadius() {return radius;}
        void setRadius(float r) {radius = r;}

        SolidCircle getHitbox() {return hitbox;}

        std::tuple<float, float> getVelocity() {return std::make_tuple(x_velocity, y_velocity);}
        void setVelocity(float xv = 0.0, float yv = 0.0) {x_velocity = xv; y_velocity = yv;}

        float getSpeed() {return speed;}
        void setSpeed(float s) {speed = s;}

        void moveToCoordinates(Position2D coord) {
            // Move the ball with its hitbox
            setCenterPosition(coord);
            getHitbox().setPosition(coord);
        }
};