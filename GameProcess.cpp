#include "include/GameProcess.h"
#include "include/MathQuest.h"
#include "include/FlashCard.h"
#include <iostream>
#include <windows.h>
#include <algorithm>
#include <cctype>
#include <ctime>
#include <cstdlib>
#include <limits>

using namespace std;

// Constructor for GameStats: initializes knowledge to 0 and energy to 10
GameStats::GameStats() : knowledge(0), energy(10) {}

// Allows player to restore energy at the cost of knowledge
void GameStats::energyGame() {
    int choice;
    system("cls");
    printLetterByLetter("Would you like to restore your energy? (0 = Exit | 1 = Yes):\n");

    // Input validation loop
    while(true){
        cout << "Choice: ";
        cin >> choice;
        if(choice != 1 && choice != 0){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid Input Try Again!!!\n";
        } else {
            break;
        }
    }

    // Energy restoration logic if player chooses yes and has enough knowledge
    if (choice == 1 && knowledge > 5) {
        srand(time(0));
        knowledge -= rand() % 5 + 1;  // Deduct random amount of knowledge
        energy += rand() % 10 + 1;    // Add random amount of energy
        if (energy > 99) energy = 99;

        // Resting animation
        printLetterByLetter("Resting");
        for (int i = 0; i < 5; i++) {
            cout << ".";
            Sleep(300);
        }
        cout << "\nEnergy Restored!\n";
        Sleep(1000);
        system("cls");

    } else {
        // Not enough knowledge to restore energy
        cout << "+========================+\n";
        printLetterByLetter("| Insufficient Knowledge!!! |\n");
        cout << "+========================+\n";
        Sleep(2000);
        system("cls");
        return;
    }
}

// Displays current knowledge and energy level of the player
void GameStats::showStatus() const {
    cout << "+====================+\n";
    printLetterByLetter("| Student Status     |\n");
    cout << "| Knowledge: " << knowledge << "\n";
    cout << "| Energy: " << energy << "\n";
    cout << "+====================+\n";
}

// Main game loop: shows menu, gets user input, and runs selected game mode
void GameProcess::run() {
    showWelcome();
    while (true) {
        stats.showStatus();
        GameType choice = getUserGameChoice();
        switch (choice) {
            case GameType::MathQuest:
                playMathQuest(); break;
            case GameType::FlashCard:
                playFlashCard(); break;
            case GameType::RestoreEnergy:
                stats.energyGame(); break;
            case GameType::Exit:
                cout << "Thanks for playing!\n";
                return;
        }
    }
}

// Shows intro and asks player if they want to play or exit
void GameProcess::showWelcome() {
    string start;
    cout << "+-------------------------------------+\n";
    cout << "|               QuizFlex              |\n";
    cout << "+-------------------------------------+\n";

    printLetterByLetter(
        "Welcome to the game!\n"
        "There are 2 Study Tools.\n"
        "Earn Knowledge and spend it to restore Energy.\n"
        "Would you like to play the game? (Y = yes | N = no)\n"
    );

    // Input loop for yes/no
    while (true) {
        printLetterByLetter("Enter your choice: ");
        getline(cin, start);
        transform(start.begin(), start.end(), start.begin(), ::toupper);

        if (start == "Y" || start == "YES") {
            system("cls");
            break;
        } else if (start == "N" || start == "NO") {
            printLetterByLetter("Exiting the game...\n");
            exit(0);
        } else {
            printLetterByLetter("Invalid input. Try again.\n");
        }
    }
}

// Displays the main menu and gets the user's selected game mode
GameType GameProcess::getUserGameChoice() const {
    int input;

    cout << "\nChoose an action:\n";
    cout << "0. Exit\n1. Mathematical Operation\n2. FlashCard\n3. Restore Energy\n";

    // Input validation loop
    while (true) {
        cout << "Enter choice: ";
        cin >> input;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (cin.fail() || input < 0 || input > 3) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Try again.\n";
        } else {
            break;
        }
    }

    return static_cast<GameType>(input);
}

// Starts the MathQuest game
void GameProcess::playMathQuest() {
    StartMathGame(stats);
}

// Starts the FlashCard game
void GameProcess::playFlashCard() {
    startFlashCardGame(stats);
}

// Prints a string letter by letter with a small delay for effect
void printLetterByLetter(const string& message) {
    for (char c : message) {
        cout << c;
        Sleep(2);
    }
}
