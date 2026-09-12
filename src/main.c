#include "raylib.h"
#include "types.h"
#include "logic.h"
#include "data.h"  
#include "render.h"
#include <stdio.h> 
#include <stdbool.h>

extern GameState state;

Font arabicFont;

static int totalCards = 0;
static Flashcard gameCards[30];

static int totalScenarios = 0;
static Scenario gameScenarios[10];

int main(void) {
    InitWindow(1280, 720, "Polyglot Quest");
    
    // Change working directory to where the executable resides
    ChangeDirectory(GetApplicationDirectory());
    printf("[DEBUG] Current Working Directory: %s\n", GetWorkingDirectory());

    SetTargetFPS(60);

    int codepoints[1500];
    int count = 0;

    for (int i = 0x0020; i <= 0x007E; i++) codepoints[count++] = i; 
    for (int i = 0x0600; i <= 0x06FF; i++) codepoints[count++] = i; 
    for (int i = 0xFB50; i <= 0xFDFF; i++) codepoints[count++] = i; 
    for (int i = 0xFE70; i <= 0xFEFC; i++) codepoints[count++] = i; 

    if (FileExists("assets/fonts/amiri-regular.ttf")) {
        arabicFont = LoadFontEx("assets/fonts/amiri-regular.ttf", 64, codepoints, count);
        printf("[SUCCESS] Loaded Amiri font.\n");
    } else {
        printf("[WARNING] Font not found at assets/fonts/amiri-regular.ttf!\n");
        arabicFont = GetFontDefault();
    }

    totalCards = loadFlashcards(gameCards);
    totalScenarios = loadScenarios(gameScenarios);

    loadProgress(&state);

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