#pragma once

#include <iostream>
#include <allegro5/allegro5.h>
#include <unordered_map>
#include <string>
#include "game/common.hpp"

class GameController{
    private:
        std::unordered_map<int, Action> DEFAULT;
        std::unordered_map<int, Action> config;
    public:
        GameController(const std::unordered_map<int, Action>& userConfig): config{userConfig}{}
        GameController();

        const std::unordered_map<int, Action>& getConfig() const;

        const Action getUserAction(int keyCode = 0) const;
};  