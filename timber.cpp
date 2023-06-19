﻿#include <SFML/Graphics.hpp>
#include <vector>
#include <sstream>
#include <SFML/Audio.hpp>
#include "Utils.h"
#include "MovingBgObj.h"
#include "InputMgr.h"
#include "Tree.h"
#include "Player.h"
#include "SpriteGo.h"
#include "EffectGo.h"

//soundBufferChop.loadFromFile("sound/chop.wav");
//soundBufferDeath.loadFromFile("sound/death.wav");
//soundBufferOutoftime.loadFromFile("sound/out_of_time.wav");
//
//soundChop.setBuffer(soundBufferChop);
//soundDeath.setBuffer(soundBufferDeath);
//soundOutoftime.setBuffer(soundBufferOutoftime);

int main()
{
    bool isPause = true;
    int score = 0;

    int screenWidth = 1920;
    int screenHeight = 1080;

    sf::Font font;
    font.loadFromFile("fonts/KOMIKAP_.ttf");

    sf::Text textMessage;
    textMessage.setFont(font);
    textMessage.setString("PRESS ENTER TO START!");
    textMessage.setCharacterSize(75);
    textMessage.setFillColor(sf::Color::White);
    Utils::SetOrigin(textMessage, Origins::MC);
    textMessage.setPosition(screenWidth * 0.5f, screenHeight * 0.5f);

    sf::Text textScore;
    textScore.setFont(font);
    textScore.setString("SCORE: ???");
    textScore.setCharacterSize(100);
    textScore.setFillColor(sf::Color::White);
    Utils::SetOrigin(textScore, Origins::TL);
    textScore.setPosition(20.f, 20.f);

    float uiTimerWidth = 400.f;
    float uiTimerHeight = 80.f;

    float duration = 15.f;
    float timer = duration;

    sf::RectangleShape uiTimer;
    uiTimer.setSize(sf::Vector2f(uiTimerWidth, uiTimerHeight));
    Utils::SetOrigin(uiTimer, Origins::BC);
    uiTimer.setPosition(screenWidth * 0.5f, screenHeight - 50.f);
    uiTimer.setFillColor(sf::Color::Red);

    sf::Texture texBackground;
    texBackground.loadFromFile("graphics/background.png");
    sf::Texture texTree;
    texTree.loadFromFile("graphics/tree.png");
    sf::Texture texCloud;
    texCloud.loadFromFile("graphics/cloud.png");
    sf::Texture texBee;
    texBee.loadFromFile("graphics/bee.png");
    sf::Texture texBranch;
    texBranch.loadFromFile("graphics/branch.png");
    sf::Texture texPlayer;
    texPlayer.loadFromFile("graphics/player.png");

    std::vector<GameObject*> gameObjects;
    gameObjects.push_back(new SpriteGo(texBackground, sf::Vector2f(1.f, 0.f), "BG", {0, 0}));

    for (int i = 0; i < 3; ++i)
    {
        MovingBgObj* newGo = new MovingBgObj(texCloud, sf::Vector2f(-1.f, -1.f), "Cloud");
        newGo->SetSpeedRange(sf::Vector2f(300.f, 600.f));
        newGo->SetLRPos(sf::Vector2f(-200.f, 1080.f / 2.f),
            sf::Vector2f(1920.f + 200.f, 1080.f / 2.f));
        newGo->SetPosXRange(0, 0);
        newGo->SetPosYRange(-400, -100);
        gameObjects.push_back(newGo);
    }

    Tree* tree = new Tree(texTree, sf::Vector2f(1.f, 0.f), "Tree");
    tree->SetOrigin(Origins::TC);
    tree->SetPosition(screenWidth * 0.5f, 0.f);
    gameObjects.push_back(tree);

    Player* player = new Player(texPlayer, sf::Vector2f(-1.f, -1.f), "Player", sf::Vector2f(0.f, 900.f));
    player->SetTree(tree);
    gameObjects.push_back(player);

    MovingBgObj* newGo = new MovingBgObj(texBee, sf::Vector2f(-1.f, -1.f), "Bee");
    newGo->SetSpeedRange(sf::Vector2f(100.f, 200.f));
    newGo->SetLRPos(sf::Vector2f(-200.f, 1080.f / 2.f),
        sf::Vector2f(1920.f + 200.f, 1080.f / 2.f));
    newGo->SetPosXRange(0, 0);
    newGo->SetPosYRange(0, 300);
    newGo->SetMoveY(2.f, 50.f);

    gameObjects.push_back(newGo);




    for (auto obj : gameObjects)
    {
        obj->Init();
    }

    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Timber!", sf::Style::Default);

    sf::Clock clock;
    while (window.isOpen())
    {
        InputMgr::Clear();

        sf::Time deltaTime = clock.restart();
        float dt = deltaTime.asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            InputMgr::Update(event);

            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            }
        }

        // 2. Update // 2. Update // 2. Update // 2. Update
        if (!isPause)
        {
            timer -= dt;

            if (timer < 0.f)
            {
                textMessage.setString("OUT OF TIME");
                Utils::SetOrigin(textMessage, Origins::MC);
                isPause = true;

                //player->SoundOutoftime();

                player->Die(timer);
            }
            else if (player->BranchDie())
            {
                textMessage.setString("Die");
                Utils::SetOrigin(textMessage, Origins::MC);
                isPause = true;

                player->Die(timer);
            }

            else
            {
                float normTime = timer / duration;
                float timeSizeX = uiTimerWidth * normTime;
                uiTimer.setSize(sf::Vector2f(timeSizeX, uiTimerHeight));

                for (auto obj : gameObjects)
                {
                    if (obj->GetActive())
                    {
                        //// 플레이어가 나뭇가지와 충돌했을 때 처리
                        //if (obj->GetName() == "Tree")
                        //{
                        //    
                        //    if (tree->CollidesWith(player))
                        //    {
                        //        player->Die();
                        //    }
                        //}
                    }
                    obj->Update(dt, score, timer, duration);
                }

                std::stringstream ss;
                ss << "SCORE: " << score;
                textScore.setString(ss.str());
            }
        }
        else
        {
            if (InputMgr::GetKeyDown(sf::Keyboard::Return))
            {
                isPause = false;
                timer = duration;
                score = 0;
                for (auto obj : gameObjects)
                {
                    obj->Init();
                }
            }
        }

        window.clear();

        // 3. Draw
        for (auto obj : gameObjects)
        {
            if (obj->GetActive())
            {
                obj->Draw(window);
            }
        }

        window.draw(textScore);
        window.draw(uiTimer);
        if (isPause)
        {
            window.draw(textMessage);
        }
        window.display();
    }

    for (auto obj : gameObjects)
    {
        obj->Release();
        delete obj;
    }

    return 0;
}