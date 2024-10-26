#include "../include/test.h"
#include "../include/player.h"
#include <assert.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

int test_player_fire() {

  int bullet_count = 0; // declare total bullet count spawned in the world
  Vector2 bullets[bullet_count]; // declare bullet list
  Vector2 bullet_spawn_position = {10, 20};

  assert(bullets != NULL);

  // fire for 2 times
  Fire(bullets, &bullet_count, bullet_spawn_position);
  assert(bullet_count == 1);

  Fire(bullets, &bullet_count, bullet_spawn_position);
  printf("%d\n", bullet_count);
  assert(bullet_count == 2);

  // assert(bullet_count == 2);

  // iterate through bullet list
  // for (int i = 0; i < bullet_count; i++) {
  //   assert(&bullets[i] != NULL);
  //   assert(bullets[i].x == 10);
  //   assert(bullets[i].y == 20);
  // }

  return 0;
}

int test_runner() {
  printf("\033[0;34mRUNNING UNIT TESTS\033[0m\n");
  test_player_fire();
  printf("\033[0;32mUNIT TESTS PASSED\033[0m\n");
  return 0;
}