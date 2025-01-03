#pragma once

#include <iostream>
#include <allegro5/allegro5.h>
#include <unordered_map>
#include <string>
#include "../common.hpp"

class GameController{
    
    private:

        std::unordered_map<int, Action> _config;
        Action _currentAction;

    public:
        
        GameController(const std::unordered_map<int, Action>& userConfig = DEFAULT_CONFIG):
            _config{userConfig},
            _currentAction{Action::NONE} {}

        ~GameController() = default;

        Action getCurrentAction();
        void setCurrentAction(const Action& action);
        const std::unordered_map<int, Action>& getConfig() const;
        void updateUserAction(int keyCode = 0);
};  