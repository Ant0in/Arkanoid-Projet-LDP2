#pragma once

#include <fstream>
#include <string>
#include <vector>

#include "../game/bonus.hpp"
#include "controller.hpp"
#include "score.hpp"

class BonusInterface;

class Player {
   private:
    int             _hp;
    GameController  _controller;
    Score           _score;
    BonusInterface* _bonus;
    Score           _highScore;
    bool            _hasBallStored;
    bool            _hasGrabDelayExpired;

   public:
    Player(int                   hp            = PLAYER_DEFAULT_HEALTH,
           const GameController& controller    = GameController(),
           const Score&          score         = Score(0),
           BonusInterface*       bonus         = nullptr,
           bool                  hasBallStored = true)
        : _hp{hp},
          _controller{controller},
          _score{score},
          _bonus{bonus},
          _highScore{readHighScoreFromFile(HIGH_SCORE_FILE)},
          _hasBallStored{hasBallStored},
          _hasGrabDelayExpired{false} {
    }

    ~Player() = default;

    Score           readHighScoreFromFile(const std::string& filePath) const;
    Score&          getHighScore();
    void            setHighScore(const Score& score);
    void            updateHighScoreFile(const std::string& filePath);
    void            checkHighScore();
    int             getHp() const;
    void            setHp(int nhp);
    bool            hasBallStored();
    void            setHasBallStored(bool flag);
    bool            hasGrabTimerExpired();
    void            setHasGrabTimerExpired(bool flag);
    void            incrementHp(int incr);
    bool            isDead() const;
    GameController& getController();
    Score&          getScore();

    bool            hasBonusActive();
    BonusInterface* getBonus();
    void            setBonus(BonusInterface* bonus);
};