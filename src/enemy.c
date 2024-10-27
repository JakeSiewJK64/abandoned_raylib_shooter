#include "../include/enemy.h"
#include "../include/player.h"
#include <math.h>
#include <raylib.h>

int DrawEnemy(GameObject *enemy) {

  if (IN_DEBUG_MODE) {
    // draw debug hitbox
    DrawRectangle(enemy->position.x, enemy->position.y, enemy->width,
                  enemy->height, RED);
  }

  DrawText(TextFormat(("Bullets: %d"), enemy->bullet_count),
           enemy->position.x + 50, enemy->position.y, 12, WHITE);

  // draw enemy texture if active
  DrawTextureEx(enemy->texture, enemy->position, 0, .2, WHITE);

  return 0;
}

int updateBullet(GameObject *enemy) {
  // iterate and draw bullets
  for (int b = 0; b < enemy->bullet_count; b++) {

    // calculate bullet trajectory
    const float x_angle = -cos(enemy->bullets[b].angle) * FAST;
    const float y_angle = -sin(enemy->bullets[b].angle) * FAST;

    // add force to bullet
    enemy->bullets[b].position.y += y_angle;
    enemy->bullets[b].position.x += x_angle;

    DrawCircle(enemy->bullets[b].position.x, enemy->bullets[b].position.y, 12,
               RED);
  }

  return 0;
}

int enemyFireBullet(GameObject *enemy, GameObject *player,
                    double current_time) {
  // Calculate angle between enemy and player
  float deltaX = enemy->position.x - player->position.x;
  float deltaY = enemy->position.y - player->position.y;
  float angle = atan2(deltaY, deltaX); // Angle in radians

  // set bullet information
  Bullet bullet;
  Vector2 start_pos;
  start_pos.x = enemy->position.x +
                (enemy->width * .5f); // define start position of bullet
  start_pos.y = enemy->position.y +
                (enemy->height * .5f); // define start position of bullet
  bullet.position = start_pos;
  bullet.angle = angle;

  // set enemy information after firing a bullet
  enemy->bullets[enemy->bullet_count] = bullet;
  enemy->bullet_count++;                 // increment bullet count
  enemy->last_shot_fired = current_time; // set time fired by enemy

  return 0;
}

int checkCollidingPlayerBullet(GameObject *player, GameObject *enemy) {
  // Check if collide with bullet
  if (player->bullet_count > 0) {
    for (int player_bullet_index = 0;
         player_bullet_index < player->bullet_count; player_bullet_index++) {

      // get bullet position
      Vector2 player_bullet_position =
          player->bullets[player_bullet_index].position;

      // get bullet hitbox
      Rectangle bullet_hitbox = {player_bullet_position.x,
                                 player_bullet_position.y, 10, 10};

      // get bullet hitbox
      Rectangle enemy_hitbox = {enemy->position.x, enemy->position.y,
                                enemy->width, enemy->height};

      if (CheckCollisionRecs(bullet_hitbox, enemy_hitbox)) {
        enemy->status = INACTIVE;
      }
    }
  }

  return 0;
}

int UpdateEnemies(GameObject *player, GameObject enemies[]) {
  const double current_time = GetTime();
  PlayBoundary boundary = GetPlayBoundary();

  // iterate enemies
  for (int i = 0; i < ENEMIES_COUNT; i++) {
    GameObject *enemy = &enemies[i];

    if (enemy->status == ACTIVE) {

      // Draw enemy
      DrawEnemy(enemy);

      // fire a bullet at the player
      if (current_time - enemy->last_shot_fired > enemy->fire_rate) {
        enemyFireBullet(enemy, player, current_time);
      }

      // destroy enemy if collide player bullet
      checkCollidingPlayerBullet(player, enemy);
    }

    // iterate and draw bullet
    updateBullet(enemy);

    DespawnBulletOutOfBounds(enemy->bullets, &enemy->bullet_count,
                             boundary.top_left, boundary.bottom_right);
  }

  return 0;
}