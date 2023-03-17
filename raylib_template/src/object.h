#pragma once
#include <raylib.h>

#ifndef OBJECT
typedef struct Object{
    Image objectImage;
    Rectangle hitBox; // The hitbox probably will need to be scaled according to the image's size.
    Vector2 position; // Vector2 Contains the X and Y coordinates of the Player.
}Object;
#endif