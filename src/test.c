#include "../include/test.h"
#include "../include/player.h"
#include <assert.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

int test_player_fire() {

  int fire_frequency = 10;
  int bullet_count = 0;  // declare total bullet count spawned in the world
  Vector2 bullets[1000]; // declare bullet list with a fixed size
  Vector2 bullet_spawn_position = {10, 20};

  // TEST: bullet entity spawned successfully
  assert(bullets != NULL);

  // Fire for 10 times
  for (int i = 0; i < fire_frequency; i++) {
    Fire(bullets, &bullet_count, bullet_spawn_position);
  }

  assert(bullet_count == fire_frequency);

  for (int i = 0; i < bullet_count; i++) {
    assert(&bullets[i] != NULL);
    assert(bullets[i].x == 10);
    assert(bullets[i].y == 20);
  }

  // TEST: bullet travel
  int original_y_coord = bullets[0].y;

  UpdateBulletPosition(bullets, &bullet_count);

  for (int i = 0; i < fire_frequency; i++) {
    assert(bullets[i].y != original_y_coord);
  }

  // TEST: despawn bullets out of bounds
  int y_coords = 0;
  int y_limit = 100;
  Vector2 start_pos = {10, 0};

  Fire(bullets, &bullet_count, start_pos);

  while (y_coords <= y_limit) {
    if (y_coords == y_limit) {
      printf("bullet did not despawn beyond boundary.\n");
      exit(1);
    }

    if (bullet_count == fire_frequency) {
      break;
    }

    UpdateBulletPosition(bullets, &bullet_count);
    DespawnBulletOutOfBounds(bullets, &bullet_count, 100, y_limit);

    y_coords++;
  }

  return 0;
}

int test_runner() {
  printf("\033[0;34mRUNNING UNIT TESTS\033[0m\n");
  test_player_fire();
  printf("\033[0;32mUNIT TESTS PASSED\033[0m\n");
  return 0;
}