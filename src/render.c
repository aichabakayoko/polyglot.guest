#include "render.h"
#include "ui_menu.h"
#include "ui_flashcards.h"
#include "ui_scenarios.h"
#include "ui_progress.h"
#include "ui_settings.h"
#include "ui_infobar.h"

extern GameState state;
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