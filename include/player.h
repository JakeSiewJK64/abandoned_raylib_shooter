#include "../include/types.h"
#include <raylib.h>

PlayBoundary GetPlayBoundary();

void UpdatePlayerPosition(GameObject *player);

/**
 * @brief Draws the player
 *
 * @param player Pointer to the player
 *
 */
int DrawPlayer(GameObject *player);

/**
 * @brief Fires a bullet from the specified position.
 *
 * Adds a new bullet to the bullets array and increments the bullet count.
 *
 * @param bullets Pointer to an array of Vector2 holding bullet positions.
 * @param bullet_count Pointer to the current number of bullets; updated after
 * firing.
 * @param bullet_spawn_position Position where the bullet is spawned.
 *
 * @note Ensure the bullets array has enough space before calling this function.
 */
int Fire(Bullet bullets[], int *bullet_count, Bullet new_bullet);

int DrawBullets(Bullet bullets[], int *bullet_count);

int UpdateBulletPosition(Bullet bullets[], int *bullet_count);

int DespawnBulletOutOfBounds(Bullet bullets[], int *bullet_count,
                             Vector2 top_left, Vector2 bottom_right);

int CheckPlayerWallCollision(GameObject *player, Vector2 top_left,
                             Vector2 bottom_right);

int DetectPlayerFireInput(GameObject *player);