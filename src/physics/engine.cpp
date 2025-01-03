#include "engine.hpp"

Action GameEngine::handleInputs(GameController& controller){return controller.getCurrentAction();}

void GameEngine::handleActions(GameBox& gamebox, const Action& action){
    gamebox.tryMoveRacket(gamebox.getRacket()->calculateNewPosition(action));
}

void GameEngine::handleCollisionsWithRacket(GameBox& gamebox){
    for (Ball* ball : gamebox.getBalls()) {

        if (CollisionHelper::isColliding((*ball).getHitbox(), gamebox.getRacket()->getHitbox())) {

            auto [vx, vy] = (*ball).getVelocity();
            float total_velocity = std::sqrt((vx * vx) + (vy * vy));

            float L = gamebox.getRacket()->getWidth();
            float x = (*ball).getCenterPosition().getX() - gamebox.getRacket()->getCenterPosition().getX();

            // formula used in the pdf
            float alpha = (static_cast<float>(M_PI) / 6.0f) + ((5.0f * static_cast<float>(M_PI)) / 6.0f) * (1.0f - (x / L));

            float dvx = total_velocity * std::sin(alpha);
            float dvy = total_velocity * std::cos(alpha);

            (*ball).setVelocity(dvx, dvy);
            (*ball).setCenterPosition(Position2D((*ball).getCenterPosition().getX(), gamebox.getRacket()->getPosition().getY() - (*ball).getRadius()));
        }
    }
}

std::vector<Brick*> GameEngine::handleCollisionsWithBricks(GameBox& gamebox){
    std::vector<Brick*> bricks_hit;

    for (Ball* ball : gamebox.getBalls()){
        auto [vx, vy] = (*ball).getVelocity();
        for (Brick* brick : gamebox.getBricks()){
            if ((std::find(bricks_hit.begin(), bricks_hit.end(), brick) == bricks_hit.end()) && CollisionHelper::isColliding((*ball).getHitbox(), (*brick).getHitbox())) {
                (*ball).setVelocity(-vx, -vy);
                bricks_hit.push_back(brick);
            }
        }
    }
    return bricks_hit;
}

Position2D GameEngine::calculateBonusSpawnPosition(const Brick& brick, const BonusInterface& bonus){
    Position2D brick_center = brick.getCenterPosition();
    Position2D offset_center = Position2D(brick_center.getX() - bonus.getSize() / 2, brick_center.getY() - bonus.getSize() / 2);
    return offset_center;
}

void GameEngine::handleBricks(GameBox& gamebox, Player& player, std::vector<Brick*> bricks){
    for (Brick* brick : bricks){
        brick->makeBrickLoseHP(1);
        if (brick->isBroken()){
            gamebox.removeBrick(brick);
            if (brick->doesBrickContainBonus() && !gamebox.doesPlayerHaveMultipleBalls()){
                BonusInterface* bonus = brick->getBonus();
                gamebox.addBonus(bonus);
                (*bonus).spawnBonus(calculateBonusSpawnPosition((*brick), (*bonus)));
            }
            player.getScore().addScore(brick->getBrickValue());
        }
    }
}

void GameEngine::handleDeadBalls(GameBox& gamebox){
    for (Ball* ball : gamebox.getBalls()){
        if (!(*ball).isAlive()){
            gamebox.removeBall(ball);
        }
    }
}

void GameEngine::handleBalls(GameBox& gamebox, Player& player){
    // 1) Move balls in gamebox
    gamebox.tryMoveBalls();
    // 2) verify collisions
    handleCollisionsWithRacket(gamebox);
    std::vector<Brick*> b = handleCollisionsWithBricks(gamebox);
    // 3) Manage bricks
    handleBricks(gamebox, player, b);
    // 4) get rid of dead balls
    handleDeadBalls(gamebox);
}

void GameEngine::handleCollisionWithEntities(GameBox& gamebox, Player& player){
    
    for (BonusInterface* bonus : gamebox.getBonuses()){
        
        Position2D falling_pos = (*bonus).getGravityPosition();
        (*bonus).setPosition(falling_pos);

        if (CollisionHelper::isColliding((*bonus).getHitbox(), gamebox.getRacket()->getHitbox())){
            player.addBonus(bonus);
            (*bonus).setActive(true);
            gamebox.removeBonus(bonus);
        }
        else if (gamebox.isObjectOutOfBounds(*bonus)){
            gamebox.removeBonus(bonus);
        }
    }
}

void GameEngine::handleBonusLogic(GameBox& gamebox, Player& player){
    for (BonusInterface* bonus : player.getBonus()){
        (*bonus).applyLogic(gamebox, player);
        if ((*bonus).hasBonusDurationExpired()){
            player.removeBonus(bonus);
        }
    }
}

void GameEngine::handleBonus(GameBox& gamebox, Player& player){
    handleCollisionWithEntities(gamebox, player);
    handleBonusLogic(gamebox, player);
}

void GameEngine::handleBallSpawn(GameBox& gamebox){
    Ball* b = new Ball(DEFAULT_SPAWN_POSITION, BALL_RADIUS, BALL_SPEED);
    gamebox.addBall(b);

}

void GameEngine::handleGameOver(const GameBox& gamebox, const Player& player){
    (void) gamebox;
    (void) player;
    std::cout << "Loose" << std::endl;
    exit(0);
}

void GameEngine::handleWin(const GameBox& gamebox, const Player& player){
    (void) gamebox;
    (void) player;
    std::cout << "Win" <<std::endl;
    exit(0);
}

void GameEngine::handleGameState(GameBox& gamebox, Player& player){
    // Verify "win" state
    if (gamebox.isWin()){
        handleWin(gamebox, player);
    }

    // Verify if ball vector empty (state: lose life)
    if (gamebox.isBallVectorEmpty()){
        player.incrementHp(-1);
        if (player.isDead()){handleGameOver(gamebox, player);}
        else{handleBallSpawn(gamebox);}
    }
}

void GameEngine::handleRoutine(GameBox& gamebox, Player& player){
    Action a = handleInputs(player.getController());
    handleActions(gamebox, a);
    handleBalls(gamebox, player);
    handleBonus(gamebox, player);
    handleGameState(gamebox, player);
}

