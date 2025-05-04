#ifndef FLASHCARD_H
#define FLASHCARD_H

#include <vector>
#include <string>

using namespace std;

class FlashCard {
public:
    FlashCard();
    void addQuestion(const string& question, const string& answer);
    void playGame(int& knowledge, int& energy, bool useDemoQuestions);
    void showQuestions(bool showDemo) const;

private:
    void loadDemoQuestions();
    void shuffleQuestions();

    vector<pair<string, string>> demoQuestions;
    vector<pair<string, string>> userQuestions;
    size_t currentQuestion = 0;
};

void startFlashCardGame(int& knowledge, int& energy);

#endif
