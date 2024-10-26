#include "../include/initializer.h"
#include "../include/player.h"
#include "../include/test.h"
#include <raylib.h>
#include <stddef.h>

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 800
#define INITIAL_BULLET_CAPACITY 1
#define MAX_BULLETS 1000

// game renderer
int RunGame(GameObject *player, Vector2 *bullets, int *bullet_count) {

  // move player
  UpdatePlayerPosition(player);

  BeginDrawing();
  ClearBackground(BLACK);

  // draw the plane
  DrawPlayer(player);

  Fire(bullets, bullet_count, player->position);
  DrawBullets(bullets, bullet_count);
  UpdateBulletPosition(bullets, bullet_count);

  EndDrawing();
  return 0;
}

int main() {

  // run unit tests
  test_runner();

  // initialize game configuration
  InitializeConfigurations(SCREEN_WIDTH, SCREEN_HEIGHT);
  float screen_width = GetScreenWidth();
  float screen_height = GetScreenHeight();

  // initialize assets
  Texture2D plane = LoadTexture("assets/plane.png");

  // initialize bullet
  int bullet_count = 0;  // declare total bullet count spawned in the world
  Vector2 bullets[1000]; // declare bullet list with a fixed size

  // initialize player
  Vector2 vector = {screen_width / 2, screen_height - (.2f * screen_width)};
  GameObject player;
  player.texture = plane;
  player.position = vector;

  // main game loop
  while (!WindowShouldClose()) {
    RunGame(&player, bullets, &bullet_count);
  }

  return 0;
}