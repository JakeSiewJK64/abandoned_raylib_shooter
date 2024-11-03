#pragma once
#include <raylib.h>

// define test mode
#ifndef TEST_MODE
#define IN_TEST_MODE false // If TEST_MODE is not defined, set to false
#else
#define IN_TEST_MODE true // If TEST_MODE is defined, set to true
#endif

// define debug mode
#ifndef DEBUG_MODE
#define IN_DEBUG_MODE false // If DEBUG_MODE is not defined, set to false
#else
#define IN_DEBUG_MODE true // If DEBUG_MODE is defined, set to true
#endif

#define MAX_BULLETS 1000
#define PLAYER_SPEED 4.0f
#define MAX_BULLETS 1000
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 800
#define ENEMIES_COUNT 10

typedef enum GAME_OBJECT_STATUS {
  ACTIVE = 0,
  INACTIVE = 1,
} GAME_OBJECT_STATUS;

typedef enum ENEMY_TYPE { TURRET, DRONE } ENEMY_TYPE;

typedef enum BULLET_SPEED {
  SLOW = 1,
  FAST = 5,
} BULLET_SPEED;

typedef struct Bullet {
  Vector2 position;
  float angle;
  float velocity;
} Bullet;

typedef struct GameObject {
  Texture2D texture;
  Vector2 position;
  Bullet bullets[MAX_BULLETS];
  double last_shot_fired;
  double fire_rate;
  int distance_travelled;
  int width;
  int height;
  int bullet_count;
  GAME_OBJECT_STATUS status;
} GameObject;

typedef struct Enemy {
  ENEMY_TYPE type;
  GameObject gameObject;
} Enemy;

typedef struct PlayBoundary {
  float width;
  float height;
  Vector2 top_left;
  Vector2 bottom_right;
} PlayBoundary;