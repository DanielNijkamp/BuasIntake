#include "Game.h"

//NOTES:
/* =================================== Design choices ===================================
 * 
 * I designed my classes to allow them to retrieve their dependencies from the main.
 * We initialize all dependencies and all classes directly inside the main.
 * All classes are designed to be left alone after creation, most values passed are immutable.
 * This approach saves us from having to deal with memory management/creating and deleting objects.
 * This is most definitely not recommended with bigger project only for small project like this one.
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
 * CollisionSystem.cpp
 */

//TODO: check release compilation LNKR errors.


int main()
{
    Game game(500, 800);

    while (game.shouldRun)
    {
        game.Run();
    }
    return 0;
}



