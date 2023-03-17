#include <raylib.h>
#include <stdio.h>
#include <math.h>
#include "object.h"

void setPlayerHitBoxRectangular(Object * p, int width, int height){
    Rectangle hitBox = { p -> position.x, p-> position.y, width, height };
    p -> hitBox = hitBox;
}

void setEnemyHitBoxRectangular(Object * e, int height, int width){
    Rectangle hitBox = { e -> position.x, e -> position.y, width, height};
    e -> hitBox = hitBox;
}

void setPlayer(Object* p, int x, int y){
    p -> position.x = x;
    p -> position.y = y;
}

void setEnemy(Object* p, int x, int y){
    p -> position.x = x;
    p -> position.y = y;
}


