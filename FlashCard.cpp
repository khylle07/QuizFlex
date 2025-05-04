#include "include/FlashCard.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <windows.h>

FlashCard::FlashCard() {
    loadDemoQuestions();
}

void FlashCard::loadDemoQuestions() {
    demoQuestions = {
        {"Capital of France?", "Paris"},
        {"2 + 2?", "4"},
        {"Largest planet?", "Jupiter"},
        {"Romeo and Juliet author?", "Shakespeare"},
        {"Chemical symbol for gold?", "Au"}
    };
    shuffleQuestions();
}

void FlashCard::shuffleQuestions() {
    random_shuffle(demoQuestions.begin(), demoQuestions.end());
    random_shuffle(userQuestions.begin(), userQuestions.end());
    currentQuestion = 0;
}

void FlashCard::addQuestion(const string& question, const string& answer) {
    userQuestions.emplace_back(question, answer);
}

void FlashCard::playGame(int& knowledge, int& energy, bool useDemo) {
    system("cls");
    auto& questions = useDemo ? demoQuestions : userQuestions;

    if (questions.empty()) {
        cout << "No questions available!\n";
        Sleep(2000);
        return;
    }

    if (currentQuestion >= questions.size()) {
        cout << "Reshuffling questions...\n";
        shuffleQuestions();
        Sleep(1000);
        system("cls");
    }

    auto& q = questions[currentQuestion];
    cout << "Question " << currentQuestion + 1 << "/" << questions.size() << ":\n"
         << q.first << "\nYour answer: ";

    string answer;
    getline(cin >> ws, answer);

    string correctLower = q.second;
    string answerLower = answer;
    transform(correctLower.begin(), correctLower.end(), correctLower.begin(), ::tolower);
    transform(answerLower.begin(), answerLower.end(), answerLower.begin(), ::tolower);

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

void FlashCard::showQuestions(bool showDemo) const {
    const auto& questions = showDemo ? demoQuestions : userQuestions;
    cout << (showDemo ? "Demo" : "Your") << " Questions:\n";

    if (questions.empty()) {
        cout << "None available\n";
        return;
    }

    for (size_t i = 0; i < questions.size(); ++i) {
        cout << i + 1 << ". Q: " << questions[i].first
             << "\n   A: " << questions[i].second << "\n";
    }
}

void showFlashCardMenu() {
    system("cls");
    cout << "+----- FlashCard Menu -----+\n"
         << "1. Play with Demo Questions\n"
         << "2. Play with Your Questions\n"
         << "3. Add Questions\n"
         << "4. View Questions\n"
         << "5. Return to Main Menu\n"
         << "Choice: ";
}

void startFlashCardGame(int& knowledge, int& energy) {
    FlashCard game;
    int choice;
    string input;

    while (energy > 0) {
        showFlashCardMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: case 2: {
                bool useDemo = (choice == 1);
                while (energy > 0) {
                    game.playGame(knowledge, energy, useDemo);
                    if (energy <= 0) break;

                    cout << "\nContinue? (y/n): ";
                    getline(cin, input);
                    if (tolower(input[0]) != 'y') break;
                }
                break;
            }
            case 3: {
                system("cls");
                cout << "Add Questions (type 'quit' to stop)\n";
                while (true) {
                    string q, a;
                    cout << "Question: ";
                    getline(cin, q);
                    if (q == "quit") break;

                    cout << "Answer: ";
                    getline(cin, a);
                    game.addQuestion(q, a);
                    cout << "Added!\n";
                }
                break;
            }
            case 4: {
                system("cls");
                cout << "View:\n1. Demo\n2. Yours\nChoice: ";
                cin >> choice;
                game.showQuestions(choice == 1);
                cout << "\nPress Enter...";
                cin.ignore();
                cin.ignore();
                break;
            }
            case 5:
                return;
            default:
                cout << "Invalid choice\n";
                Sleep(1000);
        }

        if (energy <= 0) {
            cout << "Out of energy!\n";
            Sleep(2000);
        }
    }
}
