#include "data.h"
#include <stddef.h>
#include <stdio.h>

Flashcard flashcards[30] = {
    // Greetings (1-5)
    {"ﺎًﺒَﺣْﺮَﻣ", "Hello", "marhaban", "Greetings", 0},
    {"ْﻢُﻜْﻴَﻠَﻋ ُﻡَﻼَّﺴﻟﺍ", "Peace be upon you", "as-salaamu alaykum", "Greetings", 0},
    {"َﻚُﻟﺎَﺣ َﻒْﻴَﻛ", "How are you", "kayfa haluka", "Greetings", 0},
    {"ﺍًﺮْﻜُﺷ", "Thank you", "shukran", "Greetings", 0},
    {"ﺔَﻣَﻼَّﺴﻟﺍ َﻊَﻣ", "Goodbye", "ma'a as-salaama", "Greetings", 0},
    // Numbers (6-10)
    {"ﺪِﺣﺍَﻭ", "One", "waahid", "Numbers", 0},
    {"ﻥﺎَﻨْﺛِﺍ", "Two", "ithnan", "Numbers", 0},
    {"ﺔَﺛَﻼَﺛ", "Three", "thalatha", "Numbers", 0},
    {"ﺔَﻌَﺑْﺭَﺃ", "Four", "arba'a", "Numbers", 0},
    {"ﺔَﺴْﻤَﺧ", "Five", "khamsa", "Numbers", 0},
    // Family (11-15)
    {"ﺏَﺃ", "Father", "ab", "Family", 0},
    {"ﻡُﺃ", "Mother", "umm", "Family", 0},
    {"ﺥَﺃ", "Brother", "akh", "Family", 0},
    {"ﺖْﺧُﺃ", "Sister", "ukht", "Family", 0},
    {"ﺔَﻠِﺋﺎَﻋ", "Family", "a'ilah", "Family", 0},
    // Food (16-20)
    {"ﺰْﺒُﺧ", "Bread", "khubz", "Food", 0},
    {"ﺀﺎَﻣ", "Water", "maa'", "Food", 0},
    {"ﻡﺎَﻌَﻃ", "Food", "ta'am", "Food", 0},
    {"ﻱﺎَﺷ", "Tea", "shay", "Food", 0},
    {"ﺓَﻮْﻬَﻗ", "Coffee", "qahwah", "Food", 0},
    // Travel (21-25)
    {"ﺭﺎَﻄَﻣ", "Airport", "matar", "Travel", 0},
    {"ﻕُﺪْﻨُﻓ", "Hotel", "funduq", "Travel", 0},
    {"ﻉِﺭﺎَﺷ", "Street", "shari'", "Travel", 0},
    {"ﺓَﺭﺎَّﻴَﺳ", "Car", "sayyaratun", "Travel", 0},
    {"ﺔَﻠِﻓﺎَﺣ", "Bus", "hafilah", "Travel", 0},
    // Time (26-30)
    {"ﻡْﻮَﻴﻟﺍ", "Today", "al-yawm", "Time", 0},
    {"ﺍًﺪَﻏ", "Tomorrow", "ghadan", "Time", 0},
    {"ﺲْﻣَﺃ", "Yesterday", "ams", "Time", 0},
    {"ﺡﺎَﺒَﺻ", "Morning", "sabah", "Time", 0},
    {"ﺀﺎَﺴَﻣ", "Evening", "mosa'a", "Time", 0},
};

int loadFlashcards(Flashcard* cards) {
    if (cards == NULL) return 0;
    for (int i = 0; i < 30; i++) {
        cards[i] = flashcards[i];
    }
    return 30;
}

Scenario gameScenarios[10] = {
    // 0: Coffee
    {"ﺓﻮﻬﻗ ﺪﻳﺭﺃ ﻚﻠﻀﻓ ﻦﻣ", "Min fadlik ureedu qahwah", "Please, I want coffee", {"Min fadlik ureedu qahwah", "Marhaban", "Afwan"}, 0, 10},
    // 1: Market
    {"؟ﺍﺬﻫ ﺮﻌﺳ ﻢﻛ", "Kam si'r hadha?", "How much is this?", {"Marhaban", "Kam si'r hadha?", "Shukran"}, 1, 10},
    // 2: Taxi
    {"ﻚﻠﻀﻓ ﻦﻣ ﺔﻄﺤﻤﻟﺍ ﻰﻟﺇ", "Ila al-mahattah min fadlik", "To the station please", {"Afwan", "Na'am", "Ila al-mahattah min fadlik"}, 2, 10},
    // 3: Price
    {"؟ﺍﺬﻫ ﻢﻜﺑ", "Bikam hadha?", "How much is this?", {"Bikam hadha?", "Shukran", "Na'am"}, 0, 10},
    // 4: Hospital
    {"؟ﻰﻔﺸﺘﺴﻤﻟﺍ ﻦﻳﺃ", "Ayna al-mustashfa?", "Where is the hospital?", {"Laa", "Ayna al-mustashfa?", "Marhaban"}, 1, 10},
    // 5: Goodbye
    {"ﺔﻣﻼﺴﻟﺍ ﻊﻣ", "Ma'a as-salamah", "Goodbye", {"Afwan", "Shukran", "Ma'a as-salamah"}, 2, 10},
    // 6: Thanks
    {"ﻼﻳﺰﺟ ﺍﺮﻜﺷ", "Shukran jazeelan", "Thank you very much", {"Shukran jazeelan", "Ayna?", "Bikam?"}, 0, 10},
    // 7: Welcome
    {"ﺍﻮﻔﻋ", "Afwan", "You are welcome", {"Laa", "Afwan", "Na'am"}, 1, 10},
    // 8: Greeting
    {"؟ﻚﻟﺎﺣ ﻒﻴﻛ", "Kayfa haluk?", "How are you?", {"Shukran", "Marhaban", "Kayfa haluk?"}, 2, 10},
    // 9: Water
    {"ﻚﻠﻀﻓ ﻦﻣ ﺀﺎﻣ ﺪﻳﺭﺃ", "Ureedu maa'an min fadlik", "I want water please", {"Ureedu maa'an min fadlik", "Ma'a as-salamah", "Afwan"}, 0, 10},
};

int loadScenarios(Scenario* sc) {
    if (sc == NULL) return 0;
    for (int i = 0; i < 10; i++) {
        sc[i] = gameScenarios[i];
    }
    return 10;
}

int saveProgress(const GameState* state) {
    if (state == NULL) return 0;
    FILE* file = fopen("savegame.dat", "wb");
    if (file == NULL) return 0;
    
    size_t written = fwrite(state, sizeof(GameState), 1, file);
    fclose(file);
    return (written == 1) ? 1 : 0;
}

int loadProgress(GameState* state) {
    if (state == NULL) return 0;
    FILE* file = fopen("savegame.dat", "rb");
    if (file == NULL) return 0;
    
    size_t read = fread(state, sizeof(GameState), 1, file);
    fclose(file);
    return (read == 1) ? 1 : 0;
}