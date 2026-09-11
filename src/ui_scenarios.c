#include "ui_scenarios.h"
#include "raylib.h"
#include "types.h"

extern GameState state;
extern Font arabicFont;

void drawScenario(void) {
    ClearBackground((Color){13, 27, 42, 255});

    static int selectedOption = 0;

    if (IsKeyPressed(KEY_M)) {
        selectedOption = 0;
        state.currentScreen = MENU_SCREEN;
        return;
    }

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

    Rectangle npcBox = { 60, 120, 260, 520 };
    DrawRectangleRec(npcBox, (Color){38, 81, 128, 255});
    DrawRectangleLinesEx(npcBox, 3, GOLD);
    
    int npcLabelWidth = MeasureText("MERCHANT", 22);
    int npcPlaceWidth = MeasureText("(NPC Asset Place)", 14);
    DrawText("MERCHANT", npcBox.x + (npcBox.width / 2) - (npcLabelWidth / 2), npcBox.y + 240, 22, WHITE);
    DrawText("(NPC Asset Place)", npcBox.x + (npcBox.width / 2) - (npcPlaceWidth / 2), npcBox.y + 275, 14, LIGHTGRAY);

    Color parchment = (Color){ 245, 237, 208, 255 };
    Rectangle speechBubble = { 360, 120, 860, 220 };
    DrawRectangleRounded(speechBubble, 0.04f, 4, parchment);

    const char* npcArabic = "السَّلَامُ عَلَيْكُمْ";
    const char* npcTranslit = "as-salaamu alaykum";
    const char* npcEnglish = "\"Peace be upon you.\"";

    int arabicWidth = MeasureText(npcArabic, 36);
    int translitWidth = MeasureText(npcTranslit, 18);
    int englishWidth = MeasureText(npcEnglish, 20);

    DrawText(npcArabic, speechBubble.x + (speechBubble.width / 2) - (arabicWidth / 2), speechBubble.y + 35, 36, BLACK);
    DrawText(npcTranslit, speechBubble.x + (speechBubble.width / 2) - (translitWidth / 2), speechBubble.y + 100, 18, DARKGRAY);
    DrawText(npcEnglish, speechBubble.x + (speechBubble.width / 2) - (englishWidth / 2), speechBubble.y + 150, 20, (Color){27, 58, 92, 255});

    DrawText("How will you respond?", 360, 365, 20, GOLD);

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

    Color bgA = DARKGRAY;
    Color borderA = GRAY;
    if (overA) {
        bgA = (Color){50, 60, 75, 255};
        borderA = GOLD;
    }
    DrawRectangleRounded(optA, 0.15f, 4, bgA);
    DrawRectangleRoundedLinesEx(optA, 0.15f, 4, 2.0f, borderA);
    DrawText("A", optA.x + 20, optA.y + 16, 20, GOLD);
    const char* textA = "وَعَلَيْكُمُ السَّلَام (wa-alaykum us-salaam)";
    int textAX = optA.x + 70;
    int textAY = optA.y + 18;
    DrawText(textA, textAX, textAY, 18, WHITE);
    
    int textWidthA = MeasureText(textA, 18);
    if (overA) {
        DrawLine(textAX, textAY + 20, textAX + textWidthA, textAY + 20, customGold);
    }
    if (selectedOption == 1) {
        DrawText("v", optA.x + optA.width - 40, optA.y + 14, 24, customGreen); 
    }

    Color bgB = DARKGRAY;
    Color borderB = GRAY;
    if (overB) {
        bgB = (Color){50, 60, 75, 255};
        borderB = GOLD;
    }
    DrawRectangleRounded(optB, 0.15f, 4, bgB);
    DrawRectangleRoundedLinesEx(optB, 0.15f, 4, 2.0f, borderB);
    DrawText("B", optB.x + 20, optB.y + 16, 20, GOLD);
    const char* textB = "مَرْحَبًا (marhaban)";
    int textBX = optB.x + 70;
    int textBY = optB.y + 18;
    DrawText(textB, textBX, textBY, 18, WHITE);
    
    int textWidthB = MeasureText(textB, 18);
    if (overB) {
        DrawLine(textBX, textBY + 20, textBX + textWidthB, textBY + 20, customGold);
    }
    if (selectedOption == 2) {
        DrawText("X", optB.x + optB.width - 40, optB.y + 16, 22, customRed); 
    }

    Color bgC = DARKGRAY;
    Color borderC = GRAY;
    if (overC) {
        bgC = (Color){50, 60, 75, 255};
        borderC = GOLD;
    }
    DrawRectangleRounded(optC, 0.15f, 4, bgC);
    DrawRectangleRoundedLinesEx(optC, 0.15f, 4, 2.0f, borderC);
    DrawText("C", optC.x + 20, optC.y + 16, 20, GOLD);
    const char* textC = "شُكْرًا (shukran)";
    int textCX = optC.x + 70;
    int textCY = optC.y + 18;
    DrawText(textC, textCX, textCY, 18, WHITE);
    
    int textWidthC = MeasureText(textC, 18);
    if (overC) {
        DrawLine(textCX, textCY + 20, textCX + textWidthC, textCY + 20, customGold);
    }
    if (selectedOption == 3) {
        DrawText("X", optC.x + optC.width - 40, optC.y + 16, 22, customRed); 
    }

    DrawText("Press [M] to return to Main Menu", 60, 40, 14, LIGHTGRAY);
    if (IsKeyPressed(KEY_M)) state.currentScreen = MENU_SCREEN;
}