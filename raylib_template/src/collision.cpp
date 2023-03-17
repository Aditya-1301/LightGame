#include <raylib.h>
#include <stdio.h>
#include <math.h>
#include "object.cpp"

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