#include "engine.hpp"

class GameEngine{
    static const Action handle_inputs(const GameController& controller);

    static const bool handle_actions(const GameBox& gamebox, const Action& action);

    static const std::vector<Position2D> calculate_balls_positions(const GameBox& gamebox);

    static const std::vector<Brick> handle_balls(const GameBox& gamebox);

    static const int handle_brick_destruction(GameBox& gamebox, const std::vector<Brick>& bricks);

    static const void handle_routine(const GameBox& gamebox, const GameController& controller, Score& score);
};
