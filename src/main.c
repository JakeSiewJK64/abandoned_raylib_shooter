#include "../include/enemy.h"
#include "../include/initializer.h"
#include "../include/player.h"
#include "../include/test.h"
#include "../include/utils.h"
#include <raylib.h>
#include <stddef.h>

// game renderer
int RunGame(GameObject *player, GameObject enemies[]) {

  // define play boundary
  PlayBoundary boundary = GetPlayBoundary();

  // draw play boundary
  DrawRectangle(boundary.top_left.x, boundary.top_left.y, boundary.width,
                boundary.height, SKYBLUE);

  // move player
  UpdatePlayerPosition(player);

  // detect player wall collision
  CheckPlayerWallCollision(player, boundary.top_left, boundary.bottom_right);

  BeginDrawing();
  ClearBackground(BLACK);

  // update enemies
  UpdateEnemies(player, enemies);

  // draw the plane
  DrawPlayer(player);

  // detect player fire input
  DetectPlayerFireInput(player);

  DrawBullets(player->bullets, &player->bullet_count);
  UpdateBulletPosition(player->bullets, &player->bullet_count);
  DespawnBulletOutOfBounds(player->bullets, &player->bullet_count,
                           boundary.top_left, boundary.bottom_right);

  EndDrawing();
  return 0;
}

int main() {

  // run unit tests
  if (IN_TEST_MODE) {
    test_runner();
    return 0;
  }

  // initialize game configuration
  InitializeConfigurations(SCREEN_WIDTH, SCREEN_HEIGHT);

  // initialize player
  Texture2D plane = LoadTexture("assets/plane.png");
  PlayBoundary boundary = GetPlayBoundary();
  Vector2 vector = {boundary.width / 2.f, boundary.height - 100};
  GameObject player;
  player.texture = plane;
  player.position = vector;
  player.distance_travelled = 0;
  player.last_shot_fired = -1;
  player.fire_rate = .2f;
  player.height = 110;
  player.width = 95;
  player.bullet_count = 0;

  // initialize enemies
  GameObject enemies[ENEMIES_COUNT];
  Texture2D turret_texture = LoadTexture("assets/turret.png");

  for (int i = 0; i < ENEMIES_COUNT; i++) {
    int buffer = 30;
    int x_pos = boundary.top_left.x + 200 + (i * buffer);
    int y_pos = 200 + (i * buffer);
    enemies[i].texture = turret_texture;

    Vector2 turret_vector = {x_pos, y_pos};
    enemies[i].position = turret_vector;
    enemies[i].width = 38;
    enemies[i].height = 38;
    enemies[i].status = ACTIVE;
    enemies[i].bullet_count = 0;
    enemies[i].last_shot_fired = -1;
    enemies[i].fire_rate = .7f;
  }

  // main game loop
  while (!WindowShouldClose()) {
    RunGame(&player, enemies);
  }

  return 0;
}