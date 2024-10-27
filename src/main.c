#include "../include/initializer.h"
#include "../include/player.h"
#include "../include/test.h"
#include <raylib.h>
#include <stddef.h>
#include <stdio.h>

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 800
#define INITIAL_BULLET_CAPACITY 1
#define MAX_BULLETS 1000

// game renderer
int RunGame(GameObject *player, Vector2 *bullets, int *bullet_count) {

  // define play boundary
  const int screenWidth = GetScreenWidth();
  const int screenHeight = GetScreenHeight();
  const int rectWidth = screenWidth * .5;   // 50% of screen width
  const int rectHeight = screenHeight * .8; // 80% of screen height
  const int rectX = screenWidth / 2 - rectWidth / 2;
  const int rectY = screenHeight / 2 - rectHeight / 2;

  Vector2 top_left = {rectX, rectY};
  Vector2 bottom_right = {rectX + rectWidth, rectY + rectHeight};

  // draw play boundary
  DrawRectangle(rectX, rectY, rectWidth, rectHeight, SKYBLUE);

  // move player
  UpdatePlayerPosition(player);
  player->distance_travelled++;

  BeginDrawing();
  ClearBackground(BLACK);

  // draw the plane
  DrawPlayer(player);

  // only fire if space key down
  const double current_time = GetTime();

  if (IsKeyDown(KEY_SPACE) &&
      current_time - player->last_shot_fired >= player->fire_rate) {

    Vector2 left_cannon = {player->position.x + 20, player->position.y + 40};
    Vector2 right_cannon = {player->position.x + 70, player->position.y + 40};

    Fire(bullets, bullet_count, left_cannon);
    Fire(bullets, bullet_count, right_cannon);

    player->last_shot_fired = GetTime();
  }

  DrawBullets(bullets, bullet_count);
  UpdateBulletPosition(bullets, bullet_count);
  DespawnBulletOutOfBounds(bullets, bullet_count, top_left, bottom_right);

  EndDrawing();
  return 0;
}

int main() {

  // run unit tests
  test_runner();

  // initialize game configuration
  InitializeConfigurations(SCREEN_WIDTH, SCREEN_HEIGHT);

  // initialize assets
  Texture2D plane = LoadTexture("assets/plane.png");

  // initialize bullet
  int bullet_count = 0; // declare total bullet count spawned in the world
  Vector2 bullets[MAX_BULLETS]; // declare bullet list with a fixed size

  // initialize player
  Vector2 vector = {SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - (.2f * SCREEN_WIDTH)};
  GameObject player;
  player.texture = plane;
  player.position = vector;
  player.distance_travelled = 0;
  player.last_shot_fired = -1;
  player.fire_rate = .2f;

  // main game loop
  while (!WindowShouldClose()) {
    printf("total bullets in the world: %d\n", bullet_count);
    RunGame(&player, bullets, &bullet_count);
  }

  return 0;
}