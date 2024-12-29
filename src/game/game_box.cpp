#include "game_box.hpp"

SolidRectangle& GameBox::getHitbox(){return hitbox;}
const SolidRectangle& GameBox::getHitbox() const{return hitbox;}

Position2D GameBox::getPosition() const {return getHitbox().getPosition();}

float GameBox::getWidth() const {return getHitbox().getWidth();}
float GameBox::getHeight() const {return getHitbox().getHeight();}

void GameBox::initializeWalls(){
    Position2D p = getPosition();
    float w = getWidth();
    float h = getHeight();

    leftWall = SolidRectangle(Position2D(p.getX() - BOX_WALLS_THICKNESS, p.getY()), BOX_WALLS_THICKNESS, h);
    rightWall = SolidRectangle(Position2D(p.getX() + w, p.getY()), BOX_WALLS_THICKNESS, h);
    topWall = SolidRectangle(Position2D(p.getX(), p.getY() - BOX_WALLS_THICKNESS), w, BOX_WALLS_THICKNESS);
    bottomWall = SolidRectangle(Position2D(p.getX(), p.getY() + h), w, BOX_WALLS_THICKNESS);
}

std::vector<BonusInterface*> GameBox::getBonuses() const{
    return bonuses;
}

void GameBox::addBonus(BonusInterface* b){
    getBonuses().push_back(b);
}

void GameBox::removeBonus(BonusInterface* b){
    for (auto it = getBonuses().begin(); it != getBonuses().end(); ++it) {
        if (*it == b) { 
            getBonuses().erase(it); 
            break;
        }
    }
}

std::vector<Brick*>& GameBox::getBricks() {return bricks;}

void GameBox::addBrick(Brick* brick){
    bricks.push_back(brick);
}

void GameBox::removeBrick(Brick* brick){
    for (auto it = getBricks().begin(); it != getBricks().end(); ++it) {
        if (*it == brick) { 
            getBricks().erase(it); 
            break;
        }
    }
}

std::vector<Ball*> GameBox::getBalls() const {return balls;}
bool GameBox::isBallVectorEmpty() const {return getBalls().size() == 0;}
bool GameBox::doesPlayerHaveMultipleBalls() const {return getBalls().size() > 1;}

void GameBox::addBall(Ball* b){
    getBalls().push_back(b);
}
void GameBox::removeBall(Ball* b){
    for (auto it = getBalls().begin(); it != getBalls().end(); ++it) {
        // std::cout << (*it)->getCenterPosition().getX() << std::endl;
        if (*it == b) {
            std::cout<<"ICI";
            getBalls().erase(it); 
            break;
        }
    }
}

Racket* GameBox::getRacket() const {return racket;}
void GameBox::setRacket(Racket* r) {racket = r;}

SolidRectangle& GameBox::getLeftWall() {return leftWall;}
SolidRectangle& GameBox::getRightWall() {return rightWall;}
SolidRectangle& GameBox::getTopWall() {return topWall;}
SolidRectangle& GameBox::getBottomWall() {return bottomWall;}

bool GameBox::isPositionOutOfBounds(const Position2D& pos) const{
    // checks if position in GameBox, if not -> returns true
    bool isPositionContaintedInGameBox = getHitbox().isPointInSolid(pos);
    return (! isPositionContaintedInGameBox);
}

bool GameBox::isObjectOutOfBounds(const Racket& object) const{
    // checks if object is colliding with  gamebox, if not -> returns true
    bool outOfBounds = (! CollisionHelper::isColliding(getHitbox(), object.getHitbox()));
    return outOfBounds;
}
bool GameBox::isObjectOutOfBounds(const Ball& object) const{
    // checks if object is colliding with  gamebox, if not -> returns true
    bool outOfBounds = (! CollisionHelper::isColliding(getHitbox(), object.getHitbox()));
    return outOfBounds;
}
bool GameBox::isObjectOutOfBounds(const BonusInterface& object) const{
    // checks if object is colliding with  gamebox, if not -> returns true
    bool outOfBounds = (! CollisionHelper::isColliding(getHitbox(), object.getHitbox()));
    return outOfBounds;
}

WallType GameBox::isObjectCollidingWithWalls(const Racket& object) {
    // std::cout << getLeftWall().getPosition() << std::endl;
    if (CollisionHelper::isColliding(object.getHitbox(), getLeftWall())){std::cout<<"collision"<<std::endl; return WallType::LEFT;}
    else if (CollisionHelper::isColliding(object.getHitbox(), getRightWall())){std::cout<<"collision"<<std::endl; return WallType::RIGHT;}
    else if (CollisionHelper::isColliding(object.getHitbox(), getTopWall())){std::cout<<"collision"<<std::endl; return WallType::TOP;}
    else if (CollisionHelper::isColliding(object.getHitbox(), getBottomWall())){std::cout<<"collision"<<std::endl; return WallType::BOTTOM;}
    else {return WallType::NONE;}
}
WallType GameBox::isObjectCollidingWithWalls(const Ball& object) {
    if (CollisionHelper::isColliding(object.getHitbox(), getLeftWall())){return WallType::LEFT;}
    else if (CollisionHelper::isColliding(object.getHitbox(), getRightWall())){return WallType::RIGHT;}
    else if (CollisionHelper::isColliding(object.getHitbox(), getTopWall())){return WallType::TOP;}
    else if (CollisionHelper::isColliding(object.getHitbox(), getBottomWall())){return WallType::BOTTOM;}
    else {return WallType::NONE;}
}
WallType GameBox::isObjectCollidingWithWalls(const BonusInterface& object) {
    if (CollisionHelper::isColliding(object.getHitbox(), getLeftWall())){return WallType::LEFT;}
    else if (CollisionHelper::isColliding(object.getHitbox(), getRightWall())){return WallType::RIGHT;}
    else if (CollisionHelper::isColliding(object.getHitbox(), getTopWall())){return WallType::TOP;}
    else if (CollisionHelper::isColliding(object.getHitbox(), getBottomWall())){return WallType::BOTTOM;}
    else {return WallType::NONE;}
}

bool GameBox::tryMoveRacket(const Position2D& p){
    Racket* rk = getRacket();
    Racket temp = Racket(p, rk->getWidth(), rk->getHeight(), rk->getSensibility());

    if (isObjectCollidingWithWalls(temp) == WallType::NONE){
        getRacket()->setPosition(p);
        return true;
    }
    else {
        return false;
    }
}

void GameBox::resizeRacket(float factor){
    Racket* rk = getRacket();
    Racket* temp = new Racket(rk->getPosition(), rk->getWidth() * factor, rk->getHeight(), rk->getSensibility());

    WallType collisionWithWall = isObjectCollidingWithWalls(*temp);

    // first case : no collision, replace racket by temp
    if (collisionWithWall == WallType::NONE){setRacket(temp);}
    // second case : racket too big to fit screen -> pass
    else if (temp->getWidth() > getWidth()){}
    // third case: collision with 1 wall
    else {
        if (collisionWithWall == WallType::LEFT){
            temp->setPosition(Position2D(getPosition().getX(), temp->getPosition().getY()));
        }
        else if (collisionWithWall == WallType::RIGHT){
            temp->setPosition(Position2D(getPosition().getX() + getWidth() - temp->getWidth(), temp->getPosition().getY()));
        }
        else{
            std::cerr << "Not Implemented Error" << std::endl;
        }
        setRacket(temp);
    }
}


std::vector<bool> GameBox::tryMoveBalls(){

    std::vector<Ball*> balls = getBalls();
    std::vector<bool> could_move(balls.size(), false);

    for (size_t idx = 0; idx < balls.size(); ++idx) {
        Ball* ball = balls[idx];

        Position2D np = (*ball).calculateNewPosition();
        Ball temp = Ball(np, (*ball).getRadius(), (*ball).getSpeed());

        WallType wallCollision = isObjectCollidingWithWalls(temp);

        if (wallCollision == WallType::NONE) {
            (*ball).setCenterPosition(np);
            could_move[idx] = true;
        } 
        else {
            could_move[idx] = false;
            auto [vx, vy] = (*ball).getVelocity();

            switch (wallCollision) {
                case WallType::LEFT:
                    (*ball).setVelocity(-vx, vy);
                    break;
                case WallType::RIGHT:
                    (*ball).setVelocity(-vx, vy);
                    break;
                case WallType::TOP:
                    (*ball).setVelocity(vx, -vy);
                    break;
                case WallType::BOTTOM:
                    (*ball).setAlive(false);
                    break;
                default:
                    break;
            }
        }
    }
    return could_move;
}

bool GameBox::isWin(){
    // If any not gold bricks are left, we didn't win yet
    for (Brick* brick : getBricks()) {
        if ((!brick->isBroken()) && (brick->getBrickType() != BrickType::GOLD)){
            return false;
        }
    }
    return true;
}

