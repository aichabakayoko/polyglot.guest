#include "raylib.h"
#include "types.h"
#include "logic.h"
#include "data.h"  
#include <stdio.h> 
#include <stdbool.h>

extern GameState state;

static int totalCards = 0;
static Flashcard gameCards[30];

// Day 5: Scenario storage variables
static int totalScenarios = 0;
static Scenario gameScenarios[3];

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

void drawFlashcard() {
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

void drawScenario() {
    ClearBackground((Color){13, 27, 42, 255});
 feature-flashcards
    DrawText("Scenario Mode Workspace", 400, 300, 30, GOLD);
    DrawText("Press [M] for Menu", 400, 360, 18, LIGHTGRAY);


    // 1. Step Progress Indicator (Top Center)
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

    // 2. NPC Character Placeholder Box
    Rectangle npcBox = { 60, 120, 260, 520 };
    DrawRectangleRec(npcBox, (Color){38, 81, 128, 255});
    DrawRectangleLinesEx(npcBox, 3, GOLD);
    DrawText("MERCHANT", npcBox.x + (npcBox.width / 2) - (MeasureText("MERCHANT", 22) / 2), npcBox.y + 240, 22, WHITE);
    DrawText("(NPC Asset Place)", npcBox.x + (npcBox.width / 2) - (MeasureText("(NPC Asset Place)", 14) / 2), npcBox.y + 275, 14, LIGHTGRAY);

    // 3. Dialogue Speech Bubble Card
    Color parchment = (Color){ 245, 237, 208, 255 };
    Rectangle speechBubble = { 360, 120, 860, 220 };
    DrawRectangleRounded(speechBubble, 0.04f, 4, parchment);

    const char* npcArabic = "السَّلَامُ عَلَيْكُمْ";
    const char* npcTranslit = "as-salaamu alaykum";
    const char* npcEnglish = "\"Peace be upon you.\"";

    DrawText(npcArabic, speechBubble.x + (speechBubble.width / 2) - (MeasureText(npcArabic, 36) / 2), speechBubble.y + 35, 36, BLACK);
    DrawText(npcTranslit, speechBubble.x + (speechBubble.width / 2) - (MeasureText(npcTranslit, 18) / 2), speechBubble.y + 100, 18, DARKGRAY);
    DrawText(npcEnglish, speechBubble.x + (speechBubble.width / 2) - (MeasureText(npcEnglish, 20) / 2), speechBubble.y + 150, 20, (Color){27, 58, 92, 255});

    // 4. Action Prompt Label
    DrawText("How will you respond?", 360, 365, 20, GOLD);

    // 5. Answer Choices Buttons (A, B, C Staged Layout)
    Rectangle optA = { 360, 410, 860, 55 };
    Rectangle optB = { 360, 480, 860, 55 };
    Rectangle optC = { 360, 550, 860, 55 };

    Vector2 mousePos = GetMousePosition();
    bool overA = CheckCollisionPointRec(mousePos, optA);
    bool overB = CheckCollisionPointRec(mousePos, optB);
    bool overC = CheckCollisionPointRec(mousePos, optC);

    // Option A
    DrawRectangleRounded(optA, 0.15f, 4, overA ? (Color){50, 60, 75, 255} : DARKGRAY);
    DrawRectangleRoundedLines(optA, 0.15f, 4, 2, overA ? GOLD : GRAY);
    DrawText("A", optA.x + 20, optA.y + 16, 20, GOLD);
    const char* textA = "وَعَلَيْكُمُ السَّلَام (wa-alaykum us-salaam)";
    int textAX = optA.x + 70;
    int textAY = optA.y + 18;
    DrawText(textA, textAX, textAY, 18, WHITE);
    if (overA) DrawLine(textAX, textAY + 20, textAX + MeasureText(textA, 18), textAY + 20, GOLD);

    // Option B
    DrawRectangleRounded(optB, 0.15f, 4, overB ? (Color){50, 60, 75, 255} : DARKGRAY);
    DrawRectangleRoundedLines(optB, 0.15f, 4, 2, overB ? GOLD : GRAY);
    DrawText("B", optB.x + 20, optB.y + 16, 20, GOLD);
    const char* textB = "مَرْحَبًا (marhaban)";
    int textBX = optB.x + 70;
    int textBY = optB.y + 18;
    DrawText(textB, textBX, textBY, 18, WHITE);
    if (overB) DrawLine(textBX, textBY + 20, textBX + MeasureText(textB, 18), textBY + 20, GOLD);

    // Option C
    DrawRectangleRounded(optC, 0.15f, 4, overC ? (Color){50, 60, 75, 255} : DARKGRAY);
    DrawRectangleRoundedLines(optC, 0.15f, 4, 2, overC ? GOLD : GRAY);
    DrawText("C", optC.x + 20, optC.y + 16, 20, GOLD);
    const char* textC = "شُكْرًا (shukran)";
    int textCX = optC.x + 70;
    int textCY = optC.y + 18;
    DrawText(textC, textCX, textCY, 18, WHITE);
    if (overC) DrawLine(textCX, textCY + 20, textCX + MeasureText(textC, 18), textCY + 20, GOLD);

    DrawText("Press [M] to return to Main Menu", 60, 40, 14, LIGHTGRAY);
 main
    if (IsKeyPressed(KEY_M)) state.currentScreen = MENU_SCREEN;
}

void drawProgress() {}

int main() {
    InitWindow(1280, 720, "Polyglot Quest");
    SetTargetFPS(60);

 feature-flashcards
    // Load Flashcards and Scenarios
    totalCards = loadFlashcards(gameCards);
    totalScenarios = loadScenarios(gameScenarios);

    // Day 6: Load saved progress
    loadProgress(&state);

    printf("Successfully initialized backend! Loaded %d cards and %d scenarios.\n", totalCards, totalScenarios);

 feature-flashcards
    // Load Flashcards and Scenarios
    totalCards = loadFlashcards(gameCards);
    totalScenarios = loadScenarios(gameScenarios);

    printf("Successfully initialized backend! Loaded %d cards and %d scenarios.\n", totalCards, totalScenarios);

    totalCards = loadFlashcards(gameCards);
    printf("Successfully initialized backend! Loaded %d cards.\n", totalCards);
 main
 main

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

    // Day 6: Save progress when closing game
    saveProgress(&state);

    CloseWindow();
    return 0;
}