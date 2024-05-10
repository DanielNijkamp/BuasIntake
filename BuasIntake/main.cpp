#include "Game.h"

//NOTES:
/* =================================== Design choices ===================================
 * 
 * I designed my classes to allow them to retrieve their dependencies from the main.
 * We initialize all dependencies and all classes directly inside the main.
 * All classes are designed to be left alone after creation, most values passed are immutable.
 * This approach saves us from having to deal with memory management/creating and deleting objects.
 * In this way i kind of cheated by not having to deal with some annoying parts.
 *
 * Some classes use a reference to a float to write or read to it which is also initialized inside the main
 * Game loop stuff like checking when the player is dead is signaled to other classes via custom event class.
 *
 * For small project like this ECS and Game Object pattern might be unnecessary so composition is used.
 * for larger projects one of the two would be useful to implement.
 */

/* =================================== Class notes ===================================
 * Renderable.h
 * Player.h
 * Input.h
 * Transformable.h
 * Game.h
 */

/*TODO:
 *REFACTORING:
       Fix that everything freezes when losing including player.
 *     check release compilation LNKR errors.
 * =======================================================================================
 *GAMEPLAY:
 *
 *
 *    
 *     Drunkenness UI
 *     Lose + Win UI.
 *     Movement progression UI. 0 to 100km for example?
*/

int main()
{
    Game game(500, 800);
    game.Run();

    game.Run();
    return 0;
}



