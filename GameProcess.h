#ifndef GAMEPROCESS_H
#define GAMEPROCESS_H
#include <string>
using namespace std;

void PrintMessage(string message);
void printLetterByLetter(const string& message);

// Main game loop
void GameInstruction();
void GameStart();
void processChoice();
bool ShowGameChoice();
void GameDifficulty();

class GameStats {
public:
    int knowledge;
    int energy;

    GameStats();
    void showStatus();
};
#endif
