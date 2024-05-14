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
#include "Systems/DistanceManager.h"
#include "Systems/Input.h"
#include "Systems/SpriteLoader.h"

enum class GameState { Running, Restart, Quit};

Game::Game(unsigned int windowWidth, unsigned int windowHeight) :
    window(sf::VideoMode(windowWidth, windowHeight), "Fun Driving Sim", sf::Style::Close),
    screenbounds(windowWidth, windowHeight)
{
    window.setFramerateLimit(60); //TODO: check if uncapping doesnt break systems

    if (!window.isOpen())
    {
        std::cerr << "Failed to create window!" << '\n';
        throw std::runtime_error("Failed to create window!");
    }

    srand(static_cast<unsigned>(time(0)));
}

void Game::Run()
{
#pragma region Init

    tgui::Gui gui;
    gui.setWindow(window);
    GameState gameState = GameState::Running;

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

    const float maxAcceleration = 1500;
    auto player = std::make_shared<Player>(carSprite, input,
        sf::Vector2f(screenbounds.width / 2, 600),
        acceleration, 500, maxAcceleration, 100, 60,
        50,0,100,
        6, 7.5, 1);


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

    roadSystem->canUpdate = true;

#pragma endregion Road

#pragma region Carspawner
    
    auto carSpawner = std::make_shared<CarSpawner>(screenbounds,canScroll,acceleration, startPos, endPos, storePos, 35, 1, 4);

    auto car1 = std::make_shared<Car>(storePos,spriteLoader.LoadSprite("car (1).png"));
    auto car2 = std::make_shared<Car>(storePos,spriteLoader.LoadSprite("car (2).png"));
    auto car3 = std::make_shared<Car>(storePos,spriteLoader.LoadSprite("car (3).png"));
    
    carSpawner->AddInactive({car1,car2, car3});

#pragma endregion Carspawner

#pragma region BottleSpawner

    auto bottleSpawner = std::make_shared<BottleSpawner>(screenbounds, canScroll, acceleration, startPos, endPos, storePos, 100, 1, 4, 45, 85);
    
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
    
    const RenderSystem renderSystem({road1, road2, road3, player, leftBarrier, rightBarrier, car1, car2, car3, bottle1, bottle2, bottle3});
    const FixedUpdateSystem fixedUpdateSystem({roadSystem, carSpawner, bottleSpawner, player});
    const CollisionSystem collisionSystem({leftBarrier, rightBarrier, car1, car2, car3, bottle1, bottle2, bottle3},screenbounds, player);
    DistanceManager distanceManager(maxAcceleration * 2500);
    

#pragma endregion Systems

#pragma region UI
    
    tgui::Theme::setDefault("./Assets/Themes/TransparentGrey.txt");

    auto mainMenu = tgui::Panel::create();
    auto deathScreen = tgui::Panel::create();
    auto winScreen = tgui::Panel::create();
    auto hud = tgui::Panel::create();

    mainMenu->getRenderer()->setBackgroundColor(sf::Color::Transparent);
    deathScreen->getRenderer()->setBackgroundColor(sf::Color::Transparent);
    winScreen->getRenderer()->setBackgroundColor(sf::Color::Transparent);
    hud->getRenderer()->setBackgroundColor(sf::Color::Transparent);
    
    mainMenu->loadWidgetsFromFile("./Assets/UI/mainMenu.txt");
    deathScreen->loadWidgetsFromFile("./Assets/UI/deathScreen.txt");
    winScreen->loadWidgetsFromFile("./Assets/UI/winScreen.txt");
    hud->loadWidgetsFromFile("./Assets/UI/hud.txt");
    
    gui.add(mainMenu);
    gui.add(deathScreen);
    gui.add(winScreen);
    gui.add(hud);

    roadSystem->canUpdate = true;
    player->canUpdate = true;

    //Play button
    auto playButton = gui.get<tgui::Button>("Play Button");
    playButton->onPress([&]
    {
        input.canProcessInputs = true;
        
        player->canUpdate = true;
        player->canMove = true;
        player->canIncreaseDistance = true;
        player->canCheckDrunkenness = true;
        
        bottleSpawner->canUpdate = true;
        carSpawner->canUpdate = true;
        
        mainMenu->setVisible(false);
        hud->setVisible(true);
    });

    auto restartButton = deathScreen->get<tgui::Button>("Restart Button");
    auto quitButton1 = deathScreen->get<tgui::Button>("Quit Button");
    auto quitButton2 = winScreen->get<tgui::Button>("Quit Button");
    
    restartButton->onClick([&]
    {
        gameState = GameState::Restart;
    });
    
    quitButton1->onClick([&]
    {
        gameState = GameState::Quit;
    });
    quitButton2->onClick([&]
    {
        gameState = GameState::Quit;
    });
    
    //Drunkenness bar
    auto drunkennessBar = gui.get<tgui::ProgressBar>("DrunkennessBar");
    player->drunkennessUpdated.Subscribe( [&](float drunkenness)
    {
       drunkennessBar->setValue(drunkenness);
    });
    
    deathScreen->setVisible(false);
    winScreen->setVisible(false);
    hud->setVisible(false);

    player->onSober.Subscribe( [&]
    {
        canScroll = false;
        input.canProcessInputs = false;
        player->canMove = false;
        player->canIncreaseDistance = false;
        player->canCheckDrunkenness = false;
        deathScreen->setVisible(true);
        hud->setVisible(false);
    });

    auto distanceBar = gui.get<tgui::ProgressBar>("DistanceBar");
    distanceBar->setMaximum(distanceManager.GetMaxDistance());
    
    player->movementUpdated.Subscribe([&] (float amount)
    {
        distanceBar->setValue(distanceManager.Increment(amount));
    });
    distanceManager.onEndReached.Subscribe([&]
    {
        canScroll = false;
        input.canProcessInputs = false;
        player->canMove = false;
        player->canIncreaseDistance = false;
        player->canCheckDrunkenness = false;
        hud->setVisible(false);
        winScreen->setVisible(true);
    });
    
    carSpawner->onCollision.Subscribe([&]
    {
        canScroll = false;
        input.canProcessInputs = false;
        player->canMove = false;
        player->canIncreaseDistance = false;
        player->canCheckDrunkenness = false;
        deathScreen->setVisible(true);
        hud->setVisible(false);
    });

#pragma endregion UI

#pragma region GameLoop

    sf::Clock clock;
    
    while (window.isOpen())
    {
        switch(gameState)
        {
        case GameState::Restart:
            shouldRun = true;
            return;
        case GameState::Quit:
            shouldRun = false;
            return;
        }

        sf::Time elapsed = clock.restart();
        float deltaTime = elapsed.asSeconds();
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            gui.handleEvent(event);
            
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                shouldRun = false;
                return;
            case sf::Event::GainedFocus:
                input.focussed = true;
                break;
            case sf::Event::LostFocus:
                input.focussed = false;
                break;
            default: 
                break;
            }
        }
        window.clear();

        distanceManager.CheckDistance();
        
        input.ProcessInputs();
        fixedUpdateSystem.Update(deltaTime);
        collisionSystem.UpdateCollisions();
        collisionSystem.CheckCollision();
        renderSystem.Render(window);
        
        gui.draw();
        
        window.display();
    }
    #pragma endregion GameLoop
}
