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

int DrawPlayerDied(GameObject *player) {
  const PlayBoundary boundary = GetPlayBoundary();
  const float width = 200;
  const float height = 200;
  const float x_pos = boundary.top_left.x + (boundary.width / 2) - (width / 2);
  const float y_pos =
      boundary.top_left.y + (boundary.height / 2) - (height / 2);

  if (player->status == INACTIVE) {
    DrawRectangle(x_pos, y_pos, width, height, DARKBLUE);
    DrawText(TextFormat("You Died"), x_pos + 60, y_pos + 100, 18, RED);
  }

  return 0;
}

int DrawStatus(GameObject *player) {
  const PlayBoundary boundary = GetPlayBoundary();
  const float screen_width = GetScreenWidth() - 200;
  const float health_bar_width = 100;
  const float health_bar_height = 20;

  // draw player distance travelled
  DrawText(TextFormat("Distance Travelled: %d", player->distance_travelled),
           screen_width, 40, 18, WHITE);

  // draw player coordinates
  DrawText(TextFormat("Position: \nX: %.0f\nY: %.0f\n", player->position.x,
                      player->position.y),
           screen_width, 60, 18, WHITE);

  // draw score
  DrawText(TextFormat("Score: %d\n", player->score), screen_width, 110, 18,
           WHITE);

  // draw player health
  const int margin = 2;
  const int health_text_x_pos = boundary.top_left.x + 20;
  const int health_text_y_pos =
      boundary.height - (boundary.height * .05f) + margin;

  DrawRectangle(boundary.top_left.x + 10,
                boundary.height - (boundary.height * .05f), health_bar_width,
                health_bar_height, RED);
  DrawRectangle(
      boundary.top_left.x + 10, boundary.height - (boundary.height * .05f),
      (player->health / 100.f) * health_bar_width, health_bar_height, GREEN);
  DrawText(TextFormat("%d / 100", player->health), health_text_x_pos,
           health_text_y_pos, 18, WHITE);

  DrawFPS(10, 20);

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

  DrawPlayerDied(player);

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

    // set bullet to active on fire
    b1.status = ACTIVE;
    b2.status = ACTIVE;

    Fire(player->bullets, &player->bullet_count, b1);
    Fire(player->bullets, &player->bullet_count, b2);

    player->last_shot_fired = GetTime();
  }
  return 0;
}

int CheckPlayerEnemyCollision(GameObject *player, Enemy enemies[]) {
  for (int i = 0; i < ENEMIES_COUNT; i++) {
    Enemy *enemy = &enemies[i];

    // get player rectangle
    const Rectangle playerHitbox = {player->position.x, player->position.y,
                                    player->width, player->height};
    const Rectangle enemyHitbox = {
        enemy->gameObject.position.x, enemy->gameObject.position.y,
        enemy->gameObject.width, enemy->gameObject.height};

    // if player collides with enemy, take 80% damage
    if (CheckCollisionRecs(enemyHitbox, playerHitbox)) {
      player->health -= player->health * .8f;
    }

    // iterate through enemy bullets
    for (int j = 0; j < enemies[i].gameObject.bullet_count; j++) {
      Bullet *bullet = &enemy->gameObject.bullets[j];
      const Rectangle bulletHitbox = {bullet->position.x, bullet->position.y};

      if (CheckCollisionRecs(playerHitbox, bulletHitbox)) {
        // if bullet is not active skip
        if (bullet->status != ACTIVE) {
          continue;
        }

        player->health -= 5;
        bullet->status = INACTIVE;
      }
    }
  }

  return 0;
}

int UpdatePlayer(GameObject *player, Enemy enemies[]) {

  // if player health is < 0, set player to INACTIVE status
  if (player->health <= 0) {
    player->status = INACTIVE;
    return 0;
  }

  // define play boundary
  PlayBoundary boundary = GetPlayBoundary();

  // move player
  UpdatePlayerPosition(player);

  // check player damage against enemies
  CheckPlayerEnemyCollision(player, enemies);

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