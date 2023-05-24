#include <raylib.h>

const int screenWidth = 800;
const int screenHeight = 450;

// Define a structure to represent a wall
struct Wall {
    Vector2 start;
    Vector2 end;
};

// Function to check if two lines intersect
bool doLinesIntersect(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4) {
    float den = (p4.y - p3.y) * (p2.x - p1.x) - (p4.x - p3.x) * (p2.y - p1.y);
    if (den == 0) {
        return false;
    }

    float ua = ((p4.x - p3.x) * (p1.y - p3.y) - (p4.y - p3.y) * (p1.x - p3.x)) / den;
    float ub = ((p2.x - p1.x) * (p1.y - p3.y) - (p2.y - p1.y) * (p1.x - p3.x)) / den;

    if (ua >= 0 && ua <= 1 && ub >= 0 && ub <= 1) {
        return true;
    }

    return false;
}

// Function to get a Vector2 object with both x and y components set to 0
Vector2 Vector2Zero() {
    return {0, 0};
}

// Function to add two Vector2 objects
Vector2 Vector2Add(Vector2 v1, Vector2 v2) {
    return {v1.x + v2.x, v1.y + v2.y};
}

// Function to subtract two Vector2 objects
Vector2 Vector2Subtract(Vector2 v1, Vector2 v2) {
    return {v1.x - v2.x, v1.y - v2.y};
}

// Function to scale a Vector2 object by a scalar value
Vector2 Vector2Scale(Vector2 v, float scalar) {
    return {v.x * scalar, v.y * scalar};
}


// Function to compare two Vector2 objects for equality
bool Vector2IsEqual(Vector2 v1, Vector2 v2) {
    return (v1.x == v2.x && v1.y == v2.y);
}

// Function to calculate the point of intersection between two lines
Vector2 GetCollisionPoint(Vector2 line1Start, Vector2 line1End, Vector2 line2Start, Vector2 line2End) {
    float x1 = line1Start.x;
    float y1 = line1Start.y;
    float x2 = line1End.x;
    float y2 = line1End.y;

    float x3 = line2Start.x;
    float y3 = line2Start.y;
    float x4 = line2End.x;
    float y4 = line2End.y;

    float denominator = ((x1 - x2) * (y3 - y4)) - ((y1 - y2) * (x3 - x4));

    if (denominator == 0) {
        // Lines are parallel, return (0, 0)
        return {0, 0};
    }

    float px = ((x1 * y2 - y1 * x2) * (x3 - x4)) - ((x1 - x2) * (x3 * y4 - y3 * x4));
    float py = ((x1 * y2 - y1 * x2) * (y3 - y4)) - ((y1 - y2) * (x3 * y4 - y3 * x4));

    return {px / denominator, py / denominator};
}


int main() {
    // Initialization
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "2D Shadowcaster");

    // Wall definition
    Wall walls[] = {
        {{100, 100}, {300, 100}},
        {{300, 100}, {300, 300}},
        {{300, 300}, {100, 300}},
        {{100, 300}, {100, 100}}
    };

    Vector2 playerPos = {screenWidth / 2, screenHeight / 2}; // Player position

    // Main game loop
    while (!WindowShouldClose()) {
        // Update

        // Input
        if (IsKeyDown(KEY_W)) playerPos.y -= 0.5;
        if (IsKeyDown(KEY_S)) playerPos.y += 0.5;
        if (IsKeyDown(KEY_A)) playerPos.x -= 0.5;
        if (IsKeyDown(KEY_D)) playerPos.x += 0.5;

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw walls
        for (const auto& wall : walls) {
            DrawLineEx(wall.start, wall.end, 1, BLACK);
        }

        // Cast shadows
        for (const auto& wall : walls) {
            Vector2 direction1 = Vector2Subtract(wall.start, playerPos);
            Vector2 direction2 = Vector2Subtract(wall.end, playerPos);

            Vector2 end1 = Vector2Add(playerPos, Vector2Scale(direction1, 1000));
            Vector2 end2 = Vector2Add(playerPos, Vector2Scale(direction2, 1000));

            Vector2 intersection1 = {0};
            Vector2 intersection2 = {0};

            // Check intersection with each wall
            for (const auto& w : walls) {
                if (doLinesIntersect(playerPos, end1, w.start, w.end)) {
                    intersection1 = GetCollisionPoint(playerPos, end1, w.start, w.end);
                }

                if (doLinesIntersect(playerPos, end2, w.start, w.end)) {
                    intersection2 = GetCollisionPoint(playerPos, end2, w.start, w.end);
                }
            }

                        // Draw shadow triangles
            if (!Vector2IsEqual(intersection1, Vector2Zero()) && !Vector2IsEqual(intersection2, Vector2Zero())) {
                DrawTriangle(playerPos, intersection1, intersection2, Fade(BLACK, 0.7f));
            }
        }

        // Draw player
        DrawCircleV(playerPos, 5, RED);

        EndDrawing();
    }

    // De-Initialization
    CloseWindow();

    return 0;
}
