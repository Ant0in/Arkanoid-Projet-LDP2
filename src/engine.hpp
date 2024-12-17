#pragma once

#include "game/game_box.hpp"
#include "game/ball.hpp"
#include "game/racket.hpp"
#include "game/brick.hpp"
#include "game/score.hpp"
#include "controller.hpp"
#include "game/common.hpp"
#include <vector>


class GameEngine{
    static const Action handle_inputs(const GameController& controller);

    static const bool handle_actions(GameBox& gamebox, const Action& action);

    static const std::vector<Position2D> calculate_balls_positions(const GameBox& gamebox);

    static const std::vector<Brick> handle_balls(GameBox& gamebox);

    static const int handle_brick_destruction(GameBox& gamebox, std::vector<Brick>& bricks);

    static const void handle_routine(GameBox& gamebox, const GameController& controller, Score& score);
};

