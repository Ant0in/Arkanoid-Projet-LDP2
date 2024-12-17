#pragma once

#include <iostream>

class Score{
    private:
        float value;
    public:
        Score(int value);

        float getValue() const;
        void setValue(int v);

        void addScore(int increment);

        friend std::ostream& operator<<(std::ostream& os, Score& score);
};