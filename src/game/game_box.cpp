#include "game_box.hpp"

Position2D GameBox::getPosition() const {return position;}

float GameBox::getWidth() const {return width;}
float GameBox::getHeight() const {return height;}

std::vector<Brick> GameBox::getBricks() const {return bricks;}

void GameBox::addBrick(Brick brick){
    getBricks().push_back(brick);
}
void GameBox::removeBrick(Brick brick){
    for (auto it = getBricks().begin(); it != getBricks().end(); ++it) {
        if (*it == brick) { 
            getBricks().erase(it); 
            break;
        }
    }
}

std::vector<Ball> GameBox::getBalls() const {return balls;}

Racket GameBox::getRacket() const {return racket;}

std::vector<SolidInterface*> GameBox::getEntities() const {return entities;}

void GameBox::addEntity(SolidRectangle& entity){
    getEntities().push_back(&entity);
}

void GameBox::addEntity(SolidCircle& entity){
    getEntities().push_back(&entity);
}

void GameBox::removeEntity(SolidRectangle& entity){
    for (auto it = getEntities().begin(); it != getEntities().end(); ++it) {
        if (**it == entity) { 
            getEntities().erase(it); 
            break;
        }
    }
}

void GameBox::removeEntity(SolidCircle& entity){
    for (auto it = getEntities().begin(); it != getEntities().end(); ++it) {
        if (**it == entity) { 
            getEntities().erase(it); 
            break;
        }
    }
}

bool GameBox::tryMoveRacket(const Position2D& p){
    Racket rk = getRacket();
    // If racket not out of bound
    bool can_move = (getPosition().getX() <= p.getX() && getPosition().getY() <= p.getY() && (getPosition().getX() + getWidth()) >= (p.getX() + rk.getWidth()) && (getPosition().getY() + getHeight()) >= (p.getY() + rk.getHeight()));
    
    // Move racket if possible
    if (can_move){rk.moveToCoordinates(p);}
    return can_move;
}

std::vector<bool> GameBox::tryMoveBalls(const std::vector<Position2D>& p_vec){
    std::vector<Ball> balls = getBalls();
    std::vector<bool> can_move;
    can_move.reserve(p_vec.size());

    for (const auto& p: p_vec) {
        bool flag = (getPosition().getX() < p.getX() && p.getX() < getPosition().getX() + getWidth()) &&
                    (getPosition().getY() < p.getY() && p.getY() < getPosition().getY() + getHeight());
        can_move.push_back(flag);
    }

    // Move balls if possible
    for (size_t i = 0; i < p_vec.size() && i < balls.size(); ++i) {
        if (can_move[i]) {
            balls[i].moveToCoordinates(p_vec[i]);
        }
        else {
            balls[i].moveToCoordinates(p_vec[i]);
        }
    }
    return can_move;
}

void GameBox::checkCollisionWithWalls(){
    for (auto& ball : getBalls()) {

        Position2D ball_pos = ball.getCenterPosition();
        float ball_radius = ball.getRadius();
        auto [vx, vy] = ball.getVelocity();

        // Left wall
        if ((ball_pos.getX() - ball_radius <= getPosition().getX()) && (vx < 0)) {
            ball.setVelocity(-vx, vy);
            ball.moveToCoordinates(Position2D(getPosition().getX() + ball_radius, ball_pos.getY()));
        }
        // Right wall
        else if ((ball_pos.getX() + ball_radius >= getPosition().getX() + getWidth()) && (vx > 0)) {
            ball.setVelocity(-vx, vy);
            ball.moveToCoordinates(Position2D(getPosition().getX() + getWidth() - ball_radius, ball_pos.getY()));
        }

        // Top wall
        if ((ball_pos.getY() - ball_radius <= getPosition().getY()) && (vy < 0)) {
            ball.setVelocity(vx, -vy);
            ball.moveToCoordinates(Position2D(ball_pos.getX(), getPosition().getY() + ball_radius));
        }
        // Bottom wall
        else if ((ball_pos.getY() + ball_radius >= getPosition().getY() + getHeight()) && (vy > 0)) {
            ball.setVelocity(vx, -vy);
            ball.moveToCoordinates(Position2D(ball_pos.getX(), getPosition().getY() + getHeight() - ball_radius));
        }
    }
}

std::vector<Brick> GameBox::checkCollisionsWithRacketAndBricks(){
    std::vector<Brick> bricks_hit;

    for (auto& ball: getBalls()) {
        auto [vx, vy] = ball.getVelocity();

        // Collision with racket
        if (CollisionHelper::isColliding(ball.getHitbox(), getRacket().getHitbox())) {
            float total_velocity = std::sqrt(vx * vx + vy * vy);
            float L = getRacket().getWidth();
            float x = ball.getCenterPosition().getX() - getRacket().calculateCenterPosition().getX();
            float alpha = (M_PI / 6) + ((5 * M_PI) / 6) * (1 - (x / L)); // modifiée pour 30->150 degrés

            float dvx = total_velocity * std::sin(alpha);
            float dvy = total_velocity * std::cos(alpha);
            ball.setVelocity(dvx, dvy);

            // Readjustment
            ball.moveToCoordinates(Position2D(getPosition().getX(), getRacket().getPosition().getY() - ball.getRadius()));
        }

        // Collision with bricks
        for (auto& brick: getBricks()) {
            if (CollisionHelper::isColliding(ball.getHitbox(), brick.getHitbox()) &&
                std::find(bricks_hit.begin(), bricks_hit.end(), brick) == bricks_hit.end()) {
                    ball.setVelocity(-vx, -vy);
                    bricks_hit.push_back(brick);
            }
        }
    }
    return bricks_hit;
}
