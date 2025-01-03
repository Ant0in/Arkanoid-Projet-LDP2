#include "controller.hpp"

const std::unordered_map<int, Action>& GameController::getConfig() const {return _config;}

Action GameController::getCurrentAction() {return _currentAction;}
void GameController::setCurrentAction(const Action& action){_currentAction = action;}
Position2D GameController::getCurrentMousePosition() {return _currentMousePosition;}
void GameController::setCurrentMousePosition(const Position2D& pos) {_currentMousePosition = pos;}
bool GameController::hasMouseMoved() {return _hasMouseMoved;}
void GameController::setHasMouseMoved(bool flag) {_hasMouseMoved = flag;}

void GameController::updateUserAction(int keyCode) {
    
    const std::unordered_map<int, Action>& cfg = getConfig();

    if (cfg.find(keyCode) != cfg.end()) {
        // if keybind is set in the config
        setCurrentAction(cfg.at(keyCode));

    } else {
        // we dont know the key that got pressed
        setCurrentAction(Action::NONE);
    }
}

void GameController::updateMousePosition(const Position2D& mousePosition) {

    if (mousePosition != getCurrentMousePosition()) {
        setHasMouseMoved(true);
        setCurrentMousePosition(mousePosition);
    }

}
