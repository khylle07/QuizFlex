#include "include/FlashCard.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <limits>

using namespace std;

// Waits for the user to press Enter to return to the menu
void waitForEnter() {
    cin.ignore(1000, '\n');
    cout << "\nPress Enter to return to menu...";
    cin.get();
}

// Displays the FlashCard menu with options
void showFlashCardMenu() {
    system("cls");
    cout << "+========== FlashCard Menu ==========+\n"
         << "| 1. Play with Demo Questions        |\n"
         << "| 2. Play with Your Questions        |\n"
         << "| 3. Add Questions                   |\n"
         << "| 4. View Questions                  |\n"
         << "| 5. Return to Main Menu             |\n"
         << "+====================================+\n"
         << "Choice: ";
}

// FlashCard constructor initializes demo questions
FlashCard::FlashCard() {
    loadDemoQuestions();
}

// Loads a set of default demo questions into the game
void FlashCard::loadDemoQuestions() {
    demoQuestions = {
        {"A machine that processes information?", "Computer"},
        {"A network that connects computers.", "Internet"},
        {"A way to send messages online.", "Email"},
        {"A secret code for access", "Password "},
        {"A page or group of pages online.", "Website"}
    };
    shuffleQuestions();
}

// Randomizes the order of both demo and user questions
void FlashCard::shuffleQuestions() {
    random_shuffle(demoQuestions.begin(), demoQuestions.end());
    random_shuffle(userQuestions.begin(), userQuestions.end());
    currentQuestion = 0;
}

// Adds a new user-defined question and answer pair
void FlashCard::addQuestion(const string& question, const string& answer) {
    userQuestions.emplace_back(question, answer);
}

// Main logic for playing the FlashCard game
void FlashCard::playGame(int& knowledge, int& energy, bool useDemo) {
    system("cls");
    auto& questions = useDemo ? demoQuestions : userQuestions;

    // If no questions are available
    if (questions.empty()) {
        cout << "+=========================+\n"
             << "| No questions available! |\n"
             << "+=========================+\n";
        Sleep(2000);
        return;
    }

    // If all questions have been asked, reshuffle
    if (currentQuestion >= questions.size()) {
        cout << "+==========================+\n"
             << "| Reshuffling questions... |\n"
             << "+==========================+\n";
        shuffleQuestions();
        Sleep(1000);
        system("cls");
    }

    // Display current question and take answer
    auto& q = questions[currentQuestion];
    cout << "Question " << currentQuestion + 1 << "/" << questions.size() << ":\n"
         << q.first << "\nYour answer: ";

    string answer;
    getline(cin >> ws, answer); // ws clears leading whitespace

    // Convert both correct answer and user input to lowercase
    string correctLower = q.second;
    string answerLower = answer;
    transform(correctLower.begin(), correctLower.end(), correctLower.begin(), ::tolower);
    transform(answerLower.begin(), answerLower.end(), answerLower.begin(), ::tolower);

    // Check answer
    if (answerLower == correctLower) {
        cout << "Correct! +3 Knowledge\n";
        knowledge += 3;
    } else {
        cout << "Wrong! Correct answer: " << q.second << "\n-1 Energy\n";
        energy--;
    }

    currentQuestion++;
    Sleep(1500);
}

// Shows a list of either demo or user questions
void FlashCard::showQuestions(bool showDemo) const {
    const auto& questions = showDemo ? demoQuestions : userQuestions;
    cout << (showDemo ? "Demo" : "Your") << " Questions:\n";

    if (questions.empty()) {
        cout << "+================+\n"
             << "| None available |\n"
             << "+================+";
        return;
    }

    // Print questions and answers
    for (size_t i = 0; i < questions.size(); ++i) {
        cout << i + 1 << ". Q: " << questions[i].first
             << "\n   A: " << questions[i].second << "\n";
    }
}

// Manages the FlashCard game loop and menu options
void startFlashCardGame(GameStats& stats) {
    FlashCard game;
    int choice;
    string input;

    while (stats.energy > 0) {
        showFlashCardMenu();

        // Validate user input
        while (true) {
            cin >> choice;
            if (cin.fail() || (choice < 1 || choice > 5)) {
                cout << "+===================================+\n"
                     << "| Invalid choice! Please try again. |\n"
                     << "+===================================+\n";
                cin.clear();
                cin.ignore(1000, '\n');
            } else {
                break;
            }
        }

        switch (choice) {
            // Play with demo or user questions
            case 1: case 2: {
                bool useDemo = (choice == 1);
                while (stats.energy > 0) {
                    game.playGame(stats.knowledge, stats.energy, useDemo);
                    if (stats.energy <= 0) break;

                    cout << "+=====================+\n"
                         << "| Continue? (y/n): ";
                    getline(cin, input);
                    if (tolower(input[0]) != 'y') break;
                }
                break;
            }

            // Add custom questions
            case 3: {
                system("cls");
                cout << "+=====================================+\n"
                     << "| Add Questions (type 'quit' to stop) |\n"
                     << "+=====================================+\n";
                while (true) {
                    cin.ignore(1000, '\n');
                    string q, a;
                    cout << "Question: ";
                    getline(cin, q);
                    if (q == "quit") break;

                    cout << "Answer: ";
                    getline(cin, a);
                    game.addQuestion(q, a);
                    cout << "Added! Press Enter To Continue!\n";
                }
                break;
            }

            // View demo or user questions
            case 4: {
                system("cls");
                cout << "+==========+\n"
                     << "| View:    |\n"
                     << "| 1) Demo  |\n"
                     << "| 2) Yours |\n"
                     << "+==========+\n"
                     << "Choice: ";
                cin >> choice;
                game.showQuestions(choice == 1);
                waitForEnter();
                break;
            }

            // Exit FlashCard mode
            case 5:
                return;

            default:
                cout << "+================+\n"
                     << "| Invalid choice |\n"
                     << "+================+";
                Sleep(1000);
        }

        // Check for energy exhaustion
        if (stats.energy <= 0) {
            cout << "+================+\n"
                 << "| Out of energy! |\n"
                 << "+================+\n";
            Sleep(2000);
        }
    }
}
