#include <raylib.h>

#define PLAYER_SPEED 4.0f
#define MAX_BULLETS 1000

typedef struct GameObject {
  Texture2D texture;
  Vector2 position;
  int distance_travelled;
} GameObject;

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
void Fire(Vector2 *bullets, int *bullet_count, Vector2 bullet_spawn_position);

int DrawBullets(Vector2 *bullets, int *bullet_count);

int UpdateBulletPosition(Vector2 *bullets, int *bullet_count);

int DespawnBulletOutOfBounds(Vector2 *bullets, int *bullet_count,
                             int x_boundary, int y_boundary);