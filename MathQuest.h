#ifndef MATHQUEST_H
#define MATHQUEST_H
#include "GameProcess.h"

#include <string>

class Calculation {
public:
    Calculation();
    bool operators(int num1, int num2, int& energy, int& knowledge);
    double division(int num1, int num2);
    int addition(int num1, int num2);
    int subtraction(int num1, int num2);
    int multiplication(int num1, int num2);

    int getCorrectAnswers() const { return correctAnswers; }

private:
    int level;
    int correctAnswers;
};

void GameDifficulty();
void StartMathGame(int& knowledge, int& energy);

#endif
