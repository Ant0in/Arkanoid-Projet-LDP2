#pragma once

#include "../physics/solid_shapes.hpp"
#include "../common.hpp"

class Racket{
    private:
        Position2D position;
        float width, height;
        SolidRectangle hitbox;
        float sensibility;
    public:
        Racket(const Position2D& position, float width, float height, float sensibility): position{position}, width{width}, height{height}, hitbox{SolidRectangle(position, width, height)}, sensibility{sensibility}{}
        ~Racket() = default;
        
        Position2D getPosition() const;
        void setPosition(const Position2D& pos);

        float getHeight() const;
        float getWidth() const;

        void setHeight(float h);
        void setWidth(float w);

        SolidRectangle& getHitbox();
        const SolidRectangle& getHitbox() const;

        float getSensibility() const;
        void setSensitivity(float s);

        Position2D getCenterPosition() const;

        Position2D calculateNewPosition(Action action);
};