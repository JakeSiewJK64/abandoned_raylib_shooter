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
int RunGame(GameObject *player) {

  // define play boundary
  PlayBoundary boundary = GetPlayBoundary();

  // draw play boundary
  DrawRectangle(boundary.top_left.x, boundary.top_left.y, boundary.width,
                boundary.height, SKYBLUE);

  // move player
  UpdatePlayerPosition(player);

  // detect player wall collision
  CheckPlayerWallCollision(player, boundary.top_left, boundary.bottom_right);

  // increment player distance travelled
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

    Fire(player->bullets, &player->bullet_count, left_cannon);
    Fire(player->bullets, &player->bullet_count, right_cannon);

    player->last_shot_fired = GetTime();
  }

  DrawBullets(player->bullets, &player->bullet_count);
  UpdateBulletPosition(player->bullets, &player->bullet_count);
  DespawnBulletOutOfBounds(player->bullets, &player->bullet_count,
                           boundary.top_left, boundary.bottom_right);

  EndDrawing();
  return 0;
}

int main() {

  // run unit tests
  test_runner();

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

  // main game loop
  while (!WindowShouldClose()) {
    RunGame(&player);
  }

  return 0;
}