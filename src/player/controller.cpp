#include "controller.hpp"

const std::unordered_map<int, Action>& GameController::getConfig() const {return config;}

Action& GameController::getCurrentAction() {return currentAction;}
void GameController::setCurrentAction(const Action& action){currentAction = action;}

void GameController::updateUserAction(int keyCode){
    // Called when a key is pressed to get the action
    switch (keyCode) {
        case ALLEGRO_KEY_LEFT:
            setCurrentAction(Action::LEFT);
        case ALLEGRO_KEY_RIGHT:
            setCurrentAction(Action::RIGHT);
        default:             
            setCurrentAction(Action::NONE);
    }
}
