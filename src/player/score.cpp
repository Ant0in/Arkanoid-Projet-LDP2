#include "score.hpp"

int Score::getValue() const {return value;}
void Score::setValue(int v) {value = v;}

void Score::addScore(int increment){
    int new_value = getValue() + increment;
    setValue(new_value);
}

std::ostream& operator<<(std::ostream& os, Score& score) {
        os << "Score: " << score.getValue();
        return os;
    }
