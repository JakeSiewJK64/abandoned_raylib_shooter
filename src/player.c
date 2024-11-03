#include "../include/player.h"
#include "../include/utils.h"
#include <raylib.h>

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

int UpdatePlayerPosition(GameObject *player) {

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

  return 0;
}

int DrawStatus(GameObject *player) {
  int screen_width = GetScreenWidth() - 200;

  // draw player distance travelled
  DrawText(TextFormat("Distance Travelled: %d", player->distance_travelled),
           screen_width, 40, 18, WHITE);

  // draw player coordinates
  DrawText(TextFormat("Position: \nX: %.0f\nY: %.0f\n", player->position.x,
                      player->position.y),
           screen_width, 60, 18, WHITE);

  DrawFPS(screen_width, 20);

  return 0;
}

int DrawPlayer(GameObject *player) {
  if (IN_DEBUG_MODE) {
    // debug draw player hitbox
    DrawRectangle(player->position.x, player->position.y, player->width,
                  player->height, RED);
  }

  // render player texture
  DrawTextureEx(player->texture, player->position, 0, .2f, WHITE);

  // Draw player status information
  DrawStatus(player);

  // draw bullet
  DrawBullets(player->bullets, &player->bullet_count, YELLOW, 2.f);

  return 0;
}

int DetectPlayerFireInput(GameObject *player) {
  // only fire if space key down
  const double current_time = GetTime();

  if (IsKeyDown(KEY_SPACE) &&
      current_time - player->last_shot_fired >= player->fire_rate) {

    Vector2 left_cannon = {player->position.x + 20, player->position.y + 40};
    Vector2 right_cannon = {player->position.x + 70, player->position.y + 40};
    Bullet b1 = {left_cannon, 0};
    Bullet b2 = {right_cannon, 0};

    Fire(player->bullets, &player->bullet_count, b1);
    Fire(player->bullets, &player->bullet_count, b2);

    player->last_shot_fired = GetTime();
  }
  return 0;
}

int UpdatePlayer(GameObject *player) {

  // define play boundary
  PlayBoundary boundary = GetPlayBoundary();

  // move player
  UpdatePlayerPosition(player);

  // detect player wall collision
  CheckPlayerWallCollision(player, boundary.top_left, boundary.bottom_right);

  // update player bullet
  UpdateBulletPosition(player->bullets, &player->bullet_count);

  // check and despawn bullet out of bounds
  DespawnBulletOutOfBounds(player->bullets, &player->bullet_count,
                           boundary.top_left, boundary.bottom_right);

  // detect player fire input
  DetectPlayerFireInput(player);
  return 0;
}