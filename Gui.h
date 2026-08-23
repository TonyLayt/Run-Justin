#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;


class CountGui {
private:   
    Texture textureCount;
	vector <Sprite> spriteCounts;

    Texture textureZombieHeadIco;
    Sprite spriteZombieHeadIco;

    vector <Sprite> numCounts;

    string str;
	int kills_count = 0;

    int posX = 99;     // де показувати число на екрані
    int posY = 18;
    int spacing = 65;   // додатковий пробіл між цифрам

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

public:
    CountGui();
	void setKills(int count);
    void drawGui(sf::RenderWindow& window);

};
