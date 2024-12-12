#include "ball.hpp"

class Ball{
    private:
        Position2D center;
        float radius;
        SolidCircle hitbox;

        float speed;
        float x_velocity;
        float y_velocity;
    public:
        Ball(const Position2D& center, float radius, float speed): center{center}, radius{radius}, speed{speed}, hitbox{SolidCircle(center, radius)}, x_velocity{0.0}, y_velocity{1.0}{}
        
        Position2D getCenterPosition() const {return center;}
        void setCenterPosition(Position2D pos) {center = pos;}

        float getRadius() const {return radius;}
        void setRadius(float r) {radius = r;}

        SolidCircle& getHitbox() {return hitbox;}
        const SolidCircle& getHitbox() const {return hitbox;}

        std::tuple<float, float> getVelocity() const {return std::make_tuple(x_velocity, y_velocity);}
        void setVelocity(float xv = 0.0, float yv = 0.0) {x_velocity = xv; y_velocity = yv;}

        float getSpeed() const {return speed;}
        void setSpeed(float s) {speed = s;}

        void moveToCoordinates(const Position2D& coord) {
            // Move the ball with its hitbox
            setCenterPosition(coord);
            getHitbox().setPosition(coord);
        }
};