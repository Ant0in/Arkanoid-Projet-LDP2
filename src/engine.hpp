#pragma once

#include "game/game_box.hpp"
#include "game/ball.hpp"
#include "game/racket.hpp"
#include "game/brick.hpp"
#include "game/score.hpp"
#include "controller.hpp"
#include "common.hpp"
#include <vector>


class GameEngine{
    static const Action handle_inputs(const GameController& controller);

    static const bool handle_actions(const GameBox& gamebox, const Action& action);

    static const std::vector<Position2D> calculate_balls_positions(const GameBox& gamebox);

    static const std::vector<Brick> handle_balls(const GameBox& gamebox);

    static const int handle_brick_destruction(GameBox& gamebox, const std::vector<Brick>& bricks);

    static const void handle_routine(GameBox& gamebox, const GameController& controller, Score& score);
};

