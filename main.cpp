#include <SFML/Graphics.hpp>
#include "TitleScreen.h"
#include "mapObject.h"
#include "Player.h"
#include "Enemy.h"
#include "TestLoadTitleMap.h"
#include "SpritsDecor.h"
#include "backGround .h"
#include <iostream>
#include <filesystem>

bool firstEnemy = true;
bool secondEnemy = false;
bool checkButtonMouse = true;
float valSpeedBG = 5.00f;

void permissionToRespawnOneEnemy(int checkNumbPlatform, int nambPlatform, int randPointSpavn) // разрешение на респ зомби
{
    if (checkNumbPlatform == nambPlatform)
    {
        firstEnemy = false;
    }
    if (checkNumbPlatform == nambPlatform && randPointSpavn == nambPlatform)
    {
        firstEnemy = true;
    }
}

void permissionToRespawnSecondEnemy(int checkNumbPlatform, int nambPlatform, int randPointSpavn) // разрешение на респ зомби
{
    if (checkNumbPlatform == nambPlatform)
    {
        secondEnemy = false;
    }
    if (checkNumbPlatform == nambPlatform && randPointSpavn == nambPlatform)
    {
        secondEnemy = true;
    }
}

int main(int argc, char *argv[])
{
    // jast this is need for normal start :D
    //std::filesystem::path exePath = std::filesystem::absolute(argv[0]);
    //std::filesystem::path exeDir = exePath.parent_path();

    //std::filesystem::current_path(exeDir);

    //std::cout << "CWD fixed to: " << std::filesystem::current_path() << std::endl;

    //std::cout << "CWD: " << std::filesystem::current_path() << std::endl;
    //// jast this is need for normal start  :D
    //std::cout << "START" << std::filesystem::current_path() << std::endl;
    enum Screen
    {
        TitleMain,
        Game
    };

    Screen current = Screen::TitleMain;

    sf::RenderWindow window(sf::VideoMode(960, 640), "Noname Game");
    window.setFramerateLimit(60);
    sf::Clock clock;

    sf::Event event;
    TitleScreen mainScreen;
    backGround BG;
    Level level;
    level.LoadFromFile("MyMapp.tmx");
    std::vector<Object> &objectForMap = level.GetAllObjects();

    //mapObject texturOnObject(objectForMap); // object for texture

    ProcessingSpawnObject createDecoreObjects_1;
    ProcessingSpawnObject createDecoreObjects_2;
    ProcessingSpawnObject createDecoreObjects_3;

    // Player player(90, 450, objectForMap, entity);

    Enemy zombie;
    std::vector<Enemy> entity;
    for (int enemyNamb = 0; enemyNamb < 2; enemyNamb++)
    {
        entity.push_back(zombie);
    }

    Player player(90, 450, objectForMap, entity);
    mapObject texturOnObject(objectForMap, entity); // object for texture
    bool chekAnimatioMuve = false;

    while (window.isOpen())
    {
        if (current == Screen::TitleMain)
        {

            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left)
            {

                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (mainScreen.GetStartButton().getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                {
                    std::cout << "PREEEEESSSS! ";
                    current = Screen::Game;
                }
            }

            window.clear();
            mainScreen.DrawTitle(window);
            window.display();
        }

        else if (current == Screen::Game)
        {

            texturOnObject.processingMap(player, valSpeedBG);
            std::cout << "RANDOMAZER: " << texturOnObject.randPointSpavn << std::endl;

            createDecoreObjects_1.respDecore(objectForMap[1].rect.left, objectForMap[1].rect.top); // This is a respawn decore point
            createDecoreObjects_2.respDecore(objectForMap[0].rect.left, objectForMap[0].rect.top);
            createDecoreObjects_3.respDecore(objectForMap[2].rect.left, objectForMap[2].rect.top);

            permissionToRespawnOneEnemy(texturOnObject.numbPlatform, 1, texturOnObject.randPointSpavn);
            permissionToRespawnSecondEnemy(texturOnObject.numbPlatform, 2, texturOnObject.randPointSpavn);

            if (firstEnemy)
            {
                entity[0].enemySpawn(objectForMap[1].rect.left, objectForMap[1].rect.top - objectForMap[1].rect.height - 30); // попробуй флагами определить направления
            }
            if (secondEnemy)
            {
                entity[1].enemySpawn(objectForMap[2].rect.left, objectForMap[2].rect.top - objectForMap[2].rect.height - 30); // попробуй флагами определить направления
            }

            if (!player.getCheckGemeOverEvents())
            {
                valSpeedBG = 0;
            }

            BG.speedBG(valSpeedBG);
            player.update();
            player.runAnimation = true;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left && !checkButtonMouse)
            {
				player.performAttack();
                player.attackAnimation = true;
                checkButtonMouse = true;
            }
            
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) 
                checkButtonMouse = false;
           

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                // player.runAnimation = true;
                player.goX += 10;
            }

            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                // player.runAnimation = true;
                player.goX -= 10;
            }
            else
            {
                player.runAnimation = true;
                chekAnimatioMuve = true;
            } // false, false

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                if (player.onGround)
                {
                    player.jumpAnimation = true;
                    player.goY -= 10;
                }
            }
            else
            {
                player.jumpAnimation = false;
            }

            window.clear();
            BG.DrawBG(window);
            createDecoreObjects_1.DrawDecore(window); // set point
            createDecoreObjects_2.DrawDecore(window);
            createDecoreObjects_3.DrawDecore(window);
            level.Draw(window);
            texturOnObject.showObject(window);
            player.playerDraw(window);

            if (!entity.empty())
            {
                for (int item = 0; item < entity.size(); item++)
                {
                    entity[item].enemyDraw(window);
                }
            }
            else
            {
                std::cout << "!Empty!" << std::endl;
            }

            window.display();
        }
    }

    return 0;
}
