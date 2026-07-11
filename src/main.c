#include "raylib.h"
#include "types.h"
#include "logic.h"
#include "data.h"  
#include <stdio.h> 
#include <stdbool.h>

extern GameState state;

static int totalCards = 0;
static Flashcard gameCards[30];

void drawMenu() {
    DrawText("POLYGLOT QUEST", 1280 / 2 - MeasureText("POLYGLOT QUEST", 48) / 2, 100, 48, (Color){233, 196, 106, 255}); 
    DrawText("Learn Arabic. Live the Language.", 1280 / 2 - MeasureText("Learn Arabic. Live the Language.", 20) / 2, 160, 20, (Color){245, 237, 208, 255});

    Rectangle btnFlashcards = { 1280 / 2 - 150, 260, 300, 50 };
    Rectangle btnScenario   = { 1280 / 2 - 150, 340, 300, 50 };
    Rectangle btnProgress   = { 1280 / 2 - 150, 420, 300, 50 };
    Rectangle btnExit       = { 1280 / 2 - 150, 500, 300, 50 };

    Vector2 mousePos = GetMousePosition();

    // Flashcard Button
    Color colorFlashcards = (Color){30, 140, 58, 255}; 
    if (CheckCollisionPointRec(mousePos, btnFlashcards)) {
        colorFlashcards = (Color){40, 180, 75, 255}; 
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            state.currentScreen = FLASHCARD_SCREEN; 
        }
    }
    DrawRectangleRec(btnFlashcards, colorFlashcards);
    DrawText("FLASHCARDS", btnFlashcards.x + (btnFlashcards.width / 2) - (MeasureText("FLASHCARDS", 20) / 2), btnFlashcards.y + 15, 20, WHITE);

    // Scenario Button
    Color colorScenario = (Color){27, 58, 92, 255}; 
    if (CheckCollisionPointRec(mousePos, btnScenario)) {
        colorScenario = (Color){38, 81, 128, 255}; 
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            state.currentScreen = SCENARIO_SCREEN;
        }
    }
    DrawRectangleRec(btnScenario, colorScenario);
    DrawText("SCENARIO MODE", btnScenario.x + (btnScenario.width / 2) - (MeasureText("SCENARIO MODE", 20) / 2), btnScenario.y + 15, 20, WHITE);

    // Progress Button
    Color colorProgress = (Color){74, 45, 140, 255}; 
    if (CheckCollisionPointRec(mousePos, btnProgress)) {
        colorProgress = (Color){100, 61, 190, 255}; 
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            state.currentScreen = PROGRESS_SCREEN;
        }
    }
    DrawRectangleRec(btnProgress, colorProgress);
    DrawText("PROGRESS", btnProgress.x + (btnProgress.width / 2) - (MeasureText("PROGRESS", 20) / 2), btnProgress.y + 15, 20, WHITE);

    // Exit Button
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

void drawFlashcard() {void drawFlashcard() {
    ClearBackground((Color){13, 27, 42, 255}); 

    if (totalCards == 0) {
        DrawText("No flashcards loaded from data layer!", 400, 300, 20, RED);
        return;
    }

    // Points directly to Saïda's central state tracker instead of a local copy
    Flashcard currentCard = gameCards[state.currentCardIndex];

    // Responsive positioning for 3 balanced action buttons below the card layout
    Rectangle prevBtn   = { 440, 520, 110, 45 };
    Rectangle revealBtn = { 565, 520, 110, 45 };
    Rectangle nextBtn   = { 690, 520, 110, 45 };

    // Categories Sidebar
    DrawRectangle(40, 40, 220, 640, DARKGRAY);
    DrawText("CATEGORIES", 60, 60, 20, GOLD);
    DrawRectangle(50, 110, 200, 45, MAROON); 
    DrawText("Basics", 70, 122, 18, WHITE);

    // Central Card
    Color parchment = (Color){ 245, 237, 208, 255 };
    DrawRectangleRounded((Rectangle){ 320, 100, 640, 380 }, 0.04f, 4, parchment);
    
    DrawText(currentCard.arabic, 320 + (640/2) - (MeasureText(currentCard.arabic, 48)/2), 160, 48, BLACK);
    DrawText(currentCard.transliteration, 320 + (640/2) - (MeasureText(currentCard.transliteration, 22)/2), 250, 22, DARKGRAY);

    // Day 5: Conditional English meaning display based on state.isRevealed
    if (state.isRevealed == 1) {
        DrawText(currentCard.english, 320 + (640/2) - (MeasureText(currentCard.english, 26)/2), 340, 26, (Color){27, 58, 92, 255});
    } else {
        DrawText("Click Reveal to see meaning", 320 + (640/2) - (MeasureText("Click Reveal to see meaning", 18)/2), 340, 18, GRAY);
    }

    Vector2 mousePos = GetMousePosition();
    bool overPrev   = CheckCollisionPointRec(mousePos, prevBtn);
    bool overReveal = CheckCollisionPointRec(mousePos, revealBtn);
    bool overNext   = CheckCollisionPointRec(mousePos, nextBtn);

    // Render Navigation & Control Buttons
    DrawRectangleRec(prevBtn, overPrev ? (Color){230, 150, 40, 255} : (Color){200, 120, 25, 255});
    DrawText("PREV", prevBtn.x + (prevBtn.width/2) - (MeasureText("PREV", 16)/2), prevBtn.y + 14, 16, WHITE);

    DrawRectangleRec(revealBtn, overReveal ? LIME : GREEN);
    DrawText("REVEAL", revealBtn.x + (revealBtn.width/2) - (MeasureText("REVEAL", 16)/2), revealBtn.y + 14, 16, WHITE);

    DrawRectangleRec(nextBtn, overNext ? BLUE : DARKBLUE);
    DrawText("NEXT", nextBtn.x + (nextBtn.width/2) - (MeasureText("NEXT", 16)/2), nextBtn.y + 14, 16, WHITE);

    // Interaction Management
    if (overPrev && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        state.isRevealed = 0;
        state.currentCardIndex = (state.currentCardIndex - 1 + totalCards) % totalCards;
    }
    if (overReveal && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        state.isRevealed = (state.isRevealed == 1) ? 0 : 1;
    }
    if (overNext && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        state.isRevealed = 0; 
        state.currentCardIndex = (state.currentCardIndex + 1) % totalCards; 
    }

    // Day 5: Enhanced Progress Panel with stats and mastery circle
    DrawRectangle(1020, 40, 220, 640, DARKGRAY);
    DrawText("PROGRESS", 1040, 60, 20, GOLD);
    DrawText(TextFormat("Card: %d/%d", state.currentCardIndex + 1, totalCards), 1040, 120, 18, WHITE);
    
    // Correct & Wrong Counters
    DrawText(TextFormat("Correct: %d", state.correctCount), 1040, 160, 18, GREEN);
    DrawText(TextFormat("Wrong:   %d", state.wrongCount), 1040, 190, 18, RED);

    // Calculate accuracy percentage safely to avoid division by zero
    int totalAnswers = state.correctCount + state.wrongCount;
    float accuracyPercent = (totalAnswers > 0) ? ((float)state.correctCount / totalAnswers) * 100.0f : 0.0f;
    DrawText(TextFormat("Accuracy: %.0f%%", accuracyPercent), 1040, 230, 18, VIOLET);

    // Draw mastery percentage display using DrawRing for the circular indicator
    Vector2 center = { 1130, 340 };
    float radiusInner = 35.0f;
    float radiusOuter = 45.0f;
    float startAngle = 0.0f;
    // Map accuracy percentage (0-100) to degrees (0-360)
    float endAngle = (accuracyPercent / 100.0f) * 360.0f; 
    int segments = 36;

    // Background circle tracking ring
    DrawRing(center, radiusInner, radiusOuter, 0.0f, 360.0f, segments, BLACK);
    // Active progress fill ring
    if (accuracyPercent > 0.0f) {
        DrawRing(center, radiusInner, radiusOuter, startAngle, endAngle, segments, GOLD);
    }

    DrawText("Press [M] to return to Main Menu", 320, 40, 16, LIGHTGRAY);
    if (IsKeyPressed(KEY_M)) state.currentScreen = MENU_SCREEN; 
}

void drawScenario() {
    ClearBackground((Color){13, 27, 42, 255});
    DrawText("Scenario Mode Workspace", 400, 300, 30, GOLD);
    DrawText("Press [M] for Menu", 400, 360, 18, LIGHTGRAY);
    if (IsKeyPressed(KEY_M)) state.currentScreen = MENU_SCREEN;
}

void drawProgress() {}

int main() {
    InitWindow(1280, 720, "Polyglot Quest");
    SetTargetFPS(60);

    totalCards = loadFlashcards(gameCards);
    printf("Successfully initialized backend! Loaded %d cards.\n", totalCards);

    state.currentScreen = MENU_SCREEN;

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