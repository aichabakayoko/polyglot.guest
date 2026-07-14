# 🌟 Polyglot Quest

*Polyglot Quest* is an interactive C-based Arabic language learning application built using the [Raylib](https://www.raylib.com/) game library.

---

## 👥 Team & Roles
- **Nayima**: UI Developer (Rendering, Screens, Button Layouts, and Local Build Systems)
- **Saïda**: Logic Developer (State Machine, Scoring, Answer Verification)
- **Aïcha**: Data Manager & GitHub Maintainer (Data Structures, File I/O, Version Control)

---

## 🚀 Key Features
- **Main Menu:** Dynamic, responsive navigation screen.
- **Flashcard Mode:** 30 Arabic vocabulary cards spread across categories with instant transliteration and English translations.
- **Scenario Mode:** Interactive dialogue scenarios with real-life NPC conversations and choice-based responses.
- **Progress Tracking & File I/O:** Automatic saving and loading of total score, accuracy %, and current card progress via `progress.txt`.

---

## 🛠️ Build & Run

### 💻 Windows (PowerShell)
* **Build only:** `.\make.ps1`
* **Build and run:** `.\test.ps1`
* **Manual GCC Compile & Run:**
  ```powershell
  gcc src/main.c src/logic.c src/data.c -I"C:/raylib/raylib/src" -L"C:/raylib/raylib/src" -lraylib -lopengl32 -lgdi32 -lwinmm -o build/game.exe
  ./build/game.exe
  ```

### 🐧 macOS / Linux / Git Bash (Shell)
* **Build only:** `bash make.sh`
* **Build and run:** `bash test.sh`

---

## 📂 Project Structure
```text
polyglot.guest/
├── .gitignore          # Root-level Git filter (ignores build files and executables)
├── README.md           # Project documentation
├── make.ps1            # Windows PowerShell compile script
├── test.ps1            # Windows PowerShell compile & execute script
├── make.sh             # UNIX/Bash compile script
├── test.sh             # UNIX/Bash compile & execute script
└── src/                # Project source files
    ├── data.c / .h     # Data storage, saving/loading, and initialization
    ├── logic.c / .h    # Core state machine, scoring, and input validation
    ├── main.c          # Game entry point, engine loop, and UI rendering
    └── types.h         # Shared structures, screens, and game states
```