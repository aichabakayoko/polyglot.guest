#include "raylib.h"
#include "types.h"
#include "logic.h"
#include <stdbool.h> // Ensure standard C boolean support

extern GameState state;

// Struct to keep track of flashcard data inside this UI
typedef struct {
    const char* arabic;
    const char* transliteration;
    const char* english;
    bool isRevealed;
} Flashcard;

// Global/Static instance for our test flashcard
static Flashcard sampleCard = {
    .arabic = "مَرْحَبًا",
    .transliteration = "Marhaban",
    .english = "Hello / Welcome",
    .isRevealed = false
};

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
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) { // Fixed to standard Raylib enum
            state.currentScreen = FLASHCARD_SCREEN; 
        }
    }
    DrawRectangleRec(btnFlashcards, colorFlashcards);
    DrawText("FLASHCARDS", btnFlashcards.x + (btnFlashcards.width / 2) - (MeasureText("FLASHCARDS", 20) / 2), btnFlashcards.y + 15, 20, WHITE);

    Color colorScenario = (Color){27, 58, 92, 255}; 
    if (CheckCollisionPointRec(mousePos, btnScenario)) {
        colorScenario = (Color){38, 81, 128, 255}; 
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            state.currentScreen = SCENARIO_SCREEN;
        }
    }
    DrawRectangleRec(btnScenario, colorScenario);
    DrawText("SCENARIO MODE", btnScenario.x + (btnScenario.width / 2) - (MeasureText("SCENARIO MODE", 20) / 2), btnScenario.y + 15, 20, WHITE);

    Color colorProgress = (Color){74, 45, 140, 255}; 
    if (CheckCollisionPointRec(mousePos, btnProgress)) {
        colorProgress = (Color){100, 61, 190, 255}; 
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            state.currentScreen = PROGRESS_SCREEN;
        }
    }
    DrawRectangleRec(btnProgress, colorProgress);
    DrawText("PROGRESS", btnProgress.x + (btnProgress.width / 2) - (MeasureText("PROGRESS", 20) / 2), btnProgress.y + 15, 20, WHITE);

    Color colorExit = (Color){140, 28, 28, 255}; 
    if (CheckCollisionPointRec(mousePos, btnExit)) {
        colorExit = (Color){190, 38, 38, 255}; 
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            CloseWindow(); 
        }
    }
    DrawRectangleRec(btnExit, colorExit);
    DrawText("EXIT", btnExit.x + (btnExit.width / 2) - (MeasureText("EXIT", 20) / 2), btnExit.y + 15, 20, WHITE);
}

void drawFlashcard() {
    // 1. Clean background fill matching your theme
    ClearBackground((Color){13, 27, 42, 255}); 

    // Layout configuration coordinates adjusted to look proportional on 1280x720 window
    Rectangle revealBtn = { 510, 520, 120, 45 };
    Rectangle nextBtn = { 650, 520, 120, 45 };

    // 2. Left Sidebar (Categories)
    DrawRectangle(40, 40, 220, 640, DARKGRAY);
    DrawText("CATEGORIES", 60, 60, 20, GOLD);
    DrawRectangle(50, 110, 200, 45, MAROON); 
    DrawText("Basics", 70, 122, 18, WHITE);

    // 3. Central Flashcard (Parchment color layout)
    Color parchment = (Color){ 245, 237, 208, 255 };
    DrawRectangleRounded((Rectangle){ 320, 100, 640, 380 }, 0.04f, 4, parchment);
    
    // Centers text inside parchment layout
    DrawText(sampleCard.arabic, 320 + (640/2) - (MeasureText(sampleCard.arabic, 48)/2), 160, 48, BLACK);
    DrawText(sampleCard.transliteration, 320 + (640/2) - (MeasureText(sampleCard.transliteration, 22)/2), 250, 22, DARKGRAY);

    if (sampleCard.isRevealed) {
        DrawText(sampleCard.english, 320 + (640/2) - (MeasureText(sampleCard.english, 26)/2), 340, 26, (Color){27, 58, 92, 255});
    } else {
        DrawText("Click Reveal to see meaning", 320 + (640/2) - (MeasureText("Click Reveal to see meaning", 18)/2), 340, 18, GRAY);
    }

    // 4. Interaction Buttons
    Vector2 mousePos = GetMousePosition();
    bool overReveal = CheckCollisionPointRec(mousePos, revealBtn);
    bool overNext = CheckCollisionPointRec(mousePos, nextBtn);

    DrawRectangleRec(revealBtn, overReveal ? LIME : GREEN);
    DrawText("REVEAL", revealBtn.x + (revealBtn.width/2) - (MeasureText("REVEAL", 16)/2), revealBtn.y + 14, 16, WHITE);

    DrawRectangleRec(nextBtn, overNext ? BLUE : DARKBLUE);
    DrawText("NEXT", nextBtn.x + (nextBtn.width/2) - (MeasureText("NEXT", 16)/2), nextBtn.y + 14, 16, WHITE);

    if (overReveal && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        sampleCard.isRevealed = !sampleCard.isRevealed;
    }
    if (overNext && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        sampleCard.isRevealed = false; 
    }

    // 5. Right Sidebar (Progress Panel)
    DrawRectangle(1020, 40, 220, 640, DARKGRAY);
    DrawText("PROGRESS", 1040, 60, 20, GOLD);
    DrawText("Mastery: 0%", 1040, 120, 18, WHITE);

    // Return Hint
    DrawText("Press [M] to return to Main Menu", 320, 40, 16, LIGHTGRAY);
    if (IsKeyPressed(KEY_M)) {
        state.currentScreen = MENU_SCREEN; 
    }
}

void drawScenario() {}
void drawProgress() {}

int main() {
    InitWindow(1280, 720, "Polyglot Quest");
    SetTargetFPS(60);

    // Initial State Setup
    state.currentScreen = MENU_SCREEN;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground((Color){13, 27, 42, 255}); 

        // Screen Routing
        switch (state.currentScreen) 
        {
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
            default:
                drawMenu();
                break;
        }

        EndDrawing();
    }
    CloseWindow();
    return 0;
}