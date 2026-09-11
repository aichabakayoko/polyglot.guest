#include "data.h"

Flashcard flashcards[30] = {
    // Greetings (1-5)
    {"مَرْحَبًا", "Hello", "marhaban", "Greetings", 0},
    {"السَّلَامُ عَلَيْكُمْ", "Peace be upon you", "as-salaamu alaykum", "Greetings", 0},
    {"كَيْفَ حَالُكَ", "How are you", "kayfa haluka", "Greetings", 0},
    {"شُكْرًا", "Thank you", "shukran", "Greetings", 0},
    {"مَعَ السَّلَامَة", "Goodbye", "ma'a as-salaama", "Greetings", 0},

    // Numbers (6-10)
    {"وَاحِد", "One", "waahid", "Numbers", 0},
    {"اِثْنَان", "Two", "ithnan", "Numbers", 0},
    {"ثَلَاثَة", "Three", "thalatha", "Numbers", 0},
    {"أَرْبَعَة", "Four", "arba'a", "Numbers", 0},
    {"خَمْسَة", "Five", "khamsa", "Numbers", 0},

    // Family (11-15)
    {"أَب", "Father", "ab", "Family", 0},
    {"أُم", "Mother", "umm", "Family", 0},
    {"أَخ", "Brother", "akh", "Family", 0},
    {"أُخْت", "Sister", "ukht", "Family", 0},
    {"عَائِلَة", "Family", "a'ilah", "Family", 0},

    // Food (16-20)
    {"خُبْز", "Bread", "khubz", "Food", 0},
    {"مَاء", "Water", "maa'", "Food", 0},
    {"طَعَام", "Food", "ta'am", "Food", 0},
    {"شَاي", "Tea", "shay", "Food", 0},
    {"قَهْوَة", "Coffee", "qahwah", "Food", 0},

    // Travel (21-25)
    {"مَطَار", "Airport", "matar", "Travel", 0},
    {"فُنْدُق", "Hotel", "funduq", "Travel", 0},
    {"شَارِع", "Street", "shari'", "Travel", 0},
    {"سَيَّارَة", "Car", "sayyaratun", "Travel", 0},
    {"حَافِلَة", "Bus", "hafilah", "Travel", 0},

    // Time (26-30)
    {"اليَوْم", "Today", "al-yawm", "Time", 0},
    {"غَدًا", "Tomorrow", "ghadan", "Time", 0},
    {"أَمْس", "Yesterday", "ams", "Time", 0},
    {"صَبَاح", "Morning", "sabah", "Time", 0},
    {"مَسَاء", "Evening", "mosa'a", "Time", 0}
};

int loadFlashcards(Flashcard* cards) {
    for (int i = 0; i < 30; i++) {
        cards[i] = flashcards[i];
    }
    return 30;
}

Scenario scenarios[10] = {
    // 0: Coffee
    {"من فضلك أريد قهوة", "Min fadlik ureedu qahwah", "Please, I want coffee", {"Shukran", "Marhaban", "Afwan"}, 0, 10},
    // 1: Market
    {"كم سعر هذا؟", "Kam si'r hadha?", "How much is this?", {"Marhaban", "Kam si'r hadha?", "Shukran"}, 1, 10},
    // 2: Taxi
    {"إلى المحطة من فضلك", "Ila al-mahattah min fadlik", "To the station please", {"Afwan", "Na'am", "Ila al-mahattah min fadlik"}, 2, 10},
    // 3: Price
    {"بكم هذا؟", "Bikam hadha?", "How much is this?", {"Bikam hadha?", "Shukran", "Na'am"}, 0, 10},
    // 4: Hospital
    {"أين المستشفى؟", "Ayna al-mustashfa?", "Where is the hospital?", {"Laa", "Ayna al-mustashfa?", "Marhaban"}, 1, 10},
    // 5: Goodbye
    {"مع السلامة", "Ma'a as-salamah", "Goodbye", {"Afwan", "Shukran", "Ma'a as-salamah"}, 2, 10},
    // 6: Thanks
    {"شكرا جزيلا", "Shukran jazeelan", "Thank you very much", {"Shukran jazeelan", "Ayna?", "Bikam?"}, 0, 10},
    // 7: Welcome
    {"عفوا", "Afwan", "You are welcome", {"Laa", "Afwan", "Na'am"}, 1, 10},
    // 8: Greeting
    {"كيف حالك؟", "Kayfa haluk?", "How are you?", {"Shukran", "Marhaban", "Kayfa haluk?"}, 2, 10},
    // 9: Water
    {"أريد ماء من فضلك", "Ureedu maa'an min fadlik", "I want water please", {"Ureedu maa'an min fadlik", "Ma'a as-salamah", "Afwan"}, 0, 10}
};

int loadScenarios(Scenario* sc) {
    for (int i = 0; i < 10; i++) {
        sc[i] = scenarios[i];
    }
    return 10;
}