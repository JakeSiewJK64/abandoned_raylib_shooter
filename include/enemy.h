#include "types.h"

/**
 * @brief draws a single enemy. should not contain logic control
 *
 * @param GameObject - game object of the enemy
 *
 */
int DrawEnemy(Enemy *enemy);
/**
 * @brief draws an array of enemies
 *
 * @param GameObject - game object of the enemy
 *
 */
int DrawEnemies(Enemy *enemies, int size);

int UpdateEnemies(GameObject *player, Enemy enemies[]);
