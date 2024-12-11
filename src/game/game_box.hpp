#include "collision_helper.hpp"
#include "solid_shapes.hpp"
#include "ball.hpp"
#include "racket.hpp"
#include "brick.hpp"
#include "common.hpp"
#include <vector>
#include <cmath>

class GameBox{
    private:
        Position2D position;
        float width, height;

        std::vector<Ball> balls;
        Racket racket;
        std::vector<Brick> bricks;
        std::vector<SolidInterface> entities;
    public:
        GameBox(Position2D position, float width, float height, std::vector<Ball> balls, Racket racket, std::vector<SolidInterface> entities);

        Position2D getPosition();

        float getWidth();

        float getHeight();

        std::vector<Brick> getBricks();

        void addBrick(Brick brick);
        void removeBrick(Brick brick);

        std::vector<Ball> getBalls();

        Racket getRacket();

        std::vector<SolidInterface> getEntities();

        void addEntity(SolidInterface entity);
        void removeEntity(SolidInterface entity);

        bool tryMoveRacket(Position2D p);

        std::vector<bool> tryMoveBalls(std::vector<Position2D> p_vec);

        void checkCollisionWithWalls();

        std::vector<Brick> checkCollisionsWithRaquetteAndBricks();
};