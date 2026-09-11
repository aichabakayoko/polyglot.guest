#include "ui_scenarios.h"
#include "raylib.h"
#include "types.h"

extern GameState state;
extern Font arabicFont;

// Static texture variable for lazy loading merchant.png
static Texture2D merchantTexture;
static bool merchantLoaded = false;

void drawScenario(Scenario* gameScenarios, int totalScenarios) {
    // Lazy-load merchant texture when scenario screen opens
    if (!merchantLoaded) {
        merchantTexture = LoadTexture("assets/images/merchant.png");
        merchantLoaded = true;
    }

    ClearBackground((Color){13, 27, 42, 255});

    if (totalScenarios == 0) {
        DrawText("No scenarios loaded from data layer!", 400, 300, 20, RED);
        return;
    }

    // Access scenario using state.currentScenarioStep
    Scenario current = gameScenarios[state.currentScenarioStep % totalScenarios];

    // Top Step Indicator (5 steps)
    for (int i = 0; i < 5; i++) {
        Color c = (i <= state.currentScenarioStep) ? (Color){124, 148, 115, 255} : (Color){225, 225, 225, 255};
        DrawCircle(480 + (i * 80), 50, 14, c);
        DrawText(TextFormat("%d", i + 1), 480 + (i * 80) - 5, 42, 16, BLACK);
    }

    // Left Panel: NPC Frame (Merchant image)
    Rectangle npcFrame = { 60, 100, 320, 520 };
    DrawRectangleRec(npcFrame, (Color){27, 58, 92, 255});
    DrawRectangleLinesEx(npcFrame, 3, GOLD);

    if (merchantTexture.id > 0) {
        DrawTexturePro(
            merchantTexture,
            (Rectangle){ 0, 0, (float)merchantTexture.width, (float)merchantTexture.height },
            (Rectangle){ 80, 120, 280, 480 },
            (Vector2){ 0, 0 },
            0.0f,
            WHITE
        );
    } else {
        DrawRectangle(80, 120, 280, 480, DARKGRAY);
        DrawText("MERCHANT NPC", 120, 340, 20, LIGHTGRAY);
    }

    // Right Panel: Dialogue & Options
    Rectangle dialogueBox = { 420, 100, 800, 180 };
    DrawRectangleRounded(dialogueBox, 0.04f, 4, (Color){245, 237, 208, 255});

    // Arabic Merchant Dialogue using DrawTextEx (current.prompt)
    Vector2 arabicSize = MeasureTextEx(arabicFont, current.prompt, 32, 2);
    Vector2 arabicPos = {
        dialogueBox.x + (dialogueBox.width / 2.0f) - (arabicSize.x / 2.0f),
        dialogueBox.y + 35
    };
    DrawTextEx(arabicFont, current.prompt, arabicPos, 32, 2, BLACK);

    // English Translation (current.translation)
    DrawText(current.translation, dialogueBox.x + (dialogueBox.width / 2.0f) - (MeasureText(current.translation, 20) / 2.0f), dialogueBox.y + 110, 20, DARKGRAY);

    // Option Buttons
    Vector2 mousePos = GetMousePosition();
    for (int i = 0; i < 3; i++) {
        Rectangle optionBtn = { 420, 310 + (i * 90), 800, 70 };
        bool overOption = CheckCollisionPointRec(mousePos, optionBtn);

        DrawRectangleRounded(optionBtn, 0.05f, 4, overOption ? (Color){38, 81, 128, 255} : (Color){27, 58, 92, 255});
        DrawRectangleRoundedLinesEx(optionBtn, 0.05f, 4, 2.0f, GOLD);

        DrawText(TextFormat("%c)", 'A' + i), optionBtn.x + 25, optionBtn.y + 22, 22, GOLD);

        // Arabic text on Option Button (current.options[i])
        Vector2 optArabicSize = MeasureTextEx(arabicFont, current.options[i], 24, 2);
        Vector2 optArabicPos = {
            optionBtn.x + 80,
            optionBtn.y + 20
        };
        DrawTextEx(arabicFont, current.options[i], optArabicPos, 24, 2, WHITE);

        if (overOption && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (i == current.correctIndex) {
                state.correctCount++;
            } else {
                state.wrongCount++;
            }
            state.currentScenarioStep++;
            if (state.currentScenarioStep >= 5) {
                state.currentScenarioStep = 0;
                state.currentScreen = PROGRESS_SCREEN;
            }
        }
    }

    DrawText("Press [M] to return to Main Menu", 420, 640, 16, LIGHTGRAY);
    if (IsKeyPressed(KEY_M)) state.currentScreen = MENU_SCREEN;
}