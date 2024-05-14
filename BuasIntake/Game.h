#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

#include "Collision/Screenbounds.h"
#include "Systems/Input.h"
#include "Systems/SpriteLoader.h"

/* Instead of initializing our entire game inside the main
 * We create it inside a method in this class. where we can recreate our entire game multiple times
 * We also re-use the same window created inside the ctor.
 * Since all objects in our game are designed to be created and destroyed at the same time we simply create the game agian.
 * Any persistent systems should live outside the run method.
 */

class Game final
{
public:
    explicit Game(unsigned int windowWidth, unsigned int windowHeight);
    
    void Run();

    bool shouldRun = true;
private:
    sf::RenderWindow window;
    Screenbounds screenbounds;
};
