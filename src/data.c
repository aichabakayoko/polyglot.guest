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