#pragma once

#include "../physics/solid_shapes.hpp"
#include "../common.hpp"

class Racket{

    private:

        SolidRectangle _hitbox;
        float _sensibility;

    public:

        Racket(const Position2D& position, float width, float height, float sensibility):
            _hitbox{SolidRectangle(position, width, height)},
            _sensibility{sensibility} {}

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

        Position2D calculateNewPosition(const Action& action);
};