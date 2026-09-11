#include "render.h"
#include "ui_menu.h"
#include "ui_flashcards.h"
#include "ui_scenarios.h"
#include "ui_progress.h"
#include "ui_settings.h"
#include "ui_infobar.h"

extern GameState state;
extern Scenario scenarios[]; // Updated from gameScenarios to match data.c
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
            drawScenario(scenarios, 10); // Pass scenarios array
            break;
        case PROGRESS_SCREEN:
            drawProgress();
            break;
        default:
            break;
    }
}