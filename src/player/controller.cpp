#include "controller.hpp"

const std::unordered_map<int, Action>& GameController::getConfig() const {return config;}

Action GameController::getCurrentAction() {return currentAction;}
void GameController::setCurrentAction(const Action& action){currentAction = action; std::cout<<static_cast<int>(currentAction)<<std::endl;}

void GameController::updateUserAction(int keyCode){
    // Called when a key is pressed to get the action
    switch (keyCode) {
        case ALLEGRO_KEY_LEFT:
            setCurrentAction(Action::LEFT);
            break;
        case ALLEGRO_KEY_RIGHT:
            setCurrentAction(Action::RIGHT);
            break;
        default:             
            setCurrentAction(Action::NONE);
            break;
    }
}
