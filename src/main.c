#include "raylib.h"
#include "types.h"
#include "logic.h"
#include "data.h"  
#include "render.h"
#include <stdio.h> 
#include <stdbool.h>

extern GameState state;
extern void saveProgress(const GameState* state);
extern void loadProgress(GameState* state);
Font arabicFont;

static int totalCards = 0;
static Flashcard gameCards[30];

static int totalScenarios = 0;
static Scenario gameScenarios[3];

int main(void) {
    InitWindow(1280, 720, "Polyglot Quest");
    arabicFont = LoadFontEx("assets/fonts/amiri-regular.ttf", 64, NULL, 0);
    SetTargetFPS(60);

    // Load Flashcards and Scenarios
    totalCards = loadFlashcards(gameCards);
    totalScenarios = loadScenarios(gameScenarios);

    loadProgress(&state);

    printf("Successfully initialized backend! Loaded %d cards and %d scenarios.\n", totalCards, totalScenarios);

    state.currentScreen = MENU_SCREEN;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground((Color){13, 27, 42, 255}); 

        RenderCurrentScreen(gameCards, totalCards);

        EndDrawing();
    }

    saveProgress(&state);
    UnloadFont(arabicFont);

    CloseWindow();
    return 0;
}