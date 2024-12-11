#include "racket.hpp"

class Racket{
    private:
        Position2D position;
        float width, height;
        SolidCircle hitbox;
        float sensibility;
    public:
        Racket(Position2D position, float width, float height, float sensibility): position{position}, width{width}, height{height}, sensibility{sensibility}{};

        Position2D getPosition() {return position;}
        void setPosition(Position2D pos) {position = pos;}

        float getHeight() {return height;}
        float getWidth() {return width;}

        void setHeight(float h) {height = h;}
        void setWidth(float w) {width = w;}

        SolidRectangle getHitbox() {return hitbox;}

        float getSensibility() {return sensibility;}
        void setSensitivity(float s) {sensibility = s;}

        Position2D calculateCenterPosition(){
            float cx = getPosition().getX() + getWidth() / 2;
            float cy = getPosition().getY() + getHeight() / 2;
            return Position2D(cx, cy);
        }

        void moveToCoordinates(Position2D coord){
            // Move racket with its hitbox
            setPosition(coord);
            getHitbox().setPosition(coord);
        }
};