#include "controller.hpp"

const std::unordered_map<int, Action>& GameController::getConfig() const {return _config;}

Action GameController::getCurrentAction() {return _currentAction;}
void GameController::setCurrentAction(const Action& action){_currentAction = action;}

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
