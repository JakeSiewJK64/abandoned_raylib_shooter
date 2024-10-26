#include "../include/player.h"
#include <raylib.h>
#include <stdio.h>

void UpdatePlayerPosition(GameObject *player) {
  if (IsKeyDown(KEY_D)) {
    player->position.x += PLAYER_SPEED;
  }
  if (IsKeyDown(KEY_A)) {
    player->position.x -= PLAYER_SPEED;
  }
  if (IsKeyDown(KEY_W)) {
    player->position.y -= PLAYER_SPEED;
  }
  if (IsKeyDown(KEY_S)) {
    player->position.y += PLAYER_SPEED;
  }
}

int appendBullet(Vector2 new_bullet, Vector2 *bullets, int *bullet_count,
                 int MAX_BULLETS) {
  if (*bullet_count < MAX_BULLETS) {
    bullets[*bullet_count] = new_bullet; // set new bullet as last element
    (*bullet_count)++;                   // increment bullets
    return 0;
  }

  return 1; // Indicate failure to add bullet
}

void Fire(Vector2 *bullets, int *bullet_count, Vector2 bullet_spawn_position) {
  appendBullet(bullet_spawn_position, bullets, bullet_count, 1000);
}