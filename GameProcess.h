#ifndef GAMEPROCESS_H
#define GAMEPROCESS_H

#include <string>

// Enum class to represent the different game modes
enum class GameType {
    MathQuest = 1,      // Option 1: Play MathQuest
    FlashCard = 2,      // Option 2: Play FlashCard
    RestoreEnergy = 3,  // Option 3: Restore player's energy
    Exit = 0            // Option 0: Exit the game
};

// Holds the player's current stats: knowledge and energy
class GameStats {
public:
    int knowledge;  // Player's accumulated knowledge
    int energy;     // Player's current energy level

    GameStats();            // Constructor to initialize stats
    void showStatus() const; // Displays current stats
    void energyGame();       // Allows player to restore energy using knowledge
};

// Controls the main flow of the game
class GameProcess {
public:
    void run(); // Starts the game loop

private:
    GameStats stats; // Stores player stats

    void showWelcome();              // Displays the welcome screen and handles start input
    GameType getUserGameChoice() const; // Asks the user for their choice of game mode
    void playMathQuest();           // Launches MathQuest game mode
    void playFlashCard();           // Launches FlashCard game mode
};

// Utility function to print a message with a typing effect
void printLetterByLetter(const std::string& message);

#endif
