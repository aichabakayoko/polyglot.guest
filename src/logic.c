#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
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

void revealCard(void) {
    state.isRevealed = 1; 
}

void nextCard(void) {
    state.currentCardIndex += 1;
    state.isRevealed = 0; 
    // Flashcard deck wraps back to 0 when reaching the limit
    if (state.currentCardIndex >= TOTAL_FLASHCARDS) {
        state.currentCardIndex = 0;
    }
}

int matchesCategory(const char* cardCategory, const char* selectedCategory) {
    if (selectedCategory == NULL || selectedCategory[0] == '\0') {
        return 1;
    }
    return strcmp(cardCategory, selectedCategory) == 0;
}

void checkAnswer(int selectedIndex, int correctIndex, int scoreValue) {
    if (selectedIndex == correctIndex) {
        state.totalScore += scoreValue;
        state.correctCount += 1;
    } else {
        state.wrongCount += 1;
    }
}

void nextScenarioStep(void) {
    state.currentScenarioStep += 1;
    
    // Advances through all 10 scenarios then transitions to Progress screen
    if (state.currentScenarioStep >= TOTAL_SCENARIOS) {
        goToScreen(PROGRESS_SCREEN);
    }
}

float calculateAccuracy(void) {
    int totalAnswers = state.correctCount + state.wrongCount;
    // Guard against division by zero
    if (totalAnswers == 0) {
        return 0.0f;
    }
    return ((float)state.correctCount / (float)totalAnswers) * 100.0f;
}

int getStarRating(void) {
    int score = state.totalScore;
    
    if (score >= 70) return 5;
    if (score >= 55) return 4;
    if (score >= 40) return 3;
    if (score >= 20) return 2;
    
    return 1;
}

void resetGame(void) {
    state.totalScore = 0;
    state.correctCount = 0;
    state.wrongCount = 0;
    state.currentCardIndex = 0;
    state.currentScenarioStep = 0;
    state.isRevealed = 0;
    state.currentScreen = MENU_SCREEN;
}

float calculateMastery(const char* category) {
    // Calculates overall accuracy percentage across answered questions
    return calculateAccuracy();
}