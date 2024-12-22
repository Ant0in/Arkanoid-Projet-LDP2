#pragma once

#include "score.hpp"
#include "controller.hpp"
#include "../game/bonus.hpp"
#include <vector>

class Player{
    private:
        int hp;
        GameController controller;
        Score score;
        std::vector<BonusInterface> bonus;
    public:
        Player(int hp = 3, const GameController& controller = GameController(), const Score& score = Score(0), const std::vector<BonusInterface>& bonus = std::vector<BonusInterface>{})
        : hp{hp}, controller{controller}, score{score}, bonus{bonus}{}
        ~Player() = default;

        int getHp() const;
        void setHp(int nhp);

        void incrementHp(int incr);

        bool isDead() const;

        GameController& getController();

        Score& getScore();

        std::vector<BonusInterface>& getBonus();
        void addBonus(const BonusInterface& b);
        void removeBonus(const BonusInterface& b);
};