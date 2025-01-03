#include "player.hpp"

int Player::getHp() const{return _hp;}
void Player::setHp(int nhp) {_hp = nhp;}

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