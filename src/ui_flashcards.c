#include "ui_flashcards.h"
#include "raylib.h"

extern GameState state;

void drawFlashcard(Flashcard* gameCards, int totalCards) {
    ClearBackground((Color){13, 27, 42, 255}); 

    if (totalCards == 0) {
        DrawText("No flashcards loaded from data layer!", 400, 300, 20, RED);
        return;
    }

    Flashcard currentCard = gameCards[state.currentCardIndex];

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

    if (state.isRevealed == 1) {
        DrawText(currentCard.english, 320 + (640/2) - (MeasureText(currentCard.english, 26)/2), 340, 26, (Color){27, 58, 92, 255});
    } else {
        DrawText("Click Reveal to see meaning", 320 + (640/2) - (MeasureText("Click Reveal to see meaning", 18)/2), 340, 18, GRAY);
    }

    Vector2 mousePos = GetMousePosition();
    bool overPrev   = CheckCollisionPointRec(mousePos, prevBtn);
    bool overReveal = CheckCollisionPointRec(mousePos, revealBtn);
    bool overNext   = CheckCollisionPointRec(mousePos, nextBtn);

    DrawRectangleRec(prevBtn, overPrev ? (Color){230, 150, 40, 255} : (Color){200, 120, 25, 255});
    DrawText("PREV", prevBtn.x + (prevBtn.width/2) - (MeasureText("PREV", 16)/2), prevBtn.y + 14, 16, WHITE);

    DrawRectangleRec(revealBtn, overReveal ? LIME : GREEN);
    DrawText("REVEAL", revealBtn.x + (revealBtn.width/2) - (MeasureText("REVEAL", 16)/2), revealBtn.y + 14, 16, WHITE);

    DrawRectangleRec(nextBtn, overNext ? BLUE : DARKBLUE);
    DrawText("NEXT", nextBtn.x + (nextBtn.width/2) - (MeasureText("NEXT", 16)/2), nextBtn.y + 14, 16, WHITE);

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

    // Progress Panel
    DrawRectangle(1020, 40, 220, 640, DARKGRAY);
    DrawText("PROGRESS", 1040, 60, 20, GOLD);
    DrawText(TextFormat("Card: %d/%d", state.currentCardIndex + 1, totalCards), 1040, 120, 18, WHITE);
    
    DrawText(TextFormat("Correct: %d", state.correctCount), 1040, 160, 18, GREEN);
    DrawText(TextFormat("Wrong:   %d", state.wrongCount), 1040, 190, 18, RED);

    int totalAnswers = state.correctCount + state.wrongCount;
    float accuracyPercent = (totalAnswers > 0) ? ((float)state.correctCount / totalAnswers) * 100.0f : 0.0f;
    DrawText(TextFormat("Accuracy: %.0f%%", accuracyPercent), 1040, 230, 18, VIOLET);

    Vector2 center = { 1130, 340 };
    float radiusInner = 35.0f;
    float radiusOuter = 45.0f;
    float startAngle = 0.0f;
    float endAngle = (accuracyPercent / 100.0f) * 360.0f; 
    int segments = 36;

    DrawRing(center, radiusInner, radiusOuter, 0.0f, 360.0f, segments, BLACK);
    if (accuracyPercent > 0.0f) {
        DrawRing(center, radiusInner, radiusOuter, startAngle, endAngle, segments, GOLD);
    }

    DrawText("Press [M] to return to Main Menu", 320, 40, 16, LIGHTGRAY);
    if (IsKeyPressed(KEY_M)) state.currentScreen = MENU_SCREEN; 
}