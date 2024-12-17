#include "controller.hpp"

GameController::GameController(){
    DEFAULT[ALLEGRO_KEY_LEFT] = Action::LEFT;
    DEFAULT[ALLEGRO_KEY_RIGHT] = Action::RIGHT;
    config = DEFAULT;
}

const std::unordered_map<int, Action>& GameController::getConfig() const {return config;}

const Action GameController::getUserAction(int keyCode) const{
    // Called when a key is pressed to get the action
    switch (keyCode) {
        case ALLEGRO_KEY_LEFT:
            std::cout<<"left";
            return Action::LEFT;
        case ALLEGRO_KEY_RIGHT:
            return Action::RIGHT;
        default:             
            return Action::NONE;
    }
}
