#include <iostream>
#include <thread>
#include <windows.h>
#include "include/GameProcess.h"
#include "include/MathQuest.h"
#include "include/FlashCard.h"
#include <algorithm> // for remove

using namespace std;

void ChooseGameDifficulty();

//==================================================================================
void printLetterByLetter(const string& message) {
    for (char c : message) {
        cout << c;
        Sleep(2);
    }
}

//==================================================================================

void ChooseGameDifficulty() {
    string print;
    system("cls");

    printLetterByLetter("Choose Difficulty Level\n");
    printLetterByLetter("A. Beginner\n");
    printLetterByLetter("B. Basic\n");
    printLetterByLetter("C. Moderate");
    printLetterByLetter("E. Expert");
    printLetterByLetter("M. Return To Menu");
}

void GameInstruction() {
    string print;
    cout << "+-------------------------------------+\n";
    cout << "|               QuizFlex              |\n";
    cout << "+-------------------------------------+\n";
    print += "Welcome to the game!!!\n";
    print += "There are a total of 2 Study Tools.\n";
    print += "Each game can earn you knowledge that will help restore your lost energy.\n";

    printLetterByLetter(print);
    GameStart();
}

void GameStart(){
    string choice, print;

    do{
        print = "Do You Want To Play The Game?(y/n): ";
        printLetterByLetter(print);
        cin >> choice;

        if (choice == "Y" || choice == "y") {
            print = "Great! Let's continue.";
            printLetterByLetter(print);
            Sleep(1000);
            system("cls");
        } else if (choice == "N" || choice == "n") {
            print = "Awwwww man.....\n";
            printLetterByLetter(print);
            exit(0);
        } else {
            cout << "Invalid input." << endl;
            printLetterByLetter(print);
        }
    }while(choice != "y" && choice != "Y");
}

bool ShowGameChoice(){
    system("cls");
    GameStats stats;
    stats.showStatus();
    string print;
    int choice;
    int knowledge = stats.knowledge;
    int energy = stats.energy;

    cout << endl;
    print += "\nChoose an action(Press 0 To Exit)\n";
    print += "1. Mathematical Operation\n";
    print += "2. FlashCard\n";
    printLetterByLetter(print);

    print = "Enter choice: ";
    printLetterByLetter(print);
    cin >> choice;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        system("cls");
        cout << "Invalid input. Try again.\n";
        return true; // Continue the game loop
    }

    switch (choice) {
        case 1:
            cout << "Entering.... Math Quest\n";
            StartMathGame(knowledge, energy);
            break;
        case 2:
            cout << "Entering.... FlashCards\n";
            startFlashCardGame(knowledge, energy);
            break;
        case 0:
            cout << "Exiting.....";
            return false; // Exit the game loop
        default:
            cout << "Invalid choice. Try again.\n";
            cin.clear();
            cin.ignore(100, '\n');
            break;
    }
    return true; // Continue the game loop
}

GameStats::GameStats() {
    energy = 10;
    knowledge = 0;
}

void GameStats::showStatus() {
    cout << "+====================+\n";
    printLetterByLetter("| Student Status     |\n");
    printLetterByLetter("| Knowledge: ");
    cout << knowledge << "       |" << endl;
    printLetterByLetter("| Energy: ");
    cout << energy << "         |" << endl;
    cout << "+====================+\n";
}


