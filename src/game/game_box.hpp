#pragma once

#include "collision_helper.hpp"
#include "solid_shapes.hpp"
#include "ball.hpp"
#include "racket.hpp"
#include "brick.hpp"
#include "common.hpp"
#include <vector>
#include <cmath>
#include <tuple>

class GameBox{
    private:
        Position2D position;
        float width, height;

        std::vector<Ball> balls;
        Racket racket;
        std::vector<Brick> bricks;
        std::vector<SolidInterface*> entities;
    public:
        GameBox(Position2D position, float width, float height, std::vector<Ball> balls, Racket racket, std::vector<SolidInterface*> entities): position{position}, width{width}, height{height}, balls{balls}, racket{racket}, entities{entities}{};

        Position2D getPosition() const;

        float getWidth() const;

        float getHeight() const;

        std::vector<Brick> getBricks() const;

        void addBrick(Brick brick);
        void removeBrick(Brick brick);

        std::vector<Ball> getBalls() const;

        Racket getRacket() const;

        std::vector<SolidInterface*> getEntities() const;

        void addEntity(SolidRectangle& entity);
        void addEntity(SolidCircle& entity);

        void removeEntity(SolidRectangle& entity);
        void removeEntity(SolidCircle& entity);

        bool tryMoveRacket(const Position2D& p);

        std::vector<bool> tryMoveBalls(const std::vector<Position2D>& p_vec);

        void checkCollisionWithWalls();

        std::vector<Brick> checkCollisionsWithRacketAndBricks();
};