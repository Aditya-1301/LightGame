#include <raylib.h>
#include <math.h>

const int screenWidth = 800;
const int screenHeight = 450;

bool CheckPolygonCollision(Vector2* poly1, int numVertices1, Vector2* poly2, int numVertices2);

int main()
{
    // Initialize Raylib
    InitWindow(screenWidth, screenHeight, "Checking Polygon Collision");
    
    // Define the vertices of two polygons
    Vector2 poly1[] = { { 100, 100 }, { 150, 50 }, { 200, 100 }, { 150, 150 } };
    Vector2 poly2[] = { { 150, 50 }, { 300, 200 }, { 350, 250 }, { 300, 300 } };

    Vector2 center = {400, 300};
    int sides = 6;
    float radius = 50.0f;
    float rotation = 45.0f * DEG2RAD; // convert degrees to radians
    Color color = YELLOW;
    
    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        
        // Check for collision between the two polygons
        bool collision = CheckPolygonCollision(poly1, 5, poly2, 4);
        
        // Draw the polygons on the screen, highlighting them if they are colliding
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        DrawPoly(*poly1, 5, radius, rotation, collision ? GREEN : RED);
        DrawPoly(*poly2, 4, radius, rotation, collision ? GREEN : BLUE);

        //DrawPoly(center, sides, radius, rotation, color);

        
        EndDrawing();
    }
    
    // Clean up
    CloseWindow();
    
    return 0;
}

bool CheckPolygonCollision(Vector2* poly1, int numVertices1, Vector2* poly2, int numVertices2)
{
    // Calculate the normal vectors for each edge of both polygons
    Vector2 normals[(numVertices1 + numVertices2) * 2];
    int numNormals = 0;

    for (int i = 0; i < numVertices1; i++)
    {
        Vector2 edge = {0};
        if (i < numVertices1 - 1)
        {
            edge.x = poly1[i + 1].x - poly1[i].x;
            edge.y = poly1[i + 1].y - poly1[i].y;
        }
        else
        {
            edge.x = poly1[0].x - poly1[i].x;
            edge.y = poly1[0].y - poly1[i].y;
        }
        Vector2 normal = {-edge.y, edge.x};
        normals[numNormals++] = normal;
    }

    for (int i = 0; i < numVertices2; i++)
    {
        Vector2 edge = {0};
        if (i < numVertices2 - 1)
        {
            edge.x = poly2[i + 1].x - poly2[i].x;
            edge.y = poly2[i + 1].y - poly2[i].y;
        }
        else
        {
            edge.x = poly2[0].x - poly2[i].x;
            edge.y = poly2[0].y - poly2[i].y;
        }
        Vector2 normal = {-edge.y, edge.x};
        normals[numNormals++] = normal;
    }

    // Project each polygon onto each normal vector and check for overlap
    for (int i = 0; i < numNormals; i++)
    {
        Vector2 normal = normals[i];

        float min1 = INFINITY, max1 = -INFINITY;
        float min2 = INFINITY, max2 = -INFINITY;

        for (int j = 0; j < numVertices1; j++)
        {
            float projection = poly1[j].x * normal.x + poly1[j].y * normal.y;
            min1 = fmin(min1, projection);
            max1 = fmax(max1, projection);
        }

        for (int j = 0; j < numVertices2; j++)
        {
            float projection = poly2[j].x * normal.x + poly2[j].y * normal.y;
            min2 = fmin(min2, projection);
            max2 = fmax(max2, projection);
        }

        if (max1 < min2 || max2 < min1)
        {
            return false;
        }
    }

    return true;
}
