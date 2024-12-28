#pragma once

#include <iostream>
#include <allegro5/allegro5.h>
#include <unordered_map>
#include <string>
#include "../common.hpp"

class GameController{
    private:
        std::unordered_map<int, Action> DEFAULT;
        std::unordered_map<int, Action> config;
        Action currentAction;
    public:
        GameController(const std::unordered_map<int, Action>& userConfig): config{userConfig}, currentAction{Action::NONE}{}
        GameController(): currentAction{Action::NONE}{
            DEFAULT[ALLEGRO_KEY_LEFT] = Action::LEFT;
            DEFAULT[ALLEGRO_KEY_RIGHT] = Action::RIGHT;
            config = DEFAULT;
        }
        ~GameController() = default;

        Action getCurrentAction();
        void setCurrentAction(const Action& action);

        const std::unordered_map<int, Action>& getConfig() const;

        void updateUserAction(int keyCode = 0);
};  