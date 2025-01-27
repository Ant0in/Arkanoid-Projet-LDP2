#pragma once

#include <cmath>
#include <tuple>
#include <vector>

#include "ball.hpp"
#include "bonus.hpp"
#include "brick.hpp"
#include "collision_helper.hpp"
#include "common.hpp"
#include "laser.hpp"
#include "racket.hpp"
#include "solid_shapes.hpp"


class Brick;
class BonusInterface;

class GameBox {
   private:
    Racket*                      _racket;
    std::vector<Ball*>           _balls;
    SolidRectangle               _hitbox;
    std::vector<Brick*>          _bricks;
    std::vector<BonusInterface*> _bonuses;
    std::vector<Laser*>          _lasers;
    int                          _frameCount;

    // Walls
    SolidRectangle _leftWall;
    SolidRectangle _rightWall;
    SolidRectangle _topWall;
    SolidRectangle _bottomWall;

   public:
    GameBox(Position2D                   position,
            float                        width,
            float                        height,
            Racket*                      racket,
            std::vector<Ball*>           balls   = {},
            std::vector<Brick*>          bricks  = {},
            std::vector<BonusInterface*> bonuses = {},
            std::vector<Laser*>          lasers  = {})
        :

          _racket{racket},
          _balls{balls},
          _hitbox{SolidRectangle(position, height, width)},
          _bricks{bricks},
          _bonuses{bonuses},
          _lasers{lasers},
          _frameCount{0},
          // walls
          _leftWall{SolidRectangle(DEFAULT_CORNER_POS, 0, 0)},
          _rightWall{SolidRectangle(DEFAULT_CORNER_POS, 0, 0)},
          _topWall{SolidRectangle(DEFAULT_CORNER_POS, 0, 0)},
          _bottomWall{SolidRectangle(DEFAULT_CORNER_POS, 0, 0)} {
        initializeWalls();
    };

    ~GameBox();

    SolidRectangle&       getHitbox();
    const SolidRectangle& getHitbox() const;

    Position2D getPosition() const;

    float getWidth() const;

    float getHeight() const;

    void initializeWalls();

    std::vector<BonusInterface*>& getBonuses();
    void                          addBonus(BonusInterface* b);
    void                          removeBonus(BonusInterface* b);

    std::vector<Laser*>& getLasers();
    void                 addLaser(Laser* laser);
    void                 removeLaser(Laser* laser);

    std::vector<Brick*>& getBricks();
    void                 addBrick(Brick* brick);
    void                 removeBrick(Brick* brick);

    std::vector<Ball*>& getBalls();
    bool                isBallVectorEmpty();
    bool                doesPlayerHaveMultipleBalls();
    void                addBall(Ball* b);
    void                removeBall(Ball* b);

    int  getFrameCount();
    void setFrameCount(int fc);
    void incrementFrameCount(int incr);

    Racket* getRacket() const;
    void    setRacket(Racket* r);

    SolidRectangle& getLeftWall();
    SolidRectangle& getRightWall();
    SolidRectangle& getTopWall();
    SolidRectangle& getBottomWall();

    bool isPositionOutOfBounds(const Position2D& pos) const;
    bool isObjectOutOfBounds(const SolidInterface& object) const;

    WallType isObjectCollidingWithWalls(const SolidInterface& object);

    bool tryMoveRacket(const Position2D& p);
    void resizeRacket(float factor);

    std::vector<bool> tryMoveBalls();

    void tryMoveLasers();

    bool isWin();
};