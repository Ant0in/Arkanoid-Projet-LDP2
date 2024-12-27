#pragma once

#include "../common.hpp"
#include <vector>
#include <cmath>

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
        ~SolidRectangle() = default;

        Position2D getPosition() const;
        void setPosition(const Position2D& pos);

        float getHeight() const;
        float getWidth() const;

        void setHeight(float h);
        void setWidth(float w);

        std::vector<Position2D> getCorners() const;

        bool isPointInSolid(const Position2D& point) const;

        Position2D getCenterPosition() const;

        bool operator==(const SolidInterface& other) const;
};


class SolidCircle: public SolidInterface{
    private:
        Position2D position;
        float radius;
    public:
        SolidCircle(const Position2D& position, float radius): position{position}, radius{radius}{}
        ~SolidCircle() = default;

        Position2D getPosition() const;
        void setPosition(const Position2D& pos);

        float getRadius() const;
        void setRadius(float radius);

        bool isPointInSolid(const Position2D& point) const;

        bool operator==(const SolidInterface& other) const;
};