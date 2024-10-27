#include "../include/player.h"
#include <raylib.h>

PlayBoundary GetPlayBoundary() {
  // define play boundary
  const float screen_width = GetScreenWidth();
  const float screen_height = GetScreenHeight();
  const float play_area_width = screen_width * .6f;
  const float play_area_height = screen_height * .8f;
  const float rectX = screen_width / 2 - play_area_width / 2;
  const float rectY = screen_height / 2 - play_area_height / 2;
  const Vector2 top_left = {rectX, rectY};
  const Vector2 bottom_right = {rectX + play_area_width,
                                rectY + play_area_height};

  const PlayBoundary boundary = {play_area_width, play_area_height, top_left,
                                 bottom_right};

  return boundary;
}

// Define the Clamp function
float Clamp(const float value, const float min, const float max) {
  if (value < min) {
    return min;
  }

  if (value > max) {
    return max;
  }

  return value;
}

int CheckPlayerWallCollision(GameObject *player, const Vector2 top_left,
                             const Vector2 bottom_right) {

  // Clamp the player's position within the bounds,
  // considering player's dimensions
  const float clamped_x =
      Clamp(player->position.x, top_left.x, bottom_right.x - player->width);
  const float clamped_y =
      Clamp(player->position.y, top_left.y, bottom_right.y - player->height);

  // Update player position if clamped
  player->position.x = clamped_x;
  player->position.y = clamped_y;

  return 0;
}

void UpdatePlayerPosition(GameObject *player) {

  // increment player distance travelled
  player->distance_travelled++;

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
  // debug draw player hitbox
  DrawRectangle(player->position.x, player->position.y, player->width,
                player->height, RED);

  DrawTextureEx(player->texture, player->position, 0, .2f, WHITE);

  int screen_width = GetScreenWidth() - 200;

  // draw player distance travelled
  DrawText(TextFormat("Distance Travelled: %d", player->distance_travelled),
           screen_width, 40, 18, WHITE);

  // draw player coordinates
  DrawText(TextFormat("Position: \nX: %.0f\nY: %.0f\n", player->position.x,
                      player->position.y),
           screen_width, 60, 18, WHITE);

  return 0;
}

int DetectPlayerFireInput(GameObject *player) {
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