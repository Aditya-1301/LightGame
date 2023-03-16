#include <raylib.h>
#include <stdio.h>

#define W_WIDTH 1368
#define W_HEIGHT 768

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

Image level1 = LoadImage("D:\\RayLib\\LightGame\\raylib_template\\src\\resources\\level.png");

typedef struct Player{
    int x;
    int y;
} Player;

void setPlayer(Player * p, int x, int y){
    p -> x = x;
    p -> y = y;
}

void playerMovement(Player* p){
    if(IsKeyDown(KEY_D)){
        p->x += 10;
    }
    if(IsKeyDown(KEY_A)){
        p->x -= 10;
    }
    if(IsKeyDown(KEY_S)){
        p->y += 10;
    }
    if(IsKeyDown(KEY_W)){
        p->y -= 10;
    }
}


int main()
{
    InitWindow(W_WIDTH, W_HEIGHT, "Raylib Template");
    SetTargetFPS(60);
    
    Texture t = LoadTextureFromImage(level1);
    Player p = {0};
    setPlayer(&p, 50, 50);

    printf("Level1 Height = %d | Level1 Width = %d", level1.height, level1.width);
    while (!WindowShouldClose())
    {
        //While logic
        playerMovement(&p);
        //Begin Drawing
        BeginDrawing();
        ClearBackground(WHITE);
        DrawTexture(t, 0, 0, RAYWHITE);
        //DrawCircle(p.x, p.y, 50, RED);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}