#include "ui_scenarios.h"
#include "raylib.h"
#include "types.h"
#include <stdio.h>

extern GameState state;
extern Font arabicFont;

static Texture2D merchantTexture = { 0 };
static bool merchantAttempted = false;

static void EnsureMerchantLoaded(void) {
    if (merchantAttempted) return;
    merchantAttempted = true;

    const char* appDir = GetApplicationDirectory();

    const char* candidatePaths[] = {
        "assets/merchant.png",
        "assets/images/merchant.png",
        "../assets/merchant.png",
        "../assets/images/merchant.png",
        TextFormat("%sassets/merchant.png", appDir),
        TextFormat("%sassets/images/merchant.png", appDir)
    };

    for (int i = 0; i < 6; i++) {
        printf("[CHECK] Looking for merchant.png at: %s (exists: %s)\n",
               candidatePaths[i], FileExists(candidatePaths[i]) ? "yes" : "no");

        if (FileExists(candidatePaths[i])) {
            Image img = LoadImage(candidatePaths[i]);
            if (img.data != NULL) {
                merchantTexture = LoadTextureFromImage(img);
                UnloadImage(img);
                printf("[SUCCESS] Merchant texture loaded from: %s (ID: %u)\n",
                       candidatePaths[i], merchantTexture.id);
                return;
            } else {
                printf("[WARNING] File found but failed to decode: %s\n", candidatePaths[i]);
            }
        }
    }

    printf("[WARNING] Failed to load merchant image from all candidate paths!\n");
}

void drawScenario(Scenario* gameScenarios, int totalScenarios) {
    int scenarioLimit = (totalScenarios > 0) ? totalScenarios : 10;

    // Ensure texture is safely loaded into GPU memory
    EnsureMerchantLoaded();

    ClearBackground((Color){13, 27, 42, 255});

    if (scenarioLimit == 0) {
        DrawText("No scenarios loaded from data layer!", 400, 300, 20, RED);
        return;
    }

    Scenario current = gameScenarios[state.currentScenarioStep % scenarioLimit];

    // Top Step Indicator
    for (int i = 0; i < 5; i++) {
        Color c = (i <= (state.currentScenarioStep % 5)) ? (Color){124, 148, 115, 255} : (Color){225, 225, 225, 255};
        DrawCircle(480 + (i * 80), 50, 14, c);
        DrawText(TextFormat("%d", i + 1), 480 + (i * 80) - 5, 42, 16, BLACK);
    }

    // NPC Frame
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

    // Dialogue Box
    Rectangle dialogueBox = { 420, 100, 800, 180 };
    DrawRectangleRounded(dialogueBox, 0.04f, 4, (Color){245, 237, 208, 255});

    Vector2 arabicSize = MeasureTextEx(arabicFont, current.prompt, 32, 2);
    Vector2 arabicPos = {
        dialogueBox.x + (dialogueBox.width / 2.0f) - (arabicSize.x / 2.0f),
        dialogueBox.y + 35
    };

    if (arabicFont.texture.id > 0) {
        DrawTextEx(arabicFont, current.prompt, arabicPos, 32, 2, BLACK);
    } else {
        DrawText(current.prompt, dialogueBox.x + 40, dialogueBox.y + 35, 24, BLACK);
    }

    DrawText(current.translation, dialogueBox.x + (dialogueBox.width / 2.0f) - (MeasureText(current.translation, 20) / 2.0f), dialogueBox.y + 110, 20, DARKGRAY);

    // Options
    Vector2 mousePos = GetMousePosition();
    for (int i = 0; i < 3; i++) {
        Rectangle optionBtn = { 420, 310 + (i * 90), 800, 70 };
        bool overOption = CheckCollisionPointRec(mousePos, optionBtn);

        DrawRectangleRounded(optionBtn, 0.05f, 4, overOption ? (Color){38, 81, 128, 255} : (Color){27, 58, 92, 255});
        DrawRectangleRoundedLinesEx(optionBtn, 0.05f, 4, 2.0f, GOLD);

        DrawText(TextFormat("%c)", 'A' + i), optionBtn.x + 25, optionBtn.y + 22, 22, GOLD);

        Vector2 optArabicPos = {
            optionBtn.x + 80,
            optionBtn.y + 20
        };

        if (arabicFont.texture.id > 0) {
            DrawTextEx(arabicFont, current.options[i], optArabicPos, 24, 2, WHITE);
        } else {
            DrawText(current.options[i], optionBtn.x + 80, optionBtn.y + 22, 20, WHITE);
        }

        if (overOption && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (i == current.correctIndex) {
                state.correctCount++;
            } else {
                state.wrongCount++;
            }
            state.currentScenarioStep++;
            if (state.currentScenarioStep >= scenarioLimit) {
                state.currentScenarioStep = 0;
                state.currentScreen = PROGRESS_SCREEN;
            }
        }
    }

    DrawText("Press [M] to return to Main Menu", 420, 640, 16, LIGHTGRAY);
    if (IsKeyPressed(KEY_M)) state.currentScreen = MENU_SCREEN;
}
