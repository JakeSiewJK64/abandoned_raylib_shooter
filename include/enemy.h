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
/**
 * @brief updates the logical aspect of the enemy
 *
 * @param player - player game object. updates the enemies relative to
 * the player
 * @param enemies - array of enemies to update
 */
int UpdateEnemies(GameObject *player, Enemy enemies[]);
