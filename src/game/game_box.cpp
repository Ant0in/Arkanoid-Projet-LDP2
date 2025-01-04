#include "game_box.hpp"

GameBox::~GameBox() {
    delete getRacket();
    for (auto ball : getBalls()) {
        delete ball;
    }
    for (auto brick : getBricks()) {
        delete brick;
    }
    for (auto bonus : getBonuses()) {
        delete bonus;
    }
}

SolidRectangle& GameBox::getHitbox() {
    return _hitbox;
}
const SolidRectangle& GameBox::getHitbox() const {
    return _hitbox;
}

Position2D GameBox::getPosition() const {
    return getHitbox().getPosition();
}

float GameBox::getWidth() const {
    return getHitbox().getWidth();
}
float GameBox::getHeight() const {
    return getHitbox().getHeight();
}

void GameBox::initializeWalls() {
    Position2D p = getPosition();
    float      w = getWidth();
    float      h = getHeight();

    _leftWall = SolidRectangle(
        Position2D(p.getX() - BOX_WALLS_THICKNESS, p.getY()), BOX_WALLS_THICKNESS, h);
    _rightWall = SolidRectangle(Position2D(p.getX() + w, p.getY()), BOX_WALLS_THICKNESS, h);
    _topWall =
        SolidRectangle(Position2D(p.getX() - BOX_WALLS_THICKNESS, p.getY() - BOX_WALLS_THICKNESS),
                       w + (2 * BOX_WALLS_THICKNESS),
                       BOX_WALLS_THICKNESS);
    _bottomWall = SolidRectangle(Position2D(p.getX(), p.getY() + h), w, BOX_WALLS_THICKNESS);
}

std::vector<BonusInterface*>& GameBox::getBonuses() {
    return _bonuses;
}

void GameBox::addBonus(BonusInterface* b) {
    getBonuses().push_back(b);
}

void GameBox::removeBonus(BonusInterface* b) {
    for (auto it = getBonuses().begin(); it != getBonuses().end(); ++it) {
        if (*it == b) {
            getBonuses().erase(it);
            break;
        }
    }
}

std::vector<Brick*>& GameBox::getBricks() {
    return _bricks;
}

void GameBox::addBrick(Brick* brick) {
    getBricks().push_back(brick);
}

void GameBox::removeBrick(Brick* brick) {
    for (auto it = getBricks().begin(); it != getBricks().end(); ++it) {
        if (*it == brick) {
            getBricks().erase(it);
            break;
        }
    }
}

std::vector<Ball*>& GameBox::getBalls() {
    return _balls;
}
bool GameBox::isBallVectorEmpty() {
    return getBalls().size() == 0;
}
bool GameBox::doesPlayerHaveMultipleBalls() {
    return getBalls().size() > 1;
}

void GameBox::addBall(Ball* b) {
    getBalls().push_back(b);
}

void GameBox::removeBall(Ball* b) {
    for (auto it = getBalls().begin(); it != getBalls().end(); ++it) {
        if (*it == b) {
            getBalls().erase(it);
            break;
        }
    }
}

int GameBox::getFrameCount() {
    return _frameCount;
}
void GameBox::setFrameCount(int fc) {
    _frameCount = fc;
}
void GameBox::incrementFrameCount(int incr) {
    setFrameCount(getFrameCount() + incr);
}

Racket* GameBox::getRacket() const {
    return _racket;
}
void GameBox::setRacket(Racket* r) {
    if (_racket) {
        delete _racket;
    }
    _racket = r;
}

SolidRectangle& GameBox::getLeftWall() {
    return _leftWall;
}
SolidRectangle& GameBox::getRightWall() {
    return _rightWall;
}
SolidRectangle& GameBox::getTopWall() {
    return _topWall;
}
SolidRectangle& GameBox::getBottomWall() {
    return _bottomWall;
}

bool GameBox::isPositionOutOfBounds(const Position2D& pos) const {
    // checks if position in GameBox, if not -> returns true
    bool isPositionContaintedInGameBox = getHitbox().isPointInSolid(pos);
    return (!isPositionContaintedInGameBox);
}

bool GameBox::isObjectOutOfBounds(const SolidInterface& object) const {
    // checks if object is colliding with  gamebox, if not -> returns true
    bool outOfBounds = (!CollisionHelper::isColliding(getHitbox(), object));
    return outOfBounds;
}

WallType GameBox::isObjectCollidingWithWalls(const SolidInterface& object) {
    if (CollisionHelper::isColliding(object, getLeftWall())) {
        return WallType::LEFT;
    } else if (CollisionHelper::isColliding(object, getRightWall())) {
        return WallType::RIGHT;
    } else if (CollisionHelper::isColliding(object, getTopWall())) {
        return WallType::TOP;
    } else if (CollisionHelper::isColliding(object, getBottomWall())) {
        return WallType::BOTTOM;
    } else {
        return WallType::NONE;
    }
}

bool GameBox::tryMoveRacket(const Position2D& p) {
    Racket* rk   = getRacket();
    Racket  temp = Racket(p, rk->getWidth(), rk->getHeight(), rk->getSensibility());

    if (isObjectCollidingWithWalls(temp.getHitbox()) == WallType::NONE) {
        getRacket()->setPosition(p);
        return true;
    } else {
        return false;
    }
}

void GameBox::resizeRacket(float factor) {
    Racket* rk   = getRacket();
    Racket* temp = new Racket(
        rk->getPosition(), rk->getWidth() * factor, rk->getHeight(), rk->getSensibility());

    WallType collisionWithWall = isObjectCollidingWithWalls(temp->getHitbox());

    // first case : no collision, replace racket by temp
    if (collisionWithWall == WallType::NONE) {
        setRacket(temp);
    }
    // second case : racket too big to fit screen -> pass
    else if (temp->getWidth() > getWidth()) {
    }
    // third case: collision with 1 wall
    else {
        if (collisionWithWall == WallType::LEFT) {
            temp->setPosition(Position2D(getPosition().getX(), temp->getPosition().getY()));
        } else if (collisionWithWall == WallType::RIGHT) {
            temp->setPosition(Position2D(getPosition().getX() + getWidth() - temp->getWidth(),
                                         temp->getPosition().getY()));
        } else {
            std::cerr << "Not Implemented Error" << std::endl;
        }
        setRacket(temp);
    }
}

std::vector<bool> GameBox::tryMoveBalls() {
    std::vector<Ball*> balls = getBalls();
    std::vector<bool>  could_move(balls.size(), false);

    for (size_t idx = 0; idx < balls.size(); ++idx) {
        Ball* ball = balls[idx];

        Position2D np   = ball->calculateNewPosition();
        Ball       temp = Ball(np, ball->getRadius(), ball->getSpeed());

        WallType wallCollision = isObjectCollidingWithWalls(temp.getHitbox());

        if (wallCollision == WallType::NONE) {
            ball->setCenterPosition(np);
            could_move[idx] = true;
        } else {
            could_move[idx] = false;
            auto [vx, vy]   = ball->getVelocity();

            switch (wallCollision) {
                case WallType::LEFT:
                    ball->setVelocity(-vx, vy);
                    break;
                case WallType::RIGHT:
                    ball->setVelocity(-vx, vy);
                    break;
                case WallType::TOP:
                    ball->setVelocity(vx, -vy);
                    break;
                case WallType::BOTTOM:
                    ball->setAlive(false);
                    break;
                default:
                    break;
            }
        }
    }
    return could_move;
}

bool GameBox::isWin() {
    // If any not gold bricks are left, we didn't win yet
    for (Brick* brick : getBricks()) {
        if ((!brick->isBroken()) && (brick->getBrickType() != BrickType::GOLD)) {
            return false;
        }
    }
    return true;
}
