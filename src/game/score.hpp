#include <iostream>

class Score{
    private:
        float value;
    public:
        Score(float value);

        float getValue();
        void setValue(float v);

        void addScore(int increment);

        friend std::ostream& operator<<(std::ostream& os, float& value);
};