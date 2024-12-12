#include "score.hpp"

class Score{
    private:
        int value;
    public:
        Score(int value): value{value}{};

        int getValue() const {return value;}
        void setValue(int v) {value = v;}

        void addScore(int increment){
            int new_value = getValue() + increment;
            setValue(new_value);
        }

        friend std::ostream& operator<<(std::ostream& os, Score& score);
};

std::ostream& operator<<(std::ostream& os, Score& score) {
        os << "Score: " << score.getValue();
        return os;
    }
