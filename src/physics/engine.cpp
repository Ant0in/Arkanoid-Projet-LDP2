#include "../../include/engine.hpp"

void GameEngine::handleActions(LevelManager& manager, GameBox*& gamebox, Player& player) {
    // First, we get the keyboard action if there's one
    Action action = player.getController().getCurrentAction();
    // we try to move the racket using keyboard inputs
    if (action == Action::LEFT || action == Action::RIGHT) {
        gamebox->tryMoveRacket(gamebox->getRacket()->calculateNewPosition(action));

    } else if (action == Action::SHOOT) {
        // Trying to shoot a ball or a laser.
        if (player.hasBallStored()) {
            handleBallSpawn(gamebox);
            player.setHasBallStored(false);
        } else if (player.canShootLaser()) {
            Laser* laser = new Laser();
            laser->spawnLaser(gamebox->getRacket());
            gamebox->addLaser(laser);
        }

        // finally we make sure the user will be able to make new shoots/lazers
        player.getController().updateUserAction(0);
    } else if (action == Action::NEXT_LEVEL || action == Action::PREVIOUS_LEVEL) {
        // Switch levels
        handleLevelSwitch(manager, gamebox, player);
    } else if (action == Action::RESET_HIGHSCORE) {
        player.setHighScore(Score(0));
    } else if (action == Action::REMAKE) {
        handleRemakeGame(manager, gamebox, player);
    }

    // and then we try to see if the player has moved the mouse
    if (player.getController().hasMouseMoved()) {
        float racketWidth = gamebox->getRacket()->getWidth();
        float mouseHorizontalAxis =
            player.getController().getCurrentMousePosition().getX() - (racketWidth / 2);
        float racketVerticalAxis = gamebox->getRacket()->getPosition().getY();
        gamebox->tryMoveRacket(Position2D(mouseHorizontalAxis, racketVerticalAxis));
        player.getController().setHasMouseMoved(false);  // reset the need to move to the position
    }
}

void GameEngine::handleCollisionsWithRacket(GameBox*& gamebox) {
    for (Ball* ball : gamebox->getBalls()) {
        if (CollisionHelper::isColliding(ball->getHitbox(), gamebox->getRacket()->getHitbox())) {
            auto [vx, vy]        = ball->getVelocity();
            float total_velocity = std::sqrt((vx * vx) + (vy * vy));

            float L = gamebox->getRacket()->getWidth();
            float x =
                ball->getCenterPosition().getX() - gamebox->getRacket()->getCenterPosition().getX();

            // formula used in the pdf
            float alpha = (static_cast<float>(M_PI) / 6.0f) +
                          ((5.0f * static_cast<float>(M_PI)) / 6.0f) * (1.0f - (x / L));

            float dvx = total_velocity * std::sin(alpha);
            float dvy = total_velocity * std::cos(alpha);

            ball->setVelocity(dvx, dvy);
            ball->setCenterPosition(
                Position2D(ball->getCenterPosition().getX(),
                           gamebox->getRacket()->getPosition().getY() - ball->getRadius()));
        }
    }
}

std::vector<Brick*> GameEngine::handleCollisionsWithBricks(GameBox*& gamebox) {
    std::vector<Brick*> bricks_hit;

    for (Ball* ball : gamebox->getBalls()) {
        auto [vx, vy] = ball->getVelocity();
        for (Brick* brick : gamebox->getBricks()) {
            if ((std::find(bricks_hit.begin(), bricks_hit.end(), brick) == bricks_hit.end()) &&
                CollisionHelper::isColliding(ball->getHitbox(), brick->getHitbox())) {
                ball->setVelocity(-vx, -vy);
                bricks_hit.push_back(brick);
            }
        }
    }
    return bricks_hit;
}

Position2D GameEngine::calculateBonusSpawnPosition(const Brick&          brick,
                                                   const BonusInterface& bonus) {
    Position2D brick_center  = brick.getCenterPosition();
    Position2D offset_center = Position2D(brick_center.getX() - bonus.getSize() / 2,
                                          brick_center.getY() - bonus.getSize() / 2);
    return offset_center;
}

void GameEngine::handleBricks(GameBox*& gamebox, Player& player, std::vector<Brick*> bricks) {
    for (Brick* brick : bricks) {
        brick->makeBrickLoseHP(1);
        if (brick->isBroken()) {
            if (brick->doesBrickContainBonus() && !gamebox->doesPlayerHaveMultipleBalls()) {
                BonusInterface* bonus = brick->getBonus()->clone();
                gamebox->addBonus(bonus);
                bonus->spawnBonus(calculateBonusSpawnPosition((*brick), (*bonus)));
            }
            player.getScore().addScore(brick->getBrickValue());
            player.checkHighScore();
            gamebox->removeBrick(brick);
            delete brick;
        }
    }
}

void GameEngine::handleDeadBalls(GameBox*& gamebox) {
    for (Ball* ball : gamebox->getBalls()) {
        if (!ball->isAlive()) {
            gamebox->removeBall(ball);
        }
    }
}

void GameEngine::handleBalls(GameBox*& gamebox, Player& player) {
    // 1) Move balls in gamebox
    gamebox->tryMoveBalls();
    // 2) verify collisions
    handleCollisionsWithRacket(gamebox);
    std::vector<Brick*> b = handleCollisionsWithBricks(gamebox);
    // 3) Manage bricks
    handleBricks(gamebox, player, b);
    // 4) get rid of dead balls
    handleDeadBalls(gamebox);
    // 5) Handle spawn in case the grab delay is expired
    if (player.hasGrabTimerExpired()) {
        // std::cout << "Grab timer expired : releasing ball" << std::endl;
        player.setHasGrabTimerExpired(false);
        player.setHasBallStored(false);
        handleBallSpawn(gamebox);
    }
}

void GameEngine::handleCollisionsWithLasers(GameBox*& gamebox, Player& player) {
    // TODO
    std::vector<Brick*> bricks_hit;
    for (Laser* laser : gamebox->getLasers()) {
        bool needToBeCleared = false;
        // for each laser, if colliding then we delete it and add brick to the hit list

        if (gamebox->isObjectCollidingWithWalls(laser->getHitbox()) != WallType::NONE) {
            needToBeCleared = true;
        } else {
            for (Brick* brick : gamebox->getBricks()) {
                if ((std::find(bricks_hit.begin(), bricks_hit.end(), brick) == bricks_hit.end()) &&
                    CollisionHelper::isColliding(laser->getHitbox(), brick->getHitbox())) {
                    bricks_hit.push_back(brick);
                    needToBeCleared = true;
                }
            }
        }

        if (needToBeCleared) {
            gamebox->removeLaser(laser);
            delete laser;
        }
    }
    handleBricks(gamebox, player, bricks_hit);
}

void GameEngine::handleLasers(GameBox*& gamebox, Player& player) {
    // OOP-addict aaaaa function smh
    gamebox->tryMoveLasers();
    handleCollisionsWithLasers(gamebox, player);
}

void GameEngine::handleCollisionWithEntities(GameBox*& gamebox, Player& player) {
    for (BonusInterface* bonus : gamebox->getBonuses()) {
        Position2D falling_pos = bonus->getGravityPosition();
        bonus->setPosition(falling_pos);

        if (CollisionHelper::isColliding(bonus->getHitbox(), gamebox->getRacket()->getHitbox())) {
            // first, we want to revert the effect of the previous bonus
            if (player.hasBonusActive() && !(player.getBonus()->getBonusType() == BonusType::SLOW &&
                                             bonus->getBonusType() == BonusType::SLOW)) {
                player.getBonus()->revertLogic(*gamebox, player);
            }
            // then, we override this bonus with the new one, activate it and remove it from the
            // gamebox
            player.setBonus(bonus);
            bonus->setActive(true);
            gamebox->removeBonus(bonus);
        }

        else if (gamebox->isObjectOutOfBounds(bonus->getHitbox())) {
            gamebox->removeBonus(bonus);
        }
    }
}

void GameEngine::handleBonusLogic(GameBox*& gamebox, Player& player) {
    if (player.hasBonusActive()) {
        BonusInterface* bonus = player.getBonus();
        bonus->applyLogic(*gamebox, player);

        if (bonus->hasBonusDurationExpired()) {
            bonus->setActive(false);
        }
    }
}

void GameEngine::handleBonus(GameBox*& gamebox, Player& player) {
    handleCollisionWithEntities(gamebox, player);
    handleBonusLogic(gamebox, player);
}

void GameEngine::handleBallSpawn(GameBox*& gamebox) {
    Position2D spawnPosition =
        Position2D(gamebox->getRacket()->getCenterPosition().getX(),
                   gamebox->getRacket()->getPosition().getY() - 2 * BALL_RADIUS);
    Ball* b = new Ball(
        spawnPosition, BALL_RADIUS, BALL_SPEED, BALL_X_VELOCITY_DEFAULT, BALL_Y_VELOCITY_DEFAULT);
    gamebox->addBall(b);
}

void GameEngine::handleRemakeGame(LevelManager& manager, GameBox*& gamebox, Player& player) {
    if (player.isDead()) {
        manager.setCurrentLevelIndex(0);  // reset des levels
        delete gamebox;
        gamebox = manager.generateCurrentLevelGamebox();

        // Reset player
        player.reset();
    }
}

void GameEngine::handleWin(LevelManager& manager, GameBox*& gamebox, Player& player) {
    player.getController().setCurrentAction(Action::NEXT_LEVEL);
    handleLevelSwitch(manager, gamebox, player);
}

void GameEngine::handleGameState(LevelManager& manager, GameBox*& gamebox, Player& player) {
    // Verify "win" state

    gamebox->incrementFrameCount(1);

    if (gamebox->isWin()) {
        handleWin(manager, gamebox, player);
    }

    // Verify if ball vector empty and player has no held ball (state: lose life)
    if (gamebox->isBallVectorEmpty() && !(player.hasBallStored())) {
        if (player.hasBonusActive()) {
            player.getBonus()->setActive(false);
        }

        player.incrementHp(-1);

        if (!player.isDead()) {
            // player gets a ball in his storage
            player.setHasBallStored(true);
        }
    }
}

void GameEngine::handleLevelSwitch(LevelManager& manager, GameBox*& gamebox, Player& player) {
    Action switch_action = player.getController().getCurrentAction();

    if (switch_action == Action::PREVIOUS_LEVEL) {
        manager.goToPreviousLevel();
    } else if (switch_action == Action::NEXT_LEVEL) {
        manager.goToNextLevel();
    } else {
        // idk
    }

    int saved_balls = static_cast<int>(gamebox->getBalls().size());
    delete gamebox;
    gamebox = manager.generateCurrentLevelGamebox();

    // Reset player bonus + add previously lost balls
    player.setBonus(nullptr);
    player.setCanShootLaser(false);
    player.getController().updateUserAction(0);
    player.incrementHp(saved_balls);
}

void GameEngine::handleRoutine(LevelManager& manager, GameBox*& gamebox, Player& player) {
    handleActions(manager, gamebox, player);
    if (!player.isDead()) {
        handleBalls(gamebox, player);
        handleBonus(gamebox, player);
        handleLasers(gamebox, player);
        handleGameState(manager, gamebox, player);
    }
}
