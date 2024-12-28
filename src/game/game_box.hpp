#pragma once

#include "../physics/collision_helper.hpp"
#include "../physics/solid_shapes.hpp"
#include "ball.hpp"
#include "racket.hpp"
#include "bonus.hpp"
#include "brick.hpp"
#include "../common.hpp"
#include <vector>
#include <cmath>
#include <tuple>

class Brick;
class BonusInterface;

class GameBox{
    private:
        Position2D position;
        float width, height;

        std::vector<Ball*> balls;
        Racket* racket;
        SolidRectangle hitbox;
        std::vector<Brick*> bricks;
        std::vector<BonusInterface*> bonuses;

        // Walls
        SolidRectangle leftWall;
        SolidRectangle rightWall;
        SolidRectangle topWall;
        SolidRectangle bottomWall;

    public:
        GameBox(Position2D position, float width, float height, std::vector<Ball*> balls, Racket* racket,  std::vector<Brick*> bricks = {}, std::vector<BonusInterface*> bonuses = {})
        : position{position}, width{width}, height{height}, balls{balls}, racket{racket}, hitbox{SolidRectangle(position, height, width)}, bricks{bricks}, bonuses{bonuses}, leftWall{SolidRectangle(Position2D(0, 0), 0, 0)}, rightWall{SolidRectangle(Position2D(0, 0), 0, 0)}, topWall{SolidRectangle(Position2D(0, 0), 0, 0)}, bottomWall{SolidRectangle(Position2D(0, 0), 0, 0)}{initializeWalls();};
        ~GameBox() = default;

        SolidRectangle& getHitbox();
        const SolidRectangle& getHitbox() const;

        Position2D getPosition() const;

        float getWidth() const;

        float getHeight() const;

        void initializeWalls();

        std::vector<BonusInterface*> getBonuses() const;
        void addBonus(BonusInterface* b);
        void removeBonus(BonusInterface* b);

        std::vector<Brick*>& getBricks();
        void addBrick(Brick* brick);
        void removeBrick(Brick* brick);

        std::vector<Ball*> getBalls() const;
        bool isBallVectorEmpty() const;
        bool doesPlayerHaveMultipleBalls() const;
        void addBall(Ball* b);
        void removeBall(Ball* b);

        Racket* getRacket() const;
        void setRacket(Racket* r);

        SolidRectangle& getLeftWall();
        SolidRectangle& getRightWall();
        SolidRectangle& getTopWall();
        SolidRectangle& getBottomWall();

        bool isPositionOutOfBounds(const Position2D& pos) const;

        bool isObjectOutOfBounds(const Racket& object) const;
        bool isObjectOutOfBounds(const Ball& object) const;
        bool isObjectOutOfBounds(const BonusInterface& object) const;

        WallType isObjectCollidingWithWalls(const Racket& object);
        WallType isObjectCollidingWithWalls(const Ball& object);
        WallType isObjectCollidingWithWalls(const BonusInterface& object);

        bool tryMoveRacket(const Position2D& p);
        void resizeRacket(float factor);

        std::vector<bool> tryMoveBalls();

        bool isWin();
};