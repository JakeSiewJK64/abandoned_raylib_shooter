#include "../include/enemy.h"
#include "../include/initializer.h"
#include "../include/player.h"
#include "../include/test.h"
#include "../include/utils.h"
#include <raylib.h>
#include <stddef.h>

// render game graphics
int Draw(GameObject *player, Enemy enemies[]) {
  BeginDrawing();

  // draw play boundary
  DrawPlayBoundary();

  // refresh the background
  ClearBackground(BLACK);

  // draw the enemies
  DrawEnemies(enemies, ENEMIES_COUNT);

  // draw the player
  DrawPlayer(player);

  EndDrawing();

  return 0;
}

// update game logic
int RunGame(GameObject *player, Enemy enemies[]) {

  // update player logic each frame
  UpdatePlayer(player, enemies);

  UpdateEnemies(player, enemies);

  // Render the graphics
  Draw(player, enemies);
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
  player.score = 0;
  player.bullet_count = 0;
  player.health = 100;

  // initialize enemies
  Enemy enemies[ENEMIES_COUNT];
  Texture2D turret_texture = LoadTexture("assets/turret.png");

  for (int i = 0; i < ENEMIES_COUNT; i++) {
    int buffer = 30;
    enemies[i].gameObject.texture = turret_texture;
    enemies[i].gameObject.width = 38;
    enemies[i].gameObject.height = 38;
    enemies[i].gameObject.status = INACTIVE;
    enemies[i].gameObject.bullet_count = 0;
    enemies[i].gameObject.last_shot_fired = -1;
    enemies[i].gameObject.fire_rate = .7f;
    enemies[i].gameObject.health = 100;
    enemies[i].points = 100;
    enemies[i].type = TURRET;
  }

  // main game loop
  while (!WindowShouldClose()) {
    RunGame(&player, enemies);
  }

  return 0;
}