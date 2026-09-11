#include "ui_scenarios.h"
#include "raylib.h"
#include "types.h"

extern GameState state;
extern Font arabicFont;

// Static texture variable for lazy loading merchant.png
static Texture2D merchantTexture;
static bool merchantLoaded = false;

void drawScenario(void) {
    // Lazy-load merchant texture when scenario screen opens
    if (!merchantLoaded) {
        merchantTexture = LoadTexture("assets/images/merchant.png");
        merchantLoaded = true;
    }

    ClearBackground((Color){13, 27, 42, 255});

    static int selectedOption = 0;

    if (IsKeyPressed(KEY_M)) {
        selectedOption = 0;
        state.currentScreen = MENU_SCREEN;
        return;
    }

    // Top Step Indicator
    int totalSteps = 5;
    int currentStep = 1; 
    int startX = 1280 / 2 - ((totalSteps - 1) * 60) / 2;
    int posY = 50;

    DrawLine(startX, posY, startX + (totalSteps - 1) * 60, posY, GRAY);

    for (int i = 0; i < totalSteps; i++) {
        int circleX = startX + i * 60;
        if (i + 1 == currentStep) {
            DrawCircle(circleX, posY, 15, LIME);
            DrawText(TextFormat("%d", i + 1), circleX - 4, posY - 7, 14, BLACK);
        } else if (i + 1 < currentStep) {
            DrawCircle(circleX, posY, 12, GREEN);
            DrawText(TextFormat("%d", i + 1), circleX - 4, posY - 6, 12, WHITE);
        } else {
            DrawCircle(circleX, posY, 12, DARKGRAY);
            DrawText(TextFormat("%d", i + 1), circleX - 4, posY - 6, 12, LIGHTGRAY);
        }
    }

    // Left Panel: Merchant NPC Frame & PNG Asset
    Rectangle npcBox = { 60, 120, 260, 520 };
    DrawRectangleRec(npcBox, (Color){38, 81, 128, 255});
    DrawRectangleLinesEx(npcBox, 3, GOLD);
    
    if (merchantTexture.id > 0) {
        // Render merchant.png inside the NPC box
        DrawTexturePro(
            merchantTexture,
            (Rectangle){ 0, 0, (float)merchantTexture.width, (float)merchantTexture.height },
            (Rectangle){ npcBox.x + 10, npcBox.y + 10, npcBox.width - 20, npcBox.height - 20 },
            (Vector2){ 0, 0 },
            0.0f,
            WHITE
        );
    } else {
        int npcLabelWidth = MeasureText("MERCHANT", 22);
        int npcPlaceWidth = MeasureText("(NPC Asset Place)", 14);
        DrawText("MERCHANT", npcBox.x + (npcBox.width / 2) - (npcLabelWidth / 2), npcBox.y + 240, 22, WHITE);
        DrawText("(NPC Asset Place)", npcBox.x + (npcBox.width / 2) - (npcPlaceWidth / 2), npcBox.y + 275, 14, LIGHTGRAY);
    }

    // Dialogue Parchment Box
    Color parchment = (Color){ 245, 237, 208, 255 };
    Rectangle speechBubble = { 360, 120, 860, 220 };
    DrawRectangleRounded(speechBubble, 0.04f, 4, parchment);

    const char* npcArabic = "السَّلَامُ عَلَيْكُمْ";
    const char* npcTranslit = "as-salaamu alaykum";
    const char* npcEnglish = "\"Peace be upon you.\"";

    // Measure Arabic dialogue text with MeasureTextEx
    Vector2 arabicSize = MeasureTextEx(arabicFont, npcArabic, 36, 2);
    Vector2 arabicPos = {
        speechBubble.x + (speechBubble.width / 2.0f) - (arabicSize.x / 2.0f),
        speechBubble.y + 35
    };
    DrawTextEx(arabicFont, npcArabic, arabicPos, 36, 2, BLACK);

    int translitWidth = MeasureText(npcTranslit, 18);
    int englishWidth = MeasureText(npcEnglish, 20);
    DrawText(npcTranslit, speechBubble.x + (speechBubble.width / 2) - (translitWidth / 2), speechBubble.y + 100, 18, DARKGRAY);
    DrawText(npcEnglish, speechBubble.x + (speechBubble.width / 2) - (englishWidth / 2), speechBubble.y + 150, 20, (Color){27, 58, 92, 255});

    DrawText("How will you respond?", 360, 365, 20, GOLD);

    // Response Option Buttons
    Rectangle optA = { 360, 410, 860, 55 };
    Rectangle optB = { 360, 480, 860, 55 };
    Rectangle optC = { 360, 550, 860, 55 };

    Vector2 mousePos = GetMousePosition();
    bool overA = CheckCollisionPointRec(mousePos, optA);
    bool overB = CheckCollisionPointRec(mousePos, optB);
    bool overC = CheckCollisionPointRec(mousePos, optC);

    if (overA && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) selectedOption = 1;
    if (overB && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) selectedOption = 2;
    if (overC && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) selectedOption = 3;

    Color customGold  = (Color){ 253, 249, 0, 255 };
    Color customGreen = (Color){ 0, 228, 48, 255 };
    Color customRed   = (Color){ 230, 41, 55, 255 };

    // --- Option A ---
    Color bgA = overA ? (Color){50, 60, 75, 255} : DARKGRAY;
    Color borderA = overA ? GOLD : GRAY;
    DrawRectangleRounded(optA, 0.15f, 4, bgA);
    DrawRectangleRoundedLinesEx(optA, 0.15f, 4, 2.0f, borderA);
    DrawText("A", optA.x + 20, optA.y + 16, 20, GOLD);

    const char* textA = "وَعَلَيْكُمُ السَّلَام (wa-alaykum us-salaam)";
    Vector2 optASize = MeasureTextEx(arabicFont, textA, 18, 2);
    Vector2 optAPos = { optA.x + 70, optA.y + 18 };
    DrawTextEx(arabicFont, textA, optAPos, 18, 2, WHITE);

    if (overA) DrawLine(optAPos.x, optAPos.y + 20, optAPos.x + optASize.x, optAPos.y + 20, customGold);
    if (selectedOption == 1) DrawText("v", optA.x + optA.width - 40, optA.y + 14, 24, customGreen); 

    // --- Option B ---
    Color bgB = overB ? (Color){50, 60, 75, 255} : DARKGRAY;
    Color borderB = overB ? GOLD : GRAY;
    DrawRectangleRounded(optB, 0.15f, 4, bgB);
    DrawRectangleRoundedLinesEx(optB, 0.15f, 4, 2.0f, borderB);
    DrawText("B", optB.x + 20, optB.y + 16, 20, GOLD);

    const char* textB = "مَرْحَبًا (marhaban)";
    Vector2 optBSize = MeasureTextEx(arabicFont, textB, 18, 2);
    Vector2 optBPos = { optB.x + 70, optB.y + 18 };
    DrawTextEx(arabicFont, textB, optBPos, 18, 2, WHITE);

    if (overB) DrawLine(optBPos.x, optBPos.y + 20, optBPos.x + optBSize.x, optBPos.y + 20, customGold);
    if (selectedOption == 2) DrawText("X", optB.x + optB.width - 40, optB.y + 16, 22, customRed); 

    // --- Option C ---
    Color bgC = overC ? (Color){50, 60, 75, 255} : DARKGRAY;
    Color borderC = overC ? GOLD : GRAY;
    DrawRectangleRounded(optC, 0.15f, 4, bgC);
    DrawRectangleRoundedLinesEx(optC, 0.15f, 4, 2.0f, borderC);
    DrawText("C", optC.x + 20, optC.y + 16, 20, GOLD);

    const char* textC = "شُكْرًا (shukran)";
    Vector2 optCSize = MeasureTextEx(arabicFont, textC, 18, 2);
    Vector2 optCPos = { optC.x + 70, optC.y + 18 };
    DrawTextEx(arabicFont, textC, optCPos, 18, 2, WHITE);

    if (overC) DrawLine(optCPos.x, optCPos.y + 20, optCPos.x + optCSize.x, optCPos.y + 20, customGold);
    if (selectedOption == 3) DrawText("X", optC.x + optC.width - 40, optC.y + 16, 22, customRed); 

    DrawText("Press [M] to return to Main Menu", 60, 40, 14, LIGHTGRAY);
    if (IsKeyPressed(KEY_M)) state.currentScreen = MENU_SCREEN;
}