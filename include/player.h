#include <raylib.h>

#define PLAYER_SPEED 4.0f

typedef struct GameObject {
  Texture2D texture;
  Vector2 position;
} GameObject;

void UpdatePlayerPosition(GameObject *player);

void Fire(Vector2 *bullets, int *bullet_count, Vector2 bullet_spawn_position);