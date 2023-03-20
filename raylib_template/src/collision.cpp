#include <raylib.h>
#include <stdio.h>
#include <math.h>
#include "behaviour.cpp"

bool collisionWithEnemy(Object * player, Object * enemy);
void collisionLog(Object * player, Object * enemy);
void playerMovement(Object * player, Object * enemy);

bool collisionWithEnemy(Object* player, Object * enemy){
    return CheckCollisionRecs(player->hitBox, enemy->hitBox);
}

void collisionLog(Object* player, Object* enemy){
    int p_x = player -> position.x;
    int p_y = player -> position.y;
    int e_x = enemy -> position.x;
    int e_y = enemy -> position.y;
    if(collisionWithEnemy(player, enemy)){
        printf("Collision Detected; p_coordinates -> %d, %d ; e_coordinates -> %d, %d", p_x, p_y, e_x, e_y);
    }
}

void playerMovement(Object * player, Object* enemy){
    int playerSize = 50;
    int move = 10;
    if(!collisionWithEnemy(player,enemy)){
        player->availableDirections[0] = 'W';
        player->availableDirections[1] = 'A';
        player->availableDirections[2] = 'S';
        player->availableDirections[3] = 'D';
    }

    if(IsKeyDown(KEY_D) && player->position.x + move + playerSize <= GetScreenWidth() && player->availableDirections[3] == 'D'){
        player->position.x += move;
        player->hitBox.x =(player->position.x - playerSize);
        if(collisionWithEnemy(player,enemy)) player->availableDirections[3] = '\0';
    }
    if(IsKeyDown(KEY_A) && player->position.x - move - playerSize > 0 && player->availableDirections[1] == 'A'){
        player->position.x -= move;
        player->hitBox.x =(player->position.x - playerSize);
        if(collisionWithEnemy(player,enemy)) player->availableDirections[1] = '\0';
    }
    if(IsKeyDown(KEY_S) && player->position.y + move + playerSize <= GetScreenHeight() && player->availableDirections[2] == 'S'){
        player->position.y += move;
        player->hitBox.y =(player->position.y - playerSize);
        if(collisionWithEnemy(player,enemy)) player->availableDirections[2] = '\0';
    }
    if(IsKeyDown(KEY_W) && player->position.y - move - playerSize > 0 && player->availableDirections[0] == 'W'){
        player->position.y -= move;
        player->hitBox.y =(player->position.y - playerSize);
        if(collisionWithEnemy(player,enemy)) player->availableDirections[0] = '\0';
    }
}

