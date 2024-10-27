#include "../include/initializer.h"
#include "../include/player.h"
#include "../include/test.h"
#include <raylib.h>
#include <stddef.h>

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 800

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