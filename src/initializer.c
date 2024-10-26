#include "../include/initializer.h"
#include <raylib.h>

void InitializeConfigurations(int SCREEN_WIDTH, int SCREEN_HEIGHT) {
  // Tell the window to use vysnc and work on high DPI displays
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_RESIZABLE);
  SetTargetFPS(60);

  // Initialize audio device
  InitAudioDevice();

  // Create the window and OpenGL context
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello Raylib");
}