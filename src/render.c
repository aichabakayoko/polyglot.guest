#include "render.h"
#include "ui_menu.h"
#include "ui_flashcards.h"
#include "ui_scenarios.h"
#include "ui_progress.h"

extern GameState state;
extern void saveProgress(const GameState* state);
extern void loadProgress(GameState* state);

// Global scenarios array and count exported from data.c
extern Scenario gameScenarios[];
extern int totalScenarios;

void RenderCurrentScreen(Flashcard* gameCards, int totalCards) {
    switch (state.currentScreen) {
        case MENU_SCREEN:
            drawMenu();
            break;
        case FLASHCARD_SCREEN:
            drawFlashcard(gameCards, totalCards);
            break;
        case SCENARIO_SCREEN:
            drawScenario(gameScenarios, 10);
            break;
        case PROGRESS_SCREEN:
            drawProgress();
            break;
        default:
            break;
    }
}