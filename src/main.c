#include "raylib.h"
#include "types.h"
#include "logic.h"

extern GameState state;

void drawMenu() {

    DrawText("POLYGLOT QUEST", 1280 / 2 - MeasureText("POLYGLOT QUEST", 48) / 2, 100, 48, (Color){233, 196, 106, 255}); 
    DrawText("Learn Arabic. Live the Language.", 1280 / 2 - MeasureText("Learn Arabic. Live the Language.", 20) / 2, 160, 20, (Color){245, 237, 208, 255});

    Rectangle btnFlashcards = { 1280 / 2 - 150, 260, 300, 50 };
    Rectangle btnScenario   = { 1280 / 2 - 150, 340, 300, 50 };
    Rectangle btnProgress   = { 1280 / 2 - 150, 420, 300, 50 };
    Rectangle btnExit       = { 1280 / 2 - 150, 500, 300, 50 };

    Vector2 mousePos = GetMousePosition();

    Color colorFlashcards = (Color){30, 140, 58, 255}; 
    if (CheckCollisionPointRec(mousePos, btnFlashcards)) {
        colorFlashcards = (Color){40, 180, 75, 255}; 
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            state.currentScreen = FLASHCARD_SCREEN; 
        }
    }
    DrawRectangleRec(btnFlashcards, colorFlashcards);
    DrawText("FLASHCARDS", btnFlashcards.x + (btnFlashcards.width / 2) - (MeasureText("FLASHCARDS", 20) / 2), btnFlashcards.y + 15, 20, WHITE);

    Color colorScenario = (Color){27, 58, 92, 255}; 
    if (CheckCollisionPointRec(mousePos, btnScenario)) {
        colorScenario = (Color){38, 81, 128, 255}; 
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            state.currentScreen = SCENARIO_SCREEN;
        }
    }
    DrawRectangleRec(btnScenario, colorScenario);
    DrawText("SCENARIO MODE", btnScenario.x + (btnScenario.width / 2) - (MeasureText("SCENARIO MODE", 20) / 2), btnScenario.y + 15, 20, WHITE);

    Color colorProgress = (Color){74, 45, 140, 255}; 
    if (CheckCollisionPointRec(mousePos, btnProgress)) {
        colorProgress = (Color){100, 61, 190, 255}; 
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            state.currentScreen = PROGRESS_SCREEN;
        }
    }
    DrawRectangleRec(btnProgress, colorProgress);
    DrawText("PROGRESS", btnProgress.x + (btnProgress.width / 2) - (MeasureText("PROGRESS", 20) / 2), btnProgress.y + 15, 20, WHITE);

    Color colorExit = (Color){140, 28, 28, 255}; 
    if (CheckCollisionPointRec(mousePos, btnExit)) {
        colorExit = (Color){190, 38, 38, 255}; 
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            CloseWindow(); 
        }
    }
    DrawRectangleRec(btnExit, colorExit);
    DrawText("EXIT", btnExit.x + (btnExit.width / 2) - (MeasureText("EXIT", 20) / 2), btnExit.y + 15, 20, WHITE);
}

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