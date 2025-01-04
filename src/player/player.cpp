#include "player.hpp"

Score Player::readHighScoreFromFile(const std::string& filePath) const {
    std::ifstream file(filePath);

    if (!file.is_open()) {
        fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier avec le meilleur score. Meilleur score mis a 0.\n");
        return Score(0);
    }

    int highScoreValue = 0;
    file >> highScoreValue;

    if (file.fail()) {
        fprintf(stderr, "Erreur : Impossible de lire le fichier avec le meilleur score. Meilleur score mis a 0.\n");
        return Score(0);
    }

    return Score(highScoreValue);
}

Score& Player::getHighScore() {return _highScore;};
void Player::setHighScore(const Score& score) {_highScore = score;}

void Player::updateHighScoreFile(const std::string& filePath) {
    std::ofstream file(filePath);
    if (!file.is_open()) {
        fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier avec le meilleur score pour y ecrire.\n");
        return;
    }
    file << getScore().getValue();
    file.close();
}

void Player::checkHighScore(){
    // if current score bigger than high score -> update high score
    if (getScore().getValue() > getHighScore().getValue()){
        setHighScore(getScore());
        updateHighScoreFile(HIGH_SCORE_FILE);
    }
}


int Player::getHp() const{return _hp;}
void Player::setHp(int nhp) {_hp = nhp;}

bool Player::hasBallStored() {return _hasBallStored;}

void Player::setHasBallStored(bool flag) {_hasBallStored = flag;}

void Player::incrementHp(int incr) {setHp(getHp() + incr);}

bool Player::isDead() const {return getHp() <= 0;}

GameController& Player::getController() {return _controller;}

Score& Player::getScore() {return _score;}

std::vector<BonusInterface*>& Player::getBonus() {return _bonus;}

void Player::addBonus(BonusInterface* b){
    getBonus().push_back(b);
}

void Player::removeBonus(BonusInterface* b){
    for (auto it = getBonus().begin(); it != getBonus().end(); ++it) {
        if (*it == b) { 
            getBonus().erase(it); 
            break;
        }
    }
}