#include "../include/player.h"
#include <raylib.h>

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

int DrawPlayer(GameObject *player) {
  DrawTextureEx(player->texture, player->position, 0, .2f, WHITE);
  return 0;
}

int appendBullet(Vector2 new_bullet, Vector2 *bullets, int *bullet_count) {
  if (*bullet_count < MAX_BULLETS) {
    bullets[*bullet_count] = new_bullet; // set new bullet as last element
    (*bullet_count)++;                   // increment bullets
    return 0;
  }

  return 1; // Indicate failure to add bullet
}

void Fire(Vector2 *bullets, int *bullet_count, Vector2 bullet_spawn_position) {
  appendBullet(bullet_spawn_position, bullets, bullet_count);
}

int UpdateBulletPosition(Vector2 *bullets, int *bullet_count) {
  for (int i = 0; i < *bullet_count; i++) {
    bullets[i].y -= 10;
  }

  return 0;
}

int DrawBullets(Vector2 *bullets, int *bullet_count) {
  for (int i = 0; i < *bullet_count; i++) {
    DrawCircleV(bullets[i], 5, YELLOW);
  }

  return 0;
}