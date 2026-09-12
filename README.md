# 🌸 Polyglot Quest — Gamified Arabic Language Learning App

An interactive, C-based educational game built with [Raylib](https://github.com/aichabakayoko/polyglot.guest) designed to help learners master Arabic vocabulary, grammar, and scenario-based conversation.

---

## 📌 Project Overview

**Polyglot Quest** combines flashcard exercises and interactive NPC dialogue scenarios to teach Arabic using authentic Arabic scripts (via the Amiri font) and gamified progression mechanics (XP, streaks, and category mastery).

### **Key Features**
- **Interactive Flashcard Mode:** Practice vocabulary with real-time card counters, category mastery tracking, and practice timer heuristics.
- **Scenario Dialogue Mode:** Engage in 5-step conversational scenarios with NPC merchants, formatted dialogue boxes, and multi-choice options.
- **Arabic Text Engine:** Built-in Right-to-Left (RTL) Arabic text rendering using Amiri TTF font and unicode codepoints.
- **Progress & Mastery Tracking:** Live tracking of XP, streak count, category mastery percentages, and unlockable achievement trophies.
- **Settings & Data Management:** Master volume slider, mute toggles, and a two-step confirmation progress reset.

---

## 👥 Team & File Ownership Matrix

To prevent merge conflicts and maintain clean architectural boundaries, our team enforced a **Strict File Ownership Policy**: *Team members only edit files they own. Cross-module changes are handled via formal cross-team function requests.*

| File / Module | Owner | Responsibility |
| :--- | :--- | :--- |
| **`main.c`**, **`render.c/.h`**, **`ui_*.c/.h`** | **Nayima** | Window initialization, screen state dispatcher, and all UI screen drawing (`menu`, `flashcards`, `scenarios`, `progress`). |
| **`logic.c/.h`**, **`types.h`** | **Saïda** | State machine, scoring logic, streak/XP mechanics, mastery calculations, and shared types. |
| **`data.c/.h`**, **`assets/`** | **Aïcha** | Flashcard/scenario data layers, persistence (save/load/clear progress), asset management, and repo hygiene. |

---

## 🛠 Tech Stack & Architecture

- **Language:** C (C99 Standard)
- **Graphics & UI:** [Raylib](https://github.com/aichabakayoko/polyglot.guest)
- **Font Rendering:** Custom TTF loader (`LoadFontEx` / `DrawTextEx`) supporting Arabic Unicode codepoint ranges (`0x0600–0x06FF`, `0xFB50–0xFDFF`, `0xFE70–0xFEFC`)
- **Build System:** Custom PowerShell build & execution scripts (`./test.ps1` / `gcc`)

### **Project Structure**

```text
polyglot.guest/
├── .gitignore                    # Root-level Git filter (ignores build files and executables)
├── README.md                     # Project documentation
├── make.ps1                      # Windows PowerShell compile script
├── test.ps1                      # Windows PowerShell compile & execute script
├── make.sh                       # UNIX/Bash compile script
├── test.sh                       # UNIX/Bash compile & execute script
├── savegame.dat                  # Binary persistent save data (progress, XP, streaks)
└── src/                          # Project source files
    ├── data.c / .h               # Data storage, saving/loading, and initialization
    ├── logic.c / .h              # Core state machine, scoring, and input validation
    ├── main.c                    # Game entry point, engine loop, and UI rendering
    ├── render.c / .h             # Screen rendering dispatcher
    ├── ui_flashcards.c / .h      # Flashcard practice screen
    ├── ui_menu.c / .h            # Main Menu UI
    ├── ui_progress.c / .h        # Progress & trophy screen
    ├── ui_scenarios.c / .h       # Dialogue scenario screen
    └── types.h                   # Shared structures, screens, and game states
```

---

## ⚙️ Setup & Building

### **Prerequisites**

- **GCC Compiler** (MinGW-w64 on Windows)
- **Raylib Library** (configured in your C include/lib path)
- **PowerShell**

### **Building & Running**

To compile and launch the application directly:

**PowerShell**

```powershell
# Run the automated build script
./test.ps1
```

Or compile manually using GCC:

**PowerShell**

```powershell
gcc -o PolyglotQuest.exe src/*.c -lraylib -lopengl32 -lgdi32 -lwinmm
./PolyglotQuest.exe
```

---

## 🚧 Challenges & Technical Hurdles

During development, the team navigated several platform and architectural hurdles:

1. **Arabic Text Rendering (`??????` Glyph Issue):** Standard `DrawText()` calls failed on Arabic character ranges. Resolved by loading the Amiri TTF font with extended unicode codepoint ranges via `LoadFontEx()` and routing all Arabic rendering through `DrawTextEx()` with right-to-left placement adjustments.

2. **Windows & OneDrive Asset Locks:** Executing inside OneDrive environments produced reparse link locks (`-a---l`), blocking standard runtime asset loads. Fixed by introducing multi-path asset fallbacks and changing execution directories dynamically via `GetApplicationDirectory()`.

3. **Git File Lock Conflicts:** Git operations like `git pull` or branch checkout frequently hit `Permission denied` locks on `.git/FETCH_HEAD` due to concurrent background processes (OneDrive sync cycles and VS Code git auto-fetches). Unblocked using explicit stash workflows, `attrib` permissions resets, and commit non-edit flags.

4. **Raylib Audio Capture Constraints:** Raylib's native audio module supports audio playback but lacks built-in microphone recording capabilities. Adapted pronunciation testing into a *hold-duration heuristic evaluation model* without adding heavy external dependencies.

---

## 📋 Project Scope & Status

Following post-exam project adjustments, the application scope was streamlined to deliver a clean, stable, and feature-complete core loop.

### **✓ Included in Current Release**

- Full multi-screen navigation (`Menu`, `Flashcards`, `Scenarios`, `Progress`).
- Working Arabic text engine using Amiri font.
- 10 complete, interactive dialogue scenarios with visual step indicators.
- Live progress persistence across game sessions (XP, correct/wrong stats, mastery bars).
- Reset progress workflow with confirmation options.
- Multi-path font and asset fallback resolution.

### **✗ Descoped Features**

- *100-Flashcard Dataset Expansion* (descoped due to time constraints; maintained at core practice dataset).
- *Live Microphone Audio Recording* (descoped due to Raylib audio framework limits; replaced with hold-duration evaluation heuristic).
- *Merchant Voice Playback* (descoped in favor of visual dialogue flow and core audio FX).

---

## 🌿 Git Workflow & Rules

- **Branching:** Work is conducted exclusively on feature branches (`feature-*`). Direct pushes to `main` or `develop` are prohibited.
- **Commit Granularity:** Small, focused commits following Conventional Commits format (`type(scope): message`).
- **File Integrity:** Owners only modify files within their assigned domain to eliminate cross-file merge conflicts.
