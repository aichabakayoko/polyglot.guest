// src/types.h
#ifndef TYPES_H
#define TYPES_H

#define TOTAL_SCENARIOS 10
#define TOTAL_FLASHCARDS 30

typedef enum {
    MENU_SCREEN,
    FLASHCARD_SCREEN,
    SCENARIO_SCREEN,
    PROGRESS_SCREEN
} Screen;

typedef struct {
    char arabic[100];
    char english[100];
    char transliteration[100];
    char category[50];
    int masteryLevel;
} Flashcard;

typedef struct {
    char prompt[200];
    char transliteration[200];
    char translation[200];
    char options[3][100];
    int correctIndex;
    int scoreValue;
} Scenario;

typedef struct {
    Screen currentScreen;
    int totalScore;
    int correctCount;
    int wrongCount;
    int currentCardIndex;
    int currentScenarioStep;
    int isRevealed;
} GameState;

#endif