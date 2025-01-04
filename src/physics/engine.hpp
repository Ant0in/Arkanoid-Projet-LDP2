#pragma once

#include <cmath>
#include <vector>

#include "../common.hpp"
#include "../game/ball.hpp"
#include "../game/brick.hpp"
#include "../game/game_box.hpp"
#include "../game/racket.hpp"
#include "../player/controller.hpp"
#include "../player/score.hpp"

class GameEngine {
   public:
    static void handleActions(GameBox& gamebox, Player& player);

    static void handleCollisionsWithRacket(GameBox& gamebox);

    static std::vector<Brick*> handleCollisionsWithBricks(GameBox& gamebox);

    static Position2D calculateBonusSpawnPosition(const Brick& brick, const BonusInterface& bonus);

    static void handleBricks(GameBox& gamebox, Player& player, std::vector<Brick*> bricks);

    static void handleDeadBalls(GameBox& gamebox);

    static void handleBalls(GameBox& gamebox, Player& player);

    static void handleCollisionWithEntities(GameBox& gamebox, Player& player);

    static void handleBonusLogic(GameBox& gamebox, Player& player);

    static void handleBonus(GameBox& gamebox, Player& player);

    static void handleBallSpawn(GameBox& gamebox);

    static void handleGameOver(const GameBox& gamebox, const Player& player);

    static void handleWin(const GameBox& gamebox, const Player& player);

    static void handleGameState(GameBox& gamebox, Player& player);

    static void handleRoutine(GameBox& gamebox, Player& player);
};
