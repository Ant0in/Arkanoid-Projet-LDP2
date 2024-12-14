#include <iostream>
#include <allegro5/allegro5.h>
#include <unordered_map>
#include <string>
#include "common.hpp"

class GameController{
    private:
        std::unordered_map<std::string, int> DEFAULT;
        std::unordered_map<std::string, int> config;
    public:
        GameController(const std::unordered_map<int, int>& userConfig);
        GameController();

        const std::unordered_map<std::string, int> getConfig() const;

        const int getUserAction() const;
};  