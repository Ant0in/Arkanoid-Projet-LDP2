#pragma once

#include <cmath>
#include <vector>

#include "ball.hpp"
#include "brick.hpp"
#include "common.hpp"
#include "controller.hpp"
#include "game_box.hpp"
#include "level_manager.hpp"
#include "racket.hpp"
#include "score.hpp"


class GameEngine {
   public:
    static void handleActions(LevelManager& manager, GameBox*& gamebox, Player& player);

    static void handleCollisionsWithRacket(GameBox*& gamebox);

    static std::vector<Brick*> handleCollisionsWithBricks(GameBox*& gamebox);

    static Position2D calculateBonusSpawnPosition(const Brick& brick, const BonusInterface& bonus);

    static void handleBricks(GameBox*& gamebox, Player& player, std::vector<Brick*> bricks);

    static void handleDeadBalls(GameBox*& gamebox);

    static void handleBalls(GameBox*& gamebox, Player& player);

    static void handleCollisionsWithLasers(GameBox*& gamebox, Player& player);

    static void handleLasers(GameBox*& gamebox, Player& player);

    static void handleCollisionWithEntities(GameBox*& gamebox, Player& player);

    static void handleBonusLogic(GameBox*& gamebox, Player& player);

    static void handleBonus(GameBox*& gamebox, Player& player);

    static void handleBallSpawn(GameBox*& gamebox);

    static void handleRemakeGame(LevelManager& manager, GameBox*& gamebox, Player& player);

    static void handleWin(LevelManager& manager, GameBox*& gamebox, Player& player);

    static void handleGameState(LevelManager& manager, GameBox*& gamebox, Player& player);

    static void handleLevelSwitch(LevelManager& manager, GameBox*& gamebox, Player& player);

    static void handleRoutine(LevelManager& manager, GameBox*& gamebox, Player& player);
};
