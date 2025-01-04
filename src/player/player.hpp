#pragma once

#include "score.hpp"
#include "controller.hpp"
#include "../game/bonus.hpp"
#include <vector>
#include <string>
#include <fstream>

class BonusInterface;

class Player{

    private:

        int _hp;
        GameController _controller;
        Score _score;
        std::vector<BonusInterface*> _bonus;
        Score _highScore;

    public:

        Player(int hp = PLAYER_DEFAULT_HEALTH, const GameController& controller = GameController(), const Score& score = Score(0), const std::vector<BonusInterface*>& bonus = {}):
            _hp{hp},
            _controller{controller},
            _score{score},
            _bonus{bonus},
            _highScore{readHighScoreFromFile(HIGH_SCORE_FILE)}{}

        ~Player() = default;

        Score readHighScoreFromFile(const std::string& filePath) const;
        Score& getHighScore();
        void setHighScore(const Score& score);
        void updateHighScoreFile(const std::string& filePath);
        void checkHighScore();
        int getHp() const;
        void setHp(int nhp);
        void incrementHp(int incr);
        bool isDead() const;
        GameController& getController();
        Score& getScore();
        std::vector<BonusInterface*>& getBonus();
        void addBonus(BonusInterface* b);
        void removeBonus(BonusInterface* b);
};