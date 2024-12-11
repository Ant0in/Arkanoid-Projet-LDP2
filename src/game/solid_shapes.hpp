#include "common.hpp"
#include <vector>
#include <cmath>

class SolidInterface{
    public:
        virtual bool isPointInSolid();
};


class SolidRectangle: SolidInterface{
    private:
        Position2D position;
        float width, height;
    public:
        SolidRectangle(Position2D position, float width, float height);

        Position2D getPosition();
        void setPosition(Position2D pos);

        float getHeight();
        float getWidth();

        void setHeight(float h);
        void setWidth(float w);

        std::vector<Position2D> getCorners();

        bool isPointInSolid(Position2D point);
};


class SolidCircle: SolidInterface{
    private:
        Position2D position;
        float radius;
    public:
        SolidCircle(Position2D position, float radius);

        Position2D getPosition();
        void setPosition(Position2D pos);

        float getRadius();
        void setRadius(float radius);

        bool isPointInSolid(Position2D point);
};