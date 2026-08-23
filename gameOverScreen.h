#pragma once

#include <SFML/Graphics.hpp>

using namespace std;

class gameOverScreen
{
public:
    gameOverScreen();
    void DrawGameOver(sf::RenderWindow& window);
    void setKillsST(int count);
    sf::RectangleShape& GetRestartButton();
    sf::RectangleShape& GetExitButton();

private:
    sf::Texture textureForTitle;
    sf::Texture textureForTitleKill_st;
    sf::Sprite imageKill_st;

    sf::Sprite image;
    sf::RectangleShape restartButton;
    sf::RectangleShape exitButton;

    sf::Texture textureCount_st;
    vector <sf::Sprite> spriteCounts_st;
    vector <sf::Sprite> numCountsST;

    string str_st;

    int kills_count_st = 0;
    int advance[10] = {
        64, // 0
        198, // 1
        340, // 2
        489, // 3
        620, // 4
        760, // 5
        900, // 6
        1046, // 7
        1168, // 8
        1333  // 9
    };
    int posX = 410;     // де показувати число на екрані
    int posY = 330;
    int spacing = 65;   // додатковий пробіл між цифрам
	int shiftNumForKillST = 10;
};

