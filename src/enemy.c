#include "../include/enemy.h"

int DrawEnemy(GameObject *enemy) {
  // draw debug hitbox
  DrawRectangle(enemy->position.x, enemy->position.y, enemy->width,
                enemy->height, RED);

  // draw enemy texture if active
  DrawTextureEx(enemy->texture, enemy->position, 0, .2, WHITE);

  return 0;
}

int UpdateEnemies(GameObject *player, GameObject enemies[]) {
  // iterate and draw enemies
  for (int i = 0; i < ENEMIES_COUNT; i++) {
    GameObject *enemy = &enemies[i];

    if (enemy->status == ACTIVE) {

      // Draw enemy
      DrawEnemy(enemy);

      // Check if collide with bullet
      if (player->bullet_count > 0) {
        for (int player_bullet_index = 0;
             player_bullet_index < player->bullet_count;
             player_bullet_index++) {

          // get bullet position
          Vector2 player_bullet_position = player->bullets[player_bullet_index];

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
    }
  }

  return 0;
}