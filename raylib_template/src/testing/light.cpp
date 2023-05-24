#include <raylib.h>

const int screenWidth = 800;
const int screenHeight = 450;

int main()
{
    // Initialize Raylib
    InitWindow(screenWidth, screenHeight, "Hard 2D Shadows");
    
    // Define the rectangle to draw
    Rectangle rect = { screenWidth / 2 - 100, screenHeight / 2 - 100, 300, 300 };
    
    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        
        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        // Draw the rectangle with a shadow
        DrawRectangle(rect.x + 5, rect.y + 5, rect.width, rect.height, Fade(BLACK, 0.5f));
        DrawRectangle(rect.x, rect.y, rect.width, rect.height, RED);
        
        EndDrawing();
    }
    
    // Close the window
    CloseWindow();
    
    return 0;
}
