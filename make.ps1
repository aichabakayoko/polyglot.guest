# Ensure the build directory exists locally
If (!(Test-Path -Path "build")) {
    New-Item -ItemType Directory -Path "build" | Out-Null
}

# Compile using your exact local configuration
gcc src/main.c src/render.c src/ui_menu.c src/ui_flashcards.c src/ui_scenarios.c src/ui_progress.c src/ui_settings.c src/ui_infobar.c src/logic.c src/data.c -I"C:/raylib/raylib/src" -L"C:/raylib/raylib/src" -lraylib -lopengl32 -lgdi32 -lwinmm -o ./build/game.exe