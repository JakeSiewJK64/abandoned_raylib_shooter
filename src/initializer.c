#include "../include/initializer.h"
#include <raylib.h>

int InitializeConfigurations(int screen_width, int screen_height) {
  // Tell the window to use vysnc and work on high DPI displays
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_RESIZABLE);
  SetTargetFPS(60);

  // Initialize audio device
  InitAudioDevice();

  // Create the window and OpenGL context
  InitWindow(screen_width, screen_height, "Hello Raylib");

  return 0;
}