# Ensure the build directory exists locally
If (!(Test-Path -Path "build")) {
    New-Item -ItemType Directory -Path "build" | Out-Null
}

# Compile using your exact local configuration
gcc src/main.c src/render.c src/ui_menu.c src/ui_flashcards.c src/ui_scenarios.c src/ui_progress.c src/data.c src/logic.c `
  -I"C:/Users/nayin/Downloads/winlibs-x86_64-posix-seh-gcc-15.2.0-mingw-w64ucrt-13.0.0-r6/mingw64/include" `
  -L"C:/Users/nayin/Downloads/winlibs-x86_64-posix-seh-gcc-15.2.0-mingw-w64ucrt-13.0.0-r6/mingw64/lib" `
  -o build/game.exe -lraylib -lopengl32 -lgdi32 -lwinmm