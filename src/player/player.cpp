#include "player.hpp"

int Player::getHp() const{return hp;}
void Player::setHp(int nhp) {hp = nhp;}

void Player::incrementHp(int incr) {setHp(getHp() + incr);}

bool Player::isDead() const {return getHp() <= 0;}

GameController& Player::getController() {return controller;}

Score& Player::getScore() {return score;}

std::vector<BonusInterface*>& Player::getBonus() {return bonus;}

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