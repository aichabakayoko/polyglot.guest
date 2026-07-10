#include "logic.h"

GameState state;

void initGame(void) {
    state.currentScreen = MENU_SCREEN;
    state.totalScore = 0;
    state.correctCount = 0;
    state.wrongCount = 0;
    state.currentCardIndex = 0;
    state.currentScenarioStep = 0;
    state.isRevealed = 0;
}

void goToScreen(Screen s) {
    state.currentScreen = s;
}

void handleMenuNavigation(int choice) {
    if (choice == 1) {
        goToScreen(FLASHCARD_SCREEN);
    } else if (choice == 2) {
        goToScreen(SCENARIO_SCREEN);
    } else if (choice == 3) {
        goToScreen(PROGRESS_SCREEN);
    }
}

void backToMenu(void) {
    goToScreen(MENU_SCREEN);
}