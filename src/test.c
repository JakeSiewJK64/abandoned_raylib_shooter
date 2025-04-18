#include "../include/test.h"
#include "../include/player.h"
#include "../include/utils.h"
#include <assert.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#define COLOR_BOLD "\e[1m"
#define COLOR_BOLD_OFF "\e[m"

int log_test_title(char *title) {
  printf("TEST: %s", title);
  return 0;
}

int assert_passed() {
  printf(" --- ");
  printf(COLOR_BOLD "\033[42;30m%s\033[0m", " PASSED " COLOR_BOLD_OFF);
  printf(" ✓\n");
  return 0;
}

int test_player_fire() {

  int fire_frequency = 10;
  int bullet_count = 0; // declare total bullet count spawned in the world
  Bullet bullets[1000]; // declare bullet list with a fixed size
  Bullet bullet_spawn_position = {10, 20};

  // TEST: bullet entity spawned successfully
  log_test_title("bullet entity spawned successfully");
  
  assert(bullets != NULL);

  // Fire for 10 times
  for (int i = 0; i < fire_frequency; i++) {
    Fire(bullets, &bullet_count, bullet_spawn_position);
  }

  assert(bullet_count == fire_frequency);

  for (int i = 0; i < bullet_count; i++) {
    assert(&bullets[i] != NULL);
    assert(bullets[i].position.x == 10);
    assert(bullets[i].position.y == 20);
  }

  assert_passed();
  // TEST: bullet travel
  log_test_title("bullet travel");

  int original_y_coord = bullets[0].position.y;

  UpdateBulletPosition(bullets, &bullet_count);

  for (int i = 0; i < fire_frequency; i++) {
    assert(bullets[i].position.y != original_y_coord);
  }

  assert_passed();
  // TEST: despawn bullets out of bounds
  log_test_title("despawn bullets out of bounds.");
  int y_coords = 0;
  int y_limit = 100;
  Vector2 start_pos = {10, 0};
  Bullet bullet = {start_pos, 0};

  Fire(bullets, &bullet_count, bullet);

  while (y_coords <= y_limit) {
    if (y_coords == y_limit) {
      printf("bullet did not despawn beyond boundary.\n");
      exit(1);
    }

    if (bullet_count == fire_frequency) {
      break;
    }

    UpdateBulletPosition(bullets, &bullet_count);

    // define top left and bottom right coordinates
    Vector2 top_left = {0, 0};
    Vector2 bottom_right = {100, 100};

    DespawnBulletOutOfBounds(bullets, &bullet_count, top_left, bottom_right);

    y_coords++;
  }
  assert_passed();

  return 0;
}

int test_runner() {
  printf("\033[0;34mRUNNING UNIT TESTS\033[0m\n");
  test_player_fire();
  printf("\033[0;32mUNIT TESTS PASSED\033[0m\n");
  return 0;
}