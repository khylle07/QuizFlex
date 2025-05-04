#include <iostream>
#include "include/MathQuest.h"
#include "include/GameProcess.h"
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <cmath> // for fabs()

using namespace std;

void StartMathGame(int& knowledge, int& energy) {
    srand(time(0));
    string choice;
    Calculation op;

    while(true) {
        cout << "Input the Letter of Choice: ";
        cin >> choice;
        choice[0] = toupper(choice[0]);

        if(choice == "A" || choice == "B" || choice == "C" ||
           choice == "D" || choice == "E" || choice == "M") {
            break;
        }
        cout << "\nInvalid choice! ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    while (energy > 0) {
        int correctAnswers = 0;

        for (int i = 0; i < 10; i++) {
            int num1, num2;
            system("cls");
            cout << "Knowledge: " << knowledge << endl;
            cout << "Energy: " << energy << "\n\n";

            switch(choice[0]) {
                case 'A':
                    num1 = rand() % 10;
                    num2 = rand() % 10;
                    break;
                case 'B':
                    num1 = rand() % 100;
                    num2 = rand() % 100;
                    break;
                case 'C':
                    num1 = rand() % 1000;
                    num2 = rand() % 1000;
                    break;
                case 'D':
                    num1 = rand() % 10000;
                    num2 = rand() % 10000;
                    break;
                case 'E':
                    num1 = rand() % 100000;
                    num2 = rand() % 100000;
                    break;
                case 'M':
                    cout << "Returning To Menu!!!";
                    Sleep(1000);
//                    ShowGameChoice();
            }

            if (op.operators(num1, num2, energy, knowledge)) {
                correctAnswers++;
            }
        }

        system("cls");
        cout << "Level Complete!\n";
        cout << "Correct Answers: " << correctAnswers << "/10\n";
        cout << "Knowledge Gained: " << correctAnswers * 3 << endl;
        cout << "Energy Remaining: " << energy << endl << endl;

        cout << "Do You Want To Restart The Game?(y/n)";
        cin >> choice;
        choice[0] = toupper(choice[0]);

        if(choice == "Y"){
            break;
        }else if(choice == "N"){
            cout << "Returning To Menu!!!";
            Sleep(1000);
       //     ShowGameChoice();
        }else{
            cout << "Invalid Choice! ";
        }
        Sleep(2000);
    }
    cout << "Game Over! You ran out of energy.\n";
    Sleep(2000);
}

Calculation::Calculation() : level(1), correctAnswers(0) {}

bool Calculation::operators(int num1, int num2, int& energy, int& knowledge) {
    double userAnswer, correctAnswer;
    int op = rand() % 4 + 1;

    switch(op) {
        case 1:
            correctAnswer = addition(num1, num2);
            cout << num1 << " + " << num2 << " = ? ";
            break;
        case 2:
            correctAnswer = subtraction(num1, num2);
            cout << num1 << " - " << num2 << " = ? ";
            break;
        case 3:
            correctAnswer = multiplication(num1, num2);
            cout << num1 << " * " << num2 << " = ? ";
            break;
        case 4:
            num2 = num2 == 0 ? 1 : num2;
            correctAnswer = division(num1, num2);
            cout << num1 << " / " << num2 << " = ? ";
            break;
    }

    cin >> userAnswer;
    cin.clear();
    cin.ignore(1000, '\n');

    bool isCorrect;
    if (op == 4) {
        isCorrect = fabs(userAnswer - correctAnswer) < 0.01;
    } else {
        isCorrect = (userAnswer == correctAnswer);
    }

    if (isCorrect) {
        cout << "Correct! +3 Knowledge\n";
        knowledge += 3;
        Sleep(1000);
        return true;
    } else {
        cout << "Wrong! The correct answer was " << correctAnswer << endl;
        cout << "-1 Energy\n";
        energy--;
        Sleep(1000);
        return false;
    }
}

double Calculation::division(int num1, int num2) {
    return static_cast<double>(num1) / num2;
}

int Calculation::multiplication(int num1, int num2) {
    return num1 * num2;
}

int Calculation::subtraction(int num1, int num2) {
    return num1 - num2;
}

int Calculation::addition(int num1, int num2) {
    return num1 + num2;
}
