#include "solid_shapes.hpp"


class SolidInterface{
    public:
        virtual bool isPointInSolid() = 0;
};


class SolidRectangle: SolidInterface{
    private:
        Position2D position;
        float width, height;
    public:
        SolidRectangle(Position2D position, float width, float height):position{position}, width{width}, height{height}{}

        Position2D getPosition() {return position;}
        void setPosition(Position2D pos) {position = pos;}

        float getHeight() {return height;}
        float getWidth() {return width;}

        void setHeight(float h) {height = h;}
        void setWidth(float w) {width = w;}

        std::vector<Position2D> getCorners(){
            Position2D top_left = getPosition();
            Position2D top_right = Position2D(top_left.getX() + getWidth(), top_left.getY());
            Position2D bottom_left = Position2D(top_left.getX(), top_left.getY() - getHeight());
            Position2D bottom_right = Position2D(top_left.getX() + getWidth(), top_left.getY() - getHeight());
            return {top_left, top_right, bottom_left, bottom_right};
        }

        bool isPointInSolid(Position2D point){
            Position2D top_left = getPosition();
            return (
                top_left.getX() <= point.getX() && point.getX() <= (top_left.getX() + getWidth()) &&
                top_left.getY() <= point.getY() && point.getY() <= (top_left.getY() + getHeight())
            );
        }
};


class SolidCircle: SolidInterface{
    private:
        Position2D position;
        float radius;
    public:
        SolidCircle(Position2D position, float radius): position{position}, radius{radius}{}

        Position2D getPosition() {return position;}
        void setPosition(Position2D pos) {position = pos;}

        float getRadius() {return radius;};
        void setRadius(float rad) {radius = rad;}

        bool isPointInSolid(Position2D point){
            Position2D center = getPosition();
            float distance_squared = pow((point.getX() - center.getX()), 2) + pow((point.getY() - center.getY()), 2);
            return distance_squared <= pow(getRadius(), 2);
        }
};