#include "../include/enemy.h"
#include "../include/player.h"
#include "../include/utils.h"
#include <math.h>
#include <raylib.h>

int spawnEnemy(Enemy *enemy) {

  const PlayBoundary boundary = GetPlayBoundary();

  // spawn enemy above
  const int x_margin = 100;
  const int start_x_pos = boundary.top_left.x + x_margin;
  const int end_x_pos = x_margin - boundary.top_left.x + boundary.width;
  const int start_y_pos = boundary.top_left.y - 100;
  const int random_x_buffer = GetRandomValue(start_x_pos, end_x_pos);
  const Vector2 spawn_position = {random_x_buffer, start_y_pos};

  // set enemy status to active
  enemy->gameObject.status = ACTIVE;

  // set enemy new position
  enemy->gameObject.position = spawn_position;

  return 0;
}

/**
 * @brief checks if the enemy is beyond x and y axis of play boundary.
 * @note top y axis omitted because enemy spawns above.
 */
bool checkEnemyWithinBoundary(Enemy *enemy) {
  const PlayBoundary boundary = GetPlayBoundary();

  return enemy->gameObject.position.x > boundary.top_left.x &&
         enemy->gameObject.position.x < boundary.bottom_right.x &&
         enemy->gameObject.position.y < boundary.bottom_right.y;
}

int updateBullet(Enemy *enemy) {
  // iterate and draw bullets
  for (int enemy_index = 0; enemy_index < enemy->gameObject.bullet_count;
       enemy_index++) {

    // calculate bullet trajectory
    const float x_angle =
        -cos(enemy->gameObject.bullets[enemy_index].angle) * FAST;
    const float y_angle =
        -sin(enemy->gameObject.bullets[enemy_index].angle) * FAST;

    // add force to bullet
    enemy->gameObject.bullets[enemy_index].position.y += y_angle;
    enemy->gameObject.bullets[enemy_index].position.x += x_angle;
  }

  return 0;
}

int enemyFireBullet(Enemy *enemy, GameObject *player, double current_time) {
  // Calculate angle between enemy and player
  float deltaX = enemy->gameObject.position.x - player->position.x;
  float deltaY = enemy->gameObject.position.y - player->position.y;
  float angle = atan2(deltaY, deltaX); // Angle in radians

  // set bullet information
  Bullet bullet;
  Vector2 start_pos;
  start_pos.x =
      enemy->gameObject.position.x +
      (enemy->gameObject.width * .5f); // define start position of bullet
  start_pos.y =
      enemy->gameObject.position.y +
      (enemy->gameObject.height * .5f); // define start position of bullet
  bullet.position = start_pos;
  bullet.angle = angle;

  // set enemy information after firing a bullet
  enemy->gameObject.bullets[enemy->gameObject.bullet_count] = bullet;
  enemy->gameObject.bullet_count++;                 // increment bullet count
  enemy->gameObject.last_shot_fired = current_time; // set time fired by enemy

  return 0;
}

int updateEnemyPosition(Enemy *enemy) {
  switch (enemy->type) {
  case TURRET:
    // if normal turret, just move straight
    enemy->gameObject.position.y += 2;
    break;
  default:
    break;
  }
  return 0;
}

int checkCollidingPlayerBullet(GameObject *player, Enemy *enemy) {
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
      Rectangle enemy_hitbox = {
          enemy->gameObject.position.x, enemy->gameObject.position.y,
          enemy->gameObject.width, enemy->gameObject.height};

      if (CheckCollisionRecs(bullet_hitbox, enemy_hitbox)) {
        enemy->gameObject.status = INACTIVE;
      }
    }
  }

  return 0;
}

int DrawEnemy(Enemy *enemy) {

  if (IN_DEBUG_MODE) {
    // draw debug hitbox
    DrawRectangle(enemy->gameObject.position.x, enemy->gameObject.position.y,
                  enemy->gameObject.width, enemy->gameObject.height, RED);
  }

  // draw debug bullets spawned by enemy
  DrawText(TextFormat(("Bullets: %d"), enemy->gameObject.bullet_count),
           enemy->gameObject.position.x + 50, enemy->gameObject.position.y, 12,
           WHITE);

  // draw debug enemy coordinates
  DrawText(TextFormat(("x: %.0f, y:%.0f"), enemy->gameObject.position.x,
                      enemy->gameObject.position.y),
           enemy->gameObject.position.x + 50, enemy->gameObject.position.y + 10,
           12, WHITE);

  // draw enemy texture
  DrawTextureEx(enemy->gameObject.texture, enemy->gameObject.position, 0, .2,
                WHITE);

  return 0;
}

int DrawEnemies(Enemy *enemies, int size) {
  PlayBoundary boundary = GetPlayBoundary();
  for (int i = 0; i < size; i++) {

    // if the enemy is not dead, draw enemy
    const bool within_boundary =
        enemies[i].gameObject.position.y > boundary.top_left.y &&
        enemies[i].gameObject.position.y < boundary.bottom_right.y;

    if (enemies[i].gameObject.status == ACTIVE && within_boundary) {
      DrawEnemy(&enemies[i]);
    }

    // Draw bullets
    DrawBullets(enemies[i].gameObject.bullets,
                &enemies[i].gameObject.bullet_count, RED, 5);
  }

  return 0;
}

int UpdateEnemies(GameObject *player, Enemy enemies[]) {
  const double current_time = GetTime();
  const PlayBoundary boundary = GetPlayBoundary();

  // iterate enemies
  for (int i = 0; i < ENEMIES_COUNT; i++) {
    Enemy *enemy = &enemies[i];

    // handle status INACTIVE (dead)
    if (enemy->gameObject.status == INACTIVE) {
      // respawn enemy
      spawnEnemy(enemy);
    }

    if (enemy->gameObject.status == ACTIVE) {
      // if enemy is beyond boundaries set to inactive (dead)
      const bool within_boundary = checkEnemyWithinBoundary(enemy);

      if (!within_boundary) {
        enemy->gameObject.status = INACTIVE;

        // exit loop since there is no need to process further logic
        continue;
      }

      // update position of enemy
      updateEnemyPosition(enemy);

      // fire a bullet at the player
      if (current_time - enemy->gameObject.last_shot_fired >
          enemy->gameObject.fire_rate) {
        enemyFireBullet(enemy, player, current_time);
      }

      // destroy enemy if collide player bullet
      checkCollidingPlayerBullet(player, enemy);
    }

    // update bullets of enemies
    updateBullet(&enemies[i]);

    DespawnBulletOutOfBounds(enemy->gameObject.bullets,
                             &enemy->gameObject.bullet_count, boundary.top_left,
                             boundary.bottom_right);
  }

  return 0;
}