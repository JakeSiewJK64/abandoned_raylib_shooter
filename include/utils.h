#include "types.h"

PlayBoundary GetPlayBoundary();

// Define the Clamp function
float Clamp(const float value, const float min, const float max);

int DrawBullets(Bullet bullets[], int *bullet_count, Color color, float radius);

int UpdateBulletPosition(Bullet bullets[], int *bullet_count);

int DespawnBulletOutOfBounds(Bullet bullets[], int *bullet_count,
                             Vector2 top_left, Vector2 bottom_right);

int DrawPlayBoundary();