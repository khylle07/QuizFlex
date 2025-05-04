#include <iostream>
#include "include/GameProcess.h"
#include "include/MathQuest.h"
#include "include/FlashCard.h"
#include <windows.h>
#include <vector>
#include <algorithm>

int main() {
    GameInstruction();
    while(ShowGameChoice()) {
        // The loop continues as long as ShowGameChoice returns true
    }
    return 0;
}
