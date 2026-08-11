#include "ui_progress.h"
#include "raylib.h"
#include "types.h"

extern GameState state;

void drawProgress(void) {
    ClearBackground((Color){13, 27, 42, 255});

    if (IsKeyPressed(KEY_M)) {
        state.currentScreen = MENU_SCREEN;
        return;
    }

    const char* titleText = "YOUR PROGRESS";
    int titleWidth = MeasureText(titleText, 32);
    DrawText(titleText, 1280 / 2 - titleWidth / 2, 40, 32, GOLD);

    int totalAnswers = state.correctCount + state.wrongCount;
    float accuracyPercent = (totalAnswers > 0) ? ((float)state.correctCount / totalAnswers) * 100.0f : 0.0f;
    
    int totalScore = (state.correctCount * 10) - (state.wrongCount * 5);
    if (totalScore < 0) totalScore = 0;

    Rectangle trophyBox = { 60, 120, 260, 440 };
    DrawRectangleRec(trophyBox, (Color){27, 58, 92, 255});
    DrawRectangleLinesEx(trophyBox, 3, GOLD);
    
    DrawCircle(60 + 130, 120 + 120, 50, (Color){233, 196, 106, 255});
    DrawText("🏆", 60 + 130 - 20, 120 + 95, 40, WHITE);

    int scoreLabelWidth = MeasureText("TOTAL SCORE", 20);
    int scoreNumWidth = MeasureText(TextFormat("%d", totalScore), 42);
    DrawText("TOTAL SCORE", 60 + 130 - scoreLabelWidth / 2, 120 + 240, 20, LIGHTGRAY);
    DrawText(TextFormat("%d", totalScore), 60 + 130 - scoreNumWidth / 2, 120 + 280, 42, GOLD);

    int starsEarned = 1;
    if (totalScore >= 150) starsEarned = 5;
    else if (totalScore >= 100) starsEarned = 4;
    else if (totalScore >= 50)  starsEarned = 3;
    else if (totalScore >= 20)  starsEarned = 2;

    int starY = 120 + 360;
    int starStartX = 60 + 130 - (5 * 24) / 2;
    for (int i = 0; i < 5; i++) {
        if (i < starsEarned) {
            DrawText("★", starStartX + (i * 24), starY, 24, GOLD);
        } else {
            DrawText("☆", starStartX + (i * 24), starY, 24, GRAY);
        }
    }

    Rectangle overviewBox = { 360, 120, 410, 440 };
    DrawRectangleRounded(overviewBox, 0.03f, 4, (Color){38, 81, 128, 255});
    DrawText("STATISTICS OVERVIEW", overviewBox.x + 25, overviewBox.y + 25, 20, GOLD);

    int startY = overviewBox.y + 80;
    int spacingY = 55;

    DrawText(TextFormat("Flashcard Score:   %d pts", state.correctCount * 6), overviewBox.x + 35, startY, 18, WHITE);
    DrawText(TextFormat("Scenario Score:    %d pts", state.correctCount * 4), overviewBox.x + 35, startY + spacingY, 18, WHITE);
    DrawText(TextFormat("Correct Answers:   %d", state.correctCount), overviewBox.x + 35, startY + (spacingY * 2), 18, LIME);
    DrawText(TextFormat("Wrong Answers:     %d", state.wrongCount), overviewBox.x + 35, startY + (spacingY * 3), 18, RED);
    DrawText(TextFormat("Total Accuracy:    %.0f%%", accuracyPercent), overviewBox.x + 35, startY + (spacingY * 4), 18, VIOLET);

    Rectangle masteryBox = { 810, 120, 410, 440 };
    DrawRectangleRounded(masteryBox, 0.03f, 4, (Color){20, 40, 65, 255});
    DrawRectangleRoundedLinesEx(masteryBox, 0.03f, 4, 2.0f, DARKGRAY);
    DrawText("MASTERY BY CATEGORY", masteryBox.x + 25, masteryBox.y + 25, 20, GOLD);

    int barX = masteryBox.x + 35;
    int barWidth = 340;
    int barHeight = 22;

    DrawText("Basics (Greetings & Introductions)", barX, masteryBox.y + 80, 16, LIGHTGRAY);
    DrawRectangle(barX, masteryBox.y + 110, barWidth, barHeight, DARKGRAY); 
    int fillWidthBasics = (int)((accuracyPercent / 100.0f) * barWidth);
    DrawRectangle(barX, masteryBox.y + 110, fillWidthBasics, barHeight, GREEN); 

    DrawText("Marketplace (Numbers & Bartering)", barX, masteryBox.y + 165, 16, LIGHTGRAY);
    DrawRectangle(barX, masteryBox.y + 195, barWidth, barHeight, DARKGRAY);
    DrawRectangle(barX, masteryBox.y + 195, (int)(0.0f * barWidth), barHeight, ORANGE);

    DrawText("Travel (Directions & Navigation)", barX, masteryBox.y + 250, 16, LIGHTGRAY);
    DrawRectangle(barX, masteryBox.y + 280, barWidth, barHeight, DARKGRAY);
    DrawRectangle(barX, masteryBox.y + 280, (int)(0.0f * barWidth), barHeight, BLUE);

    Rectangle btnReplay = { 1280 / 2 - 240, 590, 220, 50 };
    Rectangle btnMenu   = { 1280 / 2 + 20,  590, 220, 50 };

    Vector2 mousePos = GetMousePosition();
    bool overReplay = CheckCollisionPointRec(mousePos, btnReplay);
    bool overMenu   = CheckCollisionPointRec(mousePos, btnMenu);

    if (overReplay && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        state.currentScreen = SCENARIO_SCREEN;
    }
    if (overMenu && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        state.currentScreen = MENU_SCREEN;
    }

    DrawRectangleRec(btnReplay, overReplay ? (Color){38, 81, 128, 255} : (Color){27, 58, 92, 255});
    DrawText("REPLAY SCENARIO", btnReplay.x + (btnReplay.width / 2) - (MeasureText("REPLAY SCENARIO", 16) / 2), btnReplay.y + 17, 16, WHITE);

    DrawRectangleRec(btnMenu, overMenu ? (Color){40, 180, 75, 255} : (Color){30, 140, 58, 255});
    DrawText("BACK TO MENU", btnMenu.x + (btnMenu.width / 2) - (MeasureText("BACK TO MENU", 16) / 2), btnMenu.y + 17, 16, WHITE);

    DrawText("Press [M] to return to Main Menu", 60, 40, 14, LIGHTGRAY);
}