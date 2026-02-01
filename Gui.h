#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;


class CountGui {
private:   
    Texture textureCount;
	vector <Sprite> spriteCounts;

    std::string str;
	int kills_count = 0;
    

public:
    CountGui();
	void setKills(int count);
    void drawGui(sf::RenderWindow& window);

};
