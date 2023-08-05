#include "raylib.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - input mouse wheel");

    int boxPositionY = screenHeight / 2 - 40;
    int scrollSpeed = 4;            // Scrolling speed in pixels

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    int i = 1;
    Rectangle rec[10];
    for (int j = 0; j < 10; j++)
        rec[j] = { 400, (float) 200 + 85*j, 80, 80 };

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        //boxPositionY -= (GetMouseWheelMove() * scrollSpeed);
        //----------------------------------------------------------------------------------
        if (GetMouseWheelMove()>0)
            i++;
        else if (GetMouseWheelMove() < 0)
            i--;
        
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);
        for (int j = 0; j < 10; j++)
            DrawRectangleRec(rec[j], RED);

        DrawText("Use mouse wheel to move the cube up and down!", 10, 10, 20, GRAY);
        //DrawText(TextFormat("Box position Y: %03i", boxPositionY), 10, 40, 20, LIGHTGRAY);
        DrawText(TextFormat("Index of Rec: %03i", i/5), 10, 70, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
