#include "solid_shapes.hpp"
#include "common.hpp"

class Racket{
    private:
        Position2D position;
        float width, height;
        SolidCircle hitbox;
        float sensibility;
    public:
        Racket(Position2D position, float width, float height, float sensibility);

        Position2D getPosition();
        void setPosition(Position2D pos);

        float getHeight();
        float getWidth();

        void setHeight(float h);
        void setWidth(float w);

        SolidRectangle getHitbox();

        float getSensibility();
        void setSensitivity(float s);

        Position2D calculateCenterPosition();

        void moveToCoordinates(Position2D coord);
};