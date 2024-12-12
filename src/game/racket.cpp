#include "racket.hpp"

class Racket{
    private:
        Position2D position;
        float width, height;
        SolidRectangle hitbox;
        float sensibility;
    public:
        Racket(const Position2D& position, float width, float height, float sensibility): position{position}, width{width}, height{height}, sensibility{sensibility}, hitbox{SolidRectangle(position, width, height)}{}

        Position2D getPosition() const {return position;}
        void setPosition(const Position2D& pos) {position = pos;}

        float getHeight() const {return height;}
        float getWidth() const {return width;}

        void setHeight(float h) {height = h;}
        void setWidth(float w) {width = w;}

        SolidRectangle& getHitbox() {return hitbox;}
        const SolidRectangle& getHitbox() const {return hitbox;}


        float getSensibility() const {return sensibility;}
        void setSensitivity(float s) {sensibility = s;}

        Position2D calculateCenterPosition() const {
            float cx = getPosition().getX() + getWidth() / 2;
            float cy = getPosition().getY() + getHeight() / 2;
            return Position2D(cx, cy);
        }

        void moveToCoordinates(const Position2D& coord){
            // Move racket with its hitbox
            setPosition(coord);
            getHitbox().setPosition(coord);
        }
};