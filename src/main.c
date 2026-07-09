#include "raylib.h"
#include "types.h"
#include "logic.h"

int main() {
    InitWindow(1280, 720, "Polyglot Quest");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground((Color){13, 27, 42, 255});
        EndDrawing();
    }
    CloseWindow();
    return 0;
}