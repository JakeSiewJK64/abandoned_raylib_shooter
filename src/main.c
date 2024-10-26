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

  // move player
  UpdatePlayerPosition(player);

  BeginDrawing();
  ClearBackground(BLACK);

  // draw the plane
  DrawPlayer(player);

  // only fire if space key down
  if (IsKeyDown(KEY_SPACE)) {
    Vector2 left_cannon = {player->position.x + 20, player->position.y + 40};
    Vector2 right_cannon = {player->position.x + 70, player->position.y + 40};

    Fire(bullets, bullet_count, left_cannon);
    Fire(bullets, bullet_count, right_cannon);
  }

  DrawBullets(bullets, bullet_count);
  UpdateBulletPosition(bullets, bullet_count);
  DespawnBulletOutOfBounds(bullets, bullet_count, SCREEN_WIDTH, SCREEN_HEIGHT);

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
  int bullet_count = 0;  // declare total bullet count spawned in the world
  Vector2 bullets[MAX_BULLETS]; // declare bullet list with a fixed size

  // initialize player
  Vector2 vector = {SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - (.2f * SCREEN_WIDTH)};
  GameObject player;
  player.texture = plane;
  player.position = vector;

  // main game loop
  while (!WindowShouldClose()) {
    printf("total bullets in the world: %d\n", bullet_count);
    RunGame(&player, bullets, &bullet_count);
  }

  return 0;
}