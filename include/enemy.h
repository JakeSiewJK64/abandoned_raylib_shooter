#include "types.h"

/**
 * @brief draws a single enemy. should not contain logic control
 *
 * @param GameObject - game object of the enemy
 *
 */
int DrawEnemy(GameObject *enemy);
/**
 * @brief draws an array of enemies
 *
 * @param GameObject - game object of the enemy
 *
 */
int DrawEnemies(GameObject enemies[], int size);

int UpdateEnemies(GameObject *player, GameObject enemies[]);