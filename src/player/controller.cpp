#include "controller.hpp"

const std::unordered_map<int, Action>& GameController::getConfig() const {return _config;}

Action GameController::getCurrentAction() {return _currentAction;}
void GameController::setCurrentAction(const Action& action){_currentAction = action;}

void GameController::updateUserAction(int keyCode) {
    
    const std::unordered_map<int, Action>& cfg = getConfig();

    if (cfg.find(keyCode) != cfg.end()) {
        setCurrentAction(cfg.at(keyCode));
    } else {
        setCurrentAction(Action::NONE);
    }
}
