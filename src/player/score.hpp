#pragma once

#include <iostream>

class Score{

    private:

        int _value;

    public:

        Score(int value):
            _value{value} {}

        ~Score() = default;

        int getValue() const;
        void setValue(int v);
        void addScore(int increment);
        friend std::ostream& operator<<(std::ostream& os, Score& score);
};