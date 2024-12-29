#pragma once

#include "../game/game_box.hpp"
#include "../game/ball.hpp"
#include "../game/racket.hpp"
#include "../game/brick.hpp"
#include "../player/score.hpp"
#include "../player/controller.hpp"
#include "../common.hpp"
#include <vector>
#include <cmath>


class GameEngine{
    public:
        static const Action handleInputs(GameController& controller);

        static const void handleActions(GameBox& gamebox, const Action& action);

        static const void handleCollisionsWithRacket(GameBox& gamebox);

        static const std::vector<Brick*> handleCollisionsWithBricks(GameBox& gamebox);

        static const Position2D calculateBonusSpawnPosition(const Brick& brick, const BonusInterface& bonus);

        static const void handleBricks(GameBox& gamebox, Player& player, std::vector<Brick*> bricks);

        static const void handleDeadBalls(GameBox& gamebox);

        static const void handleBalls(GameBox& gamebox, Player& player);

        static const void handleCollisionWithEntities(GameBox& gamebox, Player& player);

        static const void handleBonusLogic(GameBox& gamebox, Player& player);

        static const void handleBonus(GameBox& gamebox, Player& player);

        static const void handleBallSpawn(GameBox& gamebox);

        static const void handleGameOver(const GameBox& gamebox, const Player& player);

        static const void handleWin(const GameBox& gamebox, const Player& player);

        static const void handleGameState(GameBox& gamebox, Player& player);

        static const void handleRoutine(GameBox& gamebox, Player& player);

};

