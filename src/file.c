#include <stdio.h>
#include "file.h"

void saveProgress(GameState* s) {
    FILE* f = fopen("progress.txt", "w");
    if (f == NULL) {
        return;
    }
    
    fprintf(f, "%d %d %d\n", s->totalScore, s->correctCount, s->wrongCount);
    fclose(f);
}

void loadProgress(GameState* s) {
    FILE* f = fopen("progress.txt", "r");
    if (f == NULL) {
        return;
    }
    
    fscanf(f, "%d %d %d", &s->totalScore, &s->correctCount, &s->wrongCount);
    fclose(f);
}