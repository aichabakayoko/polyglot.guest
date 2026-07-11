# 🌟 Polyglot Quest

**Polyglot Quest** is an interactive C-based Arabic language learning application built using the [Raylib](https://www.raylib.com/) game library.

---

## 👥 Team & Roles
* **Nayima:** UI Developer (Rendering, Screens, Button Layouts)
* **Saïda:** Logic Developer (State Machine, Scoring, Answer Verification)
* **Aïcha:** Data Manager & GitHub Maintainer (Data Structures, File I/O, Version Control)

---

## 🚀 Key Features
* **Main Menu:** Dynamic navigation screen.
* **Flashcard Mode:** 30 Arabic vocabulary cards spread across categories with instant transliteration and English translations.
* **Scenario Mode:** Interactive dialogue scenarios with real-life NPC conversations and choice-based responses.
* **Progress Tracking & File I/O:** Automatic saving and loading of total score, accuracy %, and current card progress via `progress.txt`.

---

## 🛠️ Build & Run Instructions

### Prerequisites
* GCC / MinGW C Compiler
* Raylib library

### Compilation (VS Code / Terminal)
```bash
gcc src/main.c src/data.c src/logic.c -I src/ -L src/ -lraylib -lopengl32 -lgdi32 -lwinmm -o polyglot.exe    
 ```   
### Execution

```bash
./polyglot.exe
```

