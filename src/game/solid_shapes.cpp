#include "solid_shapes.hpp"


class SolidInterface{
    public:
        virtual ~SolidInterface() = default;
        virtual bool isPointInSolid(const Position2D& point) const = 0;
        virtual bool operator==(const SolidInterface& other) const = 0;
};


class SolidRectangle: public SolidInterface{
    private:
        Position2D position;
        float width, height;
    public:
        SolidRectangle(const Position2D& position, float width, float height):position{position}, width{width}, height{height}{}

        Position2D getPosition() const {return position;}
        void setPosition(const Position2D& pos) {position = pos;}

        float getHeight() const {return height;}
        float getWidth() const {return width;}

        void setHeight(float h) {height = h;}
        void setWidth(float w) {width = w;}

        std::vector<Position2D> getCorners() const {
            Position2D top_left = getPosition();
            Position2D top_right = Position2D(top_left.getX() + getWidth(), top_left.getY());
            Position2D bottom_left = Position2D(top_left.getX(), top_left.getY() - getHeight());
            Position2D bottom_right = Position2D(top_left.getX() + getWidth(), top_left.getY() - getHeight());
            return {top_left, top_right, bottom_left, bottom_right};
        }

        bool isPointInSolid(const Position2D& point) const{
            Position2D top_left = getPosition();
            return (
                top_left.getX() <= point.getX() && point.getX() <= (top_left.getX() + getWidth()) &&
                top_left.getY() <= point.getY() && point.getY() <= (top_left.getY() + getHeight())
            );
        }

        bool operator==(const SolidInterface& other) const {
            const SolidRectangle* rect = dynamic_cast<const SolidRectangle*>(&other);
            if (!rect) return false;
            return (getPosition() == rect->getPosition()) && 
                (getWidth() == rect->getWidth()) && 
                (getHeight() == rect->getHeight());
        }
};


class SolidCircle: public SolidInterface{
    private:
        Position2D position;
        float radius;
    public:
        SolidCircle(const Position2D& position, float radius): position{position}, radius{radius}{}

        Position2D getPosition() const {return position;}
        void setPosition(const Position2D& pos) {position = pos;}

        float getRadius() const {return radius;};
        void setRadius(float rad) {radius = rad;}

        bool isPointInSolid(const Position2D& point) const {
            Position2D center = getPosition();
            float distance_squared = pow((point.getX() - center.getX()), 2) + pow((point.getY() - center.getY()), 2);
            return distance_squared <= pow(getRadius(), 2);
        }

        bool operator==(const SolidInterface& other) const {
            const SolidCircle* circle = dynamic_cast<const SolidCircle*>(&other);
            if (!circle) return false;
            return (getPosition() == circle->getPosition()) && (getRadius() == circle->getRadius());
        }
};