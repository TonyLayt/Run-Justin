#include <SFML/Graphics.hpp>
#include "TitleScreen.h"
#include "mapObject.h"
#include "Player.h"
#include "Enemy.h"
#include "TestLoadTitleMap.h"
#include "SpritsDecor.h"
#include "backGround .h"
#include "gameOverScreen.h"
#include <iostream>
#include <filesystem>

bool firstEnemy = true;
bool secondEnemy = false;

enum Screen
{
    TitleMain,
    Loading,
    Game,
    GameOver
};

Screen current = Screen::TitleMain;

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

class LoadingScreen
{
public:
    LoadingScreen() {
        
        if (!loadingTexture.loadFromFile("img/loading/loadingScreen.png"))
        {
            std::cout << "ERROR: loading.png not found\n";
        }
        loadingSprite.setTexture(loadingTexture);
        loadingSprite.scale(0.66f, 0.66f);
        loadingSprite.setPosition(-50, 0);
    }

private:
    sf::Sprite loadingSprite;
    sf::Texture loadingTexture;

public:
    void drawloading(sf::RenderWindow& window) {

        window.draw(loadingSprite);
    }
};

class GameProcessing {
public:
    GameProcessing() {
        

        level.LoadFromFile("MyMapp.tmx");
        for (int enemyNamb = 0; enemyNamb < 2; enemyNamb++)
        {
            entity.push_back(zombie);
        }
        player = std::make_unique<Player>(90, 450, objectForMap, entity);
        texturOnObject = std::make_unique<mapObject>(objectForMap, entity);

      
    }

    void tick(sf::RenderWindow& window, sf::Event& event) {
        
        texturOnObject->processingMap(*player, valSpeedBG);
        std::cout << "RANDOMAZER: " << texturOnObject->randPointSpavn << std::endl;

        sf::Time timer = clock.getElapsedTime();
        float secondsTimer = timer.asSeconds();

        std::cout << " BEFORE_RESET@ " << secondsTimer << std::endl;
        if (!player->getCheckGemeOverEvents())
        {

            if (checkResetTimer) {
                std::cout << "RESET " << secondsTimer << std::endl;
                clock.restart();
                checkResetTimer = false;
            }

            else if (secondsTimer > 1) {
                current = Screen::GameOver;
            }

        }

        for (int numDec = 0; numDec < decorObjects.size(); numDec++)
        {
            decorObjects[numDec].respDecore(objectForMap[numDec].rect.left, objectForMap[numDec].rect.top);
        }

        permissionToRespawnOneEnemy(texturOnObject->numbPlatform, 1, texturOnObject->randPointSpavn);
        permissionToRespawnSecondEnemy(texturOnObject->numbPlatform, 2, texturOnObject->randPointSpavn);

        if (firstEnemy)
        {
            entity[0].enemySpawn(objectForMap[1].rect.left, objectForMap[1].rect.top - objectForMap[1].rect.height - 30); // попробуй флагами определить направления
        }
        if (secondEnemy)
        {
            entity[1].enemySpawn(objectForMap[2].rect.left, objectForMap[2].rect.top - objectForMap[2].rect.height - 30); // попробуй флагами определить направления
        }

        if (!player->getCheckGemeOverEvents())
        {
            valSpeedBG = 0;
        }

        BG.speedBG(valSpeedBG);
        player->update();
        player->runAnimation = true;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left && !checkButtonMouse && player->getCheckGemeOverEvents())
        {
            player->performAttack();
            player->attackAnimation = true;
            checkButtonMouse = true;
        }

        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            checkButtonMouse = false;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !checkButtonSpace && player->getCheckGemeOverEvents())
        {
            if (player->onGround)
            {
                player->jumpAnimation = true;
                player->goY -= 10;
                checkButtonSpace = true;
            }
        }
        else {
            if (player->onGround) { player->jumpAnimation = false; }
        }

        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            checkButtonSpace = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            // player.runAnimation = true;
            player->goX += 10;
        }

        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            // player.runAnimation = true;
            player->goX -= 10;
        }
        else
        {
            chekAnimatioMuve = true;
        } // false, false


        window.clear();
        BG.DrawBG(window);
        for (auto& decor : decorObjects)
        {
            decor.DrawDecore(window);
        }
        level.Draw(window);
        texturOnObject->showObject(window);
        player->playerDraw(window);

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


private:
    sf::Clock clock;
    backGround BG;
    Level level;
    std::unique_ptr<Player> player;
    std::vector<Object>& objectForMap = level.GetAllObjects();
    Enemy zombie;
    std::vector<Enemy> entity;
    std::vector<ProcessingSpawnObject> decorObjects { 3 };
    std::unique_ptr<mapObject> texturOnObject;
    bool chekAnimatioMuve = false; 
    bool checkButtonMouse = true;
    bool checkButtonSpace = true;
    bool checkResetTimer = true;
    float valSpeedBG = 5.00f;

};


int main(int argc, char *argv[])
{
    srand(time(0));
    // jast this is need for normal start :D
    //std::filesystem::path exePath = std::filesystem::absolute(argv[0]);
    //std::filesystem::path exeDir = exePath.parent_path();

    //std::filesystem::current_path(exeDir);

    //std::cout << "CWD fixed to: " << std::filesystem::current_path() << std::endl;

    //std::cout << "CWD: " << std::filesystem::current_path() << std::endl;
    //// jast this is need for normal start  :D
    //std::cout << "START" << std::filesystem::current_path() << std::endl;
    
    bool needCreateGame = false;
    sf::RenderWindow window(sf::VideoMode(960, 640), "Noname Game");
    window.setFramerateLimit(60);
    sf::Event event;
    std::unique_ptr<GameProcessing> game;
    LoadingScreen loading;
    TitleScreen mainScreen;
    gameOverScreen gameOverScreen;
    
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
                    needCreateGame = true;
                    current = Screen::Loading;
                }
            }

            window.clear();
            mainScreen.DrawTitle(window);
            window.display();
        }

        else if (current == Screen::Loading)
        {
            // 1) показываем кадр Loading
            window.clear();
            loading.drawloading(window);
            window.display();

            // 2) теперь создаём игру (тут будет "подгрузка")
            if (needCreateGame)
            {
                needCreateGame = false;
                game = std::make_unique<GameProcessing>();
                current = Screen::Game;
            }
        }

        else if (current == Screen::Game)
        {
            game->tick(window, event);
        }

        else if  (current == Screen::GameOver)
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

                if (gameOverScreen.GetRestartButton().getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                {
                    needCreateGame = true;
                    current = Screen::Loading;
                }
                
            }

            window.clear();
            gameOverScreen.DrawGameOver(window);
            window.display();
        }
    }

    return 0;
}
