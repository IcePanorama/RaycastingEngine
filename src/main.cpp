#include <iostream>
#include <raylib.h>

int
main ()
{
  InitWindow (800, 450, "Raylib [core] example - basic window");

  while (!WindowShouldClose ())
    {
      BeginDrawing ();
      ClearBackground (RAYWHITE);
      DrawText ("Congrats! You created your first window!", 190, 200, 20,
                LIGHTGRAY);
      EndDrawing ();
    }

  return 0;
}
