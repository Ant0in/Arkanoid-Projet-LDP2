#pragma once

#include <iostream>

class Score{
    private:
        int value;
    public:
        Score(int value): value{value}{}

        int getValue() const;
        void setValue(int v);

        void addScore(int increment);

        friend std::ostream& operator<<(std::ostream& os, Score& score);
};