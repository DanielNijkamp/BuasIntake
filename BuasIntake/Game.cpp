#include "Game.h"

#include <iostream>
#include <memory>

#include "Player.h"
#include "BehaviourSystems/CollisionSystem.h"
#include "BehaviourSystems/FixedUpdateSystem.h"
#include "BehaviourSystems/RenderSystem.h"
#include "Objects/Barrier.h"
#include "Objects/Road/RoadSystem.h"
#include "Objects/Spawners/Bottle/Bottle.h"
#include "Objects/Spawners/Bottle/BottleSpawner.h"
#include "Objects/Spawners/Car/CarSpawner.h"
#include "Systems/Input.h"
#include "Systems/SpriteLoader.h"

Game::Game(unsigned int windowWidth, unsigned int windowHeight) :
    window(sf::VideoMode(windowWidth, windowHeight), "Fun Driving Sim",
           sf::Style::Close),
    screenbounds(windowWidth,windowHeight)
{
    window.setFramerateLimit(60); //TODO: check if uncapping doesnt break systems

    if (!window.isOpen())
    {
        std::cerr << "Failed to create window!" << '\n';
        throw std::runtime_error("Failed to create window!");
    }
}

void Game::Run()
{
#pragma region Init
    srand(static_cast<unsigned>(time(nullptr)));
    
    SpriteLoader spriteLoader("./Assets/"); 
    Input input;
    
#pragma endregion Init

#pragma region ScrollSystem
    
    bool canScroll = true; //binding bool that toggles all scroll systems.
    
    float acceleration;
    
    float offset = 400;
    
    sf::Vector2f storePos(-1500, -1500);
    
    sf::Vector2f startPos(screenbounds.width / 2, -offset);
    sf::Vector2f endPos(screenbounds.width / 2, screenbounds.height + offset);

#pragma endregion ScrollSystem

#pragma region Player
    
    auto carSprite = spriteLoader.LoadSprite("PlayerCar.png");
    
    auto player = std::make_shared<Player>(carSprite, input,
        sf::Vector2f(screenbounds.width / 2, 600),
        acceleration, 500, 1500, 100, 60,
        50,0,100,
        6, 5, 1);

    player->onSober.Subscribe( [&]
    {
        std::cout << "Is Sober" << '\n';
        canScroll = false;
    });

#pragma endregion Player

#pragma region Barrier
    
    auto leftBarrierSprite = spriteLoader.LoadSprite("Barrier.png");
    auto rightBarrierSprite = spriteLoader.LoadSprite("Barrier.png");

    sf::Vector2f leftBarrierPosition(0, ((screenbounds.height - leftBarrierSprite.getTextureRect().getSize().y) / 2.f) - 150);
    sf::Vector2f rightBarrierPosition((screenbounds.width - rightBarrierSprite.getTextureRect().getSize().x) - 10,
                                      ((screenbounds.height - rightBarrierSprite.getTextureRect().getSize().y) / 2.f) - 150);

    auto scale = sf::Vector2f(2,3);
    auto leftBarrier = std::make_shared<Barrier>(leftBarrierSprite, leftBarrierPosition, scale);
    auto rightBarrier = std::make_shared<Barrier>(rightBarrierSprite, rightBarrierPosition, scale);

#pragma endregion Barrier

#pragma region RoadSystem
    
    const auto roadSprite = spriteLoader.LoadSprite("Road.png");

    auto road1 = std::make_shared<Road>(roadSprite);
    auto road2 = std::make_shared<Road>(roadSprite);
    auto road3 = std::make_shared<Road>(roadSprite);
    
    sf::Vector2f halfwayPoint(screenbounds.width / 2, screenbounds.height / 2);
    
    road1->UpdatePositions(endPos);
    road2->UpdatePositions(storePos);
    road3->UpdatePositions(storePos);
    
    auto roadSystem = std::make_shared<RoadSystem>(canScroll,acceleration,startPos, endPos, storePos, halfwayPoint);
    roadSystem->AddActive({road1});
    roadSystem->AddInactive({road2, road3});

#pragma endregion Road

#pragma region Carspawner
    
    auto carSpawner = std::make_shared<CarSpawner>(screenbounds,canScroll,acceleration, startPos, endPos, storePos, 35, 1, 4);

    auto car1 = std::make_shared<Car>(storePos,spriteLoader.LoadSprite("car (1).png"));
    auto car2 = std::make_shared<Car>(storePos,spriteLoader.LoadSprite("car (2).png"));
    auto car3 = std::make_shared<Car>(storePos,spriteLoader.LoadSprite("car (3).png"));
    
    carSpawner->AddInactive({car1,car2, car3});
    carSpawner->onCollision.Subscribe([&]
    {
        std::cout << "Bro lost the game L + ratio" << '\n';
        canScroll = false;
    });

#pragma endregion Carspawner

#pragma region BottleSpawner

    auto bottleSpawner = std::make_shared<BottleSpawner>(screenbounds, canScroll, acceleration, startPos, endPos, storePos, 250, 1, 4, 45, 85);
    
    auto bottle1 = std::make_shared<Bottle>(storePos,spriteLoader.LoadSprite("bottle.png"));
    auto bottle2 = std::make_shared<Bottle>(storePos,spriteLoader.LoadSprite("bottle.png"));
    auto bottle3 = std::make_shared<Bottle>(storePos,spriteLoader.LoadSprite("bottle.png"));

    bottleSpawner->AddInactive({bottle1, bottle2, bottle3});
    bottleSpawner->onPickUp.Subscribe( [&](float strength)
    {
        player->AddDrunkenness(strength);
    });

#pragma endregion BottleSpawner

#pragma region Systems

    //initialize all systems with the necessary objects to iterate on
    
    const RenderSystem renderSystem({road1, road2, road3, player, leftBarrier, rightBarrier, car1, car2, car3, bottle1, bottle2, bottle3});
    const FixedUpdateSystem fixedUpdateSystem({roadSystem, carSpawner, bottleSpawner, player});
    const CollisionSystem collisionSystem({leftBarrier, rightBarrier, car1, car2, car3, bottle1, bottle2, bottle3},screenbounds, player);

#pragma endregion Game

#pragma region GameLoop

    sf::Clock clock;
    
    while (window.isOpen()){

        sf::Time elapsed = clock.restart();
        float deltaTime = elapsed.asSeconds();
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete))
            {
                return;
            }
            
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::GainedFocus:
                input.canProcessInputs = true;
                break;
            case sf::Event::LostFocus:
                input.canProcessInputs = false;
                break;
            default: 
                break;
            }
        }
        window.clear();
        
        input.ProcessInputs();
        fixedUpdateSystem.Update(deltaTime);
        collisionSystem.UpdateCollisions();
        collisionSystem.CheckCollision();
        renderSystem.Render(window);
        
        window.display();
    }
    return;

#pragma endregion GameLoop
}
