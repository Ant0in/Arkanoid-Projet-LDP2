#include "engine.hpp"

const Action GameEngine::handle_inputs(const GameController& controller){
    return controller.getUserAction();
}

const bool GameEngine::handle_actions(GameBox& gamebox, const Action& action){
    Racket rk = gamebox.getRacket();
    float rk_x = rk.getPosition().getX(); 
    float rk_y = rk.getPosition().getY();
    float rk_sensibility = rk.getSensibility();

    Position2D new_position(rk_x, rk_y);

    switch(action){
        case Action::LEFT:
            new_position = Position2D(rk_x-rk_sensibility, rk_y);
            break;
        case Action::RIGHT:
            new_position = Position2D(rk_x+rk_sensibility, rk_y);
            break;
        case Action::NONE:
            new_position = Position2D(rk_x, rk_y);
            break;
    }

    bool can_move = gamebox.tryMoveRacket(new_position);
    return can_move;
}

const std::vector<Position2D> GameEngine::calculate_balls_positions(const GameBox& gamebox){
    std::vector<Position2D> pvec;
    for (const auto& ball : gamebox.getBalls()) {
        float x_vel = std::get<0>(ball.getVelocity());
        float y_vel = std::get<1>(ball.getVelocity());
        float dx = ball.getCenterPosition().getX() + (x_vel * ball.getSpeed());
        float dy = ball.getCenterPosition().getY() + (y_vel * ball.getSpeed());
        pvec.push_back(Position2D(dx, dy));
    }
    return pvec;
}

const std::vector<Brick> GameEngine::handle_balls(GameBox& gamebox){
    // Calculate new positions of the balls and try to move them
    std::vector<Position2D> pvec = calculate_balls_positions(gamebox);
    std::vector<bool> can_move = gamebox.tryMoveBalls(pvec);

    // Apply collisions
    gamebox.checkCollisionWithWalls();
    std::vector<Brick> bricks_hit = gamebox.checkCollisionsWithRacketAndBricks();
    return bricks_hit;
}

const int GameEngine::handle_brick_destruction(GameBox& gamebox, std::vector<Brick>& bricks){
    int total_reward = 0;

    for (auto& brick : bricks){
        brick.makeBrickLoseHP(1);
        if (brick.isBroken()){

            //  TODO spawn des bonus ici

            gamebox.removeBrick(brick);
            total_reward += brick.getBrickValue();
        }
    }

    return total_reward;
}

const void GameEngine::handle_routine(GameBox& gamebox, const GameController& controller, Score& score){
    // Manage actions
    Action player_action = handle_inputs(controller);
    handle_actions(gamebox, player_action);

    // Manage collisions
    std::vector<Brick> bricks_hit = handle_balls(gamebox);
    int reward = handle_brick_destruction(gamebox, bricks_hit);
    score.addScore(reward);

    // TODO GESTION DES BONUS (utilisation bonus / collision bonus (pickup) / fin d'un bonus actif)


    // TODO GESTION FIN DE NIVEAU (plus aucune balle active ou plus aucune brique non dorée)
}

