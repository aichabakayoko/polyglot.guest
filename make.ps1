# Ensure build folder exists
if (!(Test-Path -Path "build")) {
    New-Item -ItemType Directory -Path "build" | Out-Null
}

# Raylib paths on your laptop
$RAYLIB_INC = "C:/raylib/raylib/src"
$RAYLIB_LIB = "C:/raylib/raylib/src"

gcc src/main.c src/render.c src/ui_menu.c src/ui_flashcards.c src/ui_scenarios.c src/ui_progress.c src/data.c src/logic.c `
  "-I$RAYLIB_INC" `
  "-L$RAYLIB_LIB" `
  -o build/game.exe -lraylib -lopengl32 -lgdi32 -lwinmm