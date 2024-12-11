#include "score.hpp"

class Score{
    private:
        float value;
    public:
        Score(float value): float{float}{};

        float getValue() {return value;}
        void setValue() {value = v;}

        void addScore(int increment){
            float new_value = getValue() + increment;
            setValue(new_value);
        }

        friend std::ostream& operator<<(std::ostream& os, float& value);
};

std::ostream& operator<<(std::ostream& os, float& value) {
        std::cout<< "Score: " << getValue();
        return os;
    }
