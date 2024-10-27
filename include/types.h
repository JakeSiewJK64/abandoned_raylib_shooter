#pragma once
#include <raylib.h>

#define MAX_BULLETS 1000
#define PLAYER_SPEED 4.0f
#define MAX_BULLETS 1000
#define ENEMIES_COUNT 5
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 800
#define ENEMIES_COUNT 5

typedef enum GAME_OBJECT_STATUS {
  ACTIVE = 0,
  INACTIVE = 1,
} GAME_OBJECT_STATUS;

typedef struct GameObject {
  Texture2D texture;
  Vector2 position;
  Vector2 bullets[MAX_BULLETS];
  double last_shot_fired;
  double fire_rate;
  int distance_travelled;
  int width;
  int height;
  int bullet_count;
  GAME_OBJECT_STATUS status;
} GameObject;

typedef struct PlayBoundary {
  float width;
  float height;
  Vector2 top_left;
  Vector2 bottom_right;
} PlayBoundary;