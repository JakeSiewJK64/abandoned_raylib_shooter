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

  int screen_width = GetScreenWidth() - 200;

  // draw player distance travelled
  DrawText(TextFormat("Distance Travelled: %d", player->distance_travelled),
           screen_width, 40, 12, WHITE);

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

int DespawnBulletOutOfBounds(Vector2 *bullets, int *bullet_count,
                             Vector2 top_left, Vector2 bottom_right) {
  for (int i = 0; i < *bullet_count; i++) {
    Vector2 bullet_entity = bullets[i];
    bool beyond_top_right =
        bullet_entity.y < top_left.y || bullet_entity.x < top_left.x;
    bool beyond_bottom_left =
        bullet_entity.y > bottom_right.y || bullet_entity.x > bottom_right.x;

    if (beyond_top_right || beyond_bottom_left) {
      // Shift bullets down to overwrite the "despawned" bullet
      for (int j = i; j < *bullet_count - 1; j++) {
        bullets[j] = bullets[j + 1];
      }

      (*bullet_count)--; // decrement bullet count
      i--; // stay at the current index since we shifted elements down
    }
  }

  return 0;
}