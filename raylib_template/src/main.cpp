#include <raylib.h>

#define W_WIDTH 500
#define W_HEIGHT 500

int main()
{
    InitWindow(W_WIDTH, W_HEIGHT, "Raylib Template");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}