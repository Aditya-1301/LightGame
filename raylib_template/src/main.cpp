#include <raylib.h>
#include <stdio.h>
#include <math.h>
#include "collision.cpp"

#define W_WIDTH 1368
#define W_HEIGHT 768

Image level1Image = LoadImage("D:\\RayLib\\LightGame\\raylib_template\\src\\resources\\level.png");
Image frameImage = LoadImage("D:\\RayLib\\LightGame\\raylib_template\\src\\resources\\levels\\frame.png");
Image enemyImage = LoadImage("D:\\RayLib\\LightGame\\raylib_template\\src\\resources\\enemy\\enemy.png");

int main()
{
    InitWindow(W_WIDTH, W_HEIGHT, "Raylib Template");
    SetTargetFPS(60);
    
    Texture frameTex = LoadTextureFromImage(frameImage);
    Texture enemyTex = LoadTextureFromImage(enemyImage);

    Object player = {0};
    Object enemy = { enemyImage, {0,0}};
    setPlayer(&player, 60, 60);
    setEnemy(&enemy, 150, 150);
    setPlayerHitBoxRectangular(&player, 100, 100);
    setEnemyHitBoxRectangular(&enemy, enemyImage.height, enemyImage.width);

    //printf("Level1 Height = %d | Level1 Width = %d", level1.height, level1.width);
    while (!WindowShouldClose())
    {
        //While logic
        playerMovement(&player,&enemy);
        //collisionLog(&player, &enemy);
        //Begin Drawing
        BeginDrawing();
        ClearBackground(WHITE);
        //DrawTexture(frameTex, 0, 0, WHITE);
        DrawRectangle(enemy.position.x, enemy.position.y, enemy.hitBox.width, enemy.hitBox.height, BLUE);
        DrawTexture(enemyTex, enemy.position.x, enemy.position.y, WHITE);
        DrawRectangle(player.hitBox.x, player.hitBox.y, player.hitBox.width, player.hitBox.height, GREEN);
        DrawCircle(player.position.x, player.position.y, 50, RED);
        EndDrawing();
    }

    UnloadImage(frameImage);
    UnloadImage(enemyImage);

    CloseWindow();

    return 0;
}


/*
1. We can probably have a rectangular hitbox for each object (Enemy/Player etc). -
2. We can have an array that contains positions of each enemy or object in the map at all times so that we can always check for collisions.
3. We might need to resort to using a true/false array instead for the collision of the map boundaries and such (maybe). 
*/