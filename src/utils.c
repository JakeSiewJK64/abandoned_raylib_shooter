#include "../include/utils.h"

int appendBullet(Bullet new_bullet, Bullet bullets[], int *bullet_count) {
  if (*bullet_count < MAX_BULLETS) {
    bullets[*bullet_count] = new_bullet; // set new bullet as last element
    (*bullet_count)++;                   // increment bullets
    return 0;
  }

  return 1; // Indicate failure to add bullet
}

int Fire(Bullet bullets[], int *bullet_count, Bullet new_bullet) {
  appendBullet(new_bullet, bullets, bullet_count);
  return 0;
}

int UpdateBulletPosition(Bullet bullets[], int *bullet_count) {
  for (int i = 0; i < *bullet_count; i++) {
    bullets[i].position.y -= 10;
  }

  return 0;
}

int DrawBullets(Bullet bullets[], int *bullet_count) {
  for (int i = 0; i < *bullet_count; i++) {
    DrawCircleV(bullets[i].position, 5, YELLOW);
  }

  return 0;
}

int DespawnBulletOutOfBounds(Bullet bullets[], int *bullet_count,
                             Vector2 top_left, Vector2 bottom_right) {
  for (int i = 0; i < *bullet_count; i++) {
    Bullet bullet_entity = bullets[i];

    bool beyond_top_right = bullet_entity.position.y < top_left.y ||
                            bullet_entity.position.x < top_left.x;
    bool beyond_bottom_left = bullet_entity.position.y > bottom_right.y ||
                              bullet_entity.position.x > bottom_right.x;

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

int DrawPlayBoundary() {
  // define play boundary
  PlayBoundary boundary = GetPlayBoundary();

  // draw play boundary
  DrawRectangle(boundary.top_left.x, boundary.top_left.y, boundary.width,
                boundary.height, SKYBLUE);

  return 0;
}