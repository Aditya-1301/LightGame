#include <raylib.h>
#include <stdio.h>
#include <math.h>
#include "behaviour.cpp"

bool collisionWithEnemy(Object* player, Object * enemy){
    int p_x = player -> position.x;
    int p_y = player -> position.y;
    int p_w = (int)((player -> objectImage.width) / 2);
    int p_h = (int)((player -> objectImage.height) / 2) ;
    int e_x = enemy -> position.x;
    int e_y = enemy -> position.y;
    int e_w = (int)((enemy -> objectImage.width) / 2);
    int e_h = (int)((enemy -> objectImage.height) / 2);
    if(p_x + p_w > e_x - e_w){
        return true;
    }
    if(p_x - p_w < e_x + e_w){
        return true;
    }
    if(p_y - p_h < e_y + e_h){
        return true;
    }
    if(p_y + p_h < e_y - e_h){
        return true;
    }
    return false;
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

bool collisionWithEnemy2(Object* player, Object * enemy){
    if(CheckCollisionRecs(player->hitBox, enemy->hitBox)){
        return true;
    }
    return false;
}

void collisionLog2(Object* player, Object* enemy){
    int p_x = player -> position.x;
    int p_y = player -> position.y;
    int e_x = enemy -> position.x;
    int e_y = enemy -> position.y;
    if(collisionWithEnemy2(player, enemy)){
        printf("Collision Detected; p_coordinates -> %d, %d ; e_coordinates -> %d, %d", p_x, p_y, e_x, e_y);
    }
}

void playerMovement(Object * p, Object* e){
    int playerSize = 50;
    int move = 10;
    collisionLog2(p, e);
    if(!collisionWithEnemy2(p, e)){
        if(IsKeyDown(KEY_D) && p->position.x + move + playerSize <= GetScreenWidth()){
            p->position.x += move;
        }
        if(IsKeyDown(KEY_A) && p->position.x - move - playerSize > 0){
            p->position.x -= move;
        }
        if(IsKeyDown(KEY_S) && p->position.y + move + playerSize <= GetScreenHeight()){
            p->position.y += move;
        }
        if(IsKeyDown(KEY_W) && p->position.y - move - playerSize > 0){
            p->position.y -= move;
        }
    }
}