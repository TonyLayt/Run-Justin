#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "TitleScreen.h"
#include "mapObject.h"
#include "Player.h"
#include "Enemy.h"
#include "TestLoadTitleMap.h"
#include "SpritsDecor.h"
#include "backGround .h"
#include "gameOverScreen.h"
#include "Gui.h"
#include <iostream>
#include <filesystem>

bool firstEnemy = true;
bool secondEnemy = false;
int counterKillsRecord = 0;

enum Screen
{
    TitleMain,
	Pause,
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
        

        level.LoadFromFile("mainMap.tmx");
        for (int enemyNamb = 0; enemyNamb < 2; enemyNamb++)
        {
            entity.push_back(zombie);
        }
        player = std::make_unique<Player>(90, 450, objectForMap, entity);
        texturOnObject = std::make_unique<mapObject>(objectForMap, entity);
        
		music.openFromFile("sound/Graveyard_High_Score.mp3");
		music.setVolume(30);
		music.setLoop(true);
		//music.play();

        
		buffer.loadFromFile("sound/player_run.wav");
        sound.setBuffer(buffer);
        sound.setPitch(0.7f);

		buffer_jump.loadFromFile("sound/player_jump.wav");
		sound_jump.setBuffer(buffer_jump);

        buffer_damage.loadFromFile("sound/damage_sound.wav");
        sound_damage.setBuffer(buffer_damage);

        buffer_death.loadFromFile("sound/death.wav");
        sound_death.setBuffer(buffer_death);

    }
   
    void tick(sf::RenderWindow& window, sf::Event& event) {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Escape)
            {
                sound.pause();
                music.pause();

                current = Screen::Pause;

                std::cout << "Escape pressed, pausing game." << std::endl;

				return;
            }
        }
        
        texturOnObject->processingMap(*player, valSpeedBG);
        std::cout << "RANDOMAZER: " << texturOnObject->randPointSpavn << std::endl;

        /*sf::Time timer = clock.getElapsedTime();
        float secondsTimer = timer.asSeconds();*/
        
        
        //std::cout << " BEFORE_RESET@ " << secondsTimer << std::endl;
        if (player->getCheckGemeOverEvents())
        {
            if (secondClock.getElapsedTime().asSeconds() >= 1.0f)
            {
                survivalSeconds++;
                secondClock.restart();

                std::cout << "survivalSeconds: " << survivalSeconds << std::endl;
            }

            valSpeedBG = survivalSeconds;
        }
        else
        {
            valSpeedBG = 0.0f;
        }
        if (!player->getCheckGemeOverEvents())
        {
            deathTimer += survivalSeconds;
          
            if (!deathSoundPlayed)
            {
                sound_death.play();
                deathSoundPlayed = true;
            }
            music.stop();
            sound.stop();
            valSpeedBG = 0.0f;

            /*if (checkResetTimer) {
                std::cout << "RESET " << secondsTimer << std::endl;
                clock.restart();
                checkResetTimer = false;
            }*/

            if (deathTimer > 1) {
				counterKillsRecord = player->getKills();
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
                    
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !checkButtonMouse && player->getCheckGemeOverEvents())
        {
            player->performAttack();
            player->attackAnimation = true;
            checkButtonMouse = true;
            if (player->getKills() > lastNumbKill) {
				sound_damage.play();
                lastNumbKill++;
            }
        }
        if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            checkButtonMouse = false ;
		}

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !checkButtonSpace && player->getCheckGemeOverEvents())
        {
            if (player->onGround)
            {
                player->jumpAnimation = true;
                player->goY -= 10;
                checkButtonSpace = true;
                sound.pause();
                sound_jump.play();
            }
        }
        else {
            if (player->onGround && player->getCheckGemeOverEvents()) {
                player->jumpAnimation = false;
                if (sound.getStatus() != sf::Sound::Playing &&
                    current != Screen::Pause) 
                {
                sound.play(); 
                sound_jump.stop(); 
                }
            }
            if (current != Screen::Pause && music.getStatus() != sf::Sound::Playing && player->getCheckGemeOverEvents())
            {
                music.play();
            }
        }

        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            checkButtonSpace = false;
        }
     
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            // player.runAnimation = true;
            //player->goX += 10;
        }

        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            // player.runAnimation = true;
            //player->goX -= 10;
        }
        else
        {
            chekAnimatioMuve = true;
        } // false, false
        
        // DRAW PLACE
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
    //sf::Clock clock;
    sf::Clock secondClock;


    backGround BG;
    sf::Music music;
    sf::Sound sound;
    sf::Sound sound_jump;
    sf::SoundBuffer buffer;
    sf::SoundBuffer buffer_jump;
    sf::Sound sound_damage;
    sf::SoundBuffer buffer_damage;
    sf::Sound sound_death;
    sf::SoundBuffer buffer_death;
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
    bool deathSoundPlayed = false;
    int lastNumbKill = 0;
    float deathTimer = 0.0f;
    float valSpeedBG = 5.00f;
    int survivalSeconds = 0;
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
    sf::RenderWindow window(sf::VideoMode(960, 640), "Run Justin");
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
            }else { current = Screen::TitleMain; }
        }

        else if (current == Screen::Game)
        {
            game->tick(window, event);
        }

        else if (current == Screen::Pause) {
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }

                if (event.type == sf::Event::KeyPressed &&
                    event.key.code == sf::Keyboard::Escape)
                {
                    current = Screen::Game;
                    
                    std::cout << "Escape pressed, resuming game." << std::endl;
                }
            }
           
            //window.clear();
            //Тут можно отрисовать паузу, например, затемнить экран и написать "Пауза"
            //window.display();
        }

        else if  (current == Screen::GameOver)
        {
			gameOverScreen.setKillsST(counterKillsRecord); // тут нужно передать реальное количество убийств
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
                if (gameOverScreen.GetExitButton().getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                {
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
