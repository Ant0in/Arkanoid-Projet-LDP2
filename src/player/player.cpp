#include "../../include/player.hpp"

Score Player::readHighScoreFromFile(const std::string& filePath) const {
    std::ifstream file(filePath);

    if (!file.is_open()) {
        fprintf(stderr,
                "Erreur : Impossible d'ouvrir le fichier avec le meilleur score. Meilleur score "
                "mis a 0.\n");
        return Score(0);
    }

    int highScoreValue = 0;
    file >> highScoreValue;

    if (file.fail()) {
        fprintf(stderr,
                "Erreur : Impossible de lire le fichier avec le meilleur score. Meilleur score mis "
                "a 0.\n");
        return Score(0);
    }

    return Score(highScoreValue);
}

Score& Player::getHighScore() {
    return _highScore;
};
void Player::setHighScore(const Score& score) {
    _highScore = score;
}

void Player::updateHighScoreFile(const std::string& filePath) {
    std::ofstream file(filePath);
    if (!file.is_open()) {
        fprintf(stderr,
                "Erreur : Impossible d'ouvrir le fichier avec le meilleur score pour y ecrire.\n");
        return;
    }
    file << getScore().getValue();
    file.close();
}

void Player::checkHighScore() {
    // if current score bigger than high score -> update high score
    if (getScore().getValue() > getHighScore().getValue()) {
        setHighScore(getScore());
        updateHighScoreFile(HIGH_SCORE_FILE);
    }
}

int Player::getHp() const {
    return _hp;
}
void Player::setHp(int nhp) {
    _hp = nhp;
}

bool Player::hasBallStored() {
    return _hasBallStored;
}

void Player::setHasBallStored(bool flag) {
    _hasBallStored = flag;
}

bool Player::hasGrabTimerExpired() {
    return _hasGrabDelayExpired;
}

void Player::setHasGrabTimerExpired(bool flag) {
    _hasGrabDelayExpired = flag;
}

void Player::incrementHp(int incr) {
    setHp(getHp() + incr);
}

bool Player::isDead() const {
    return getHp() <= 0;
}

GameController& Player::getController() {
    return _controller;
}

Score& Player::getScore() {
    return _score;
}

bool Player::hasBonusActive() {
    return (_bonus);
}

BonusInterface* Player::getBonus() {
    if (!hasBonusActive()) {
        // for debug purposes
        std::cerr << "Shouldn't get bonus without checking if there's one." << std::endl;
    }
    return _bonus;
}

void Player::setBonus(BonusInterface* bonus) {
    if (hasBonusActive()) {
        delete _bonus;
    }

    _bonus = bonus;
}

bool Player::canShootLaser() {
    return _canShootLaser;
}

void Player::setCanShootLaser(bool flag) {
    _canShootLaser = flag;
}

void Player::reset() {
    this->setBonus(nullptr);
    this->getController().updateUserAction(0);
    this->setHp(PLAYER_DEFAULT_HEALTH);
    this->getScore().setValue(0);
    this->setHasBallStored(true);
    this->setCanShootLaser(false);
}