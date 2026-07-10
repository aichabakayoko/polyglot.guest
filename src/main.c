#include "raylib.h"
#include "types.h"
#include "logic.h"

extern GameState state;

void drawMenu() {}
void drawFlashcard() {}
void drawScenario() {}
void drawProgress() {}

int main() {
    InitWindow(1280, 720, "Polyglot Quest");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground((Color){13, 27, 42, 255}); 

        switch (state.currentScreen) {
            case MENU_SCREEN:
                drawMenu(); 
                break;
            case FLASHCARD_SCREEN:
                drawFlashcard();
                break;
            case SCENARIO_SCREEN:
                drawScenario(); 
                break;
            case PROGRESS_SCREEN:
                drawProgress(); 
                break;
        }

        EndDrawing();
    }
    CloseWindow();
    return 0;
}