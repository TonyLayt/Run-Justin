#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

struct ObjectDecor
{
public:

	ObjectDecor(Texture& textureFile);

	Sprite sprite;

private:

};


class ProcessingSpawnObject {

public:
	ProcessingSpawnObject();

	void respDecore (int x, int y);

	void DrawDecore(sf::RenderWindow& window);

private:
    int randPointBrush = 0;
	int randPointBrush_2 = 0;
	int randPointBrush_3 = 0;
    int randPointTree = 0; 
	int randPointTree_2 = 0;
    int randSpawnFirst = 0;
    int randSpawnSecond = 0;
	int tombStone = 0;
	int tombStone_1 = 0;


	vector <ObjectDecor> objectDecors;
    Texture addTexture[7];
    vector <Texture> texture;
};
