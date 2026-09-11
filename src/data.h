#ifndef DATA_H
#define DATA_H

#include "types.h"

int loadFlashcards(Flashcard* cards);
int loadScenarios(Scenario* scenarios);

// Progress management
int saveProgress(const GameState* state);
int loadProgress(GameState* state);

#endif