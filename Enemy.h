#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>


class Enemy {

public:
	Enemy();

	void enemySpawn(int x, int y);
	void enemyDraw(sf::RenderWindow& window);
	void kill(bool status);
	void reset(bool status);
    sf::FloatRect enemyRect;

private:
	int enemyX = 0;
	int enemyY = 0;
	int movSpeed = 3;
	int variablePositionTexture = -20;
	bool checkStatusLife = false;
	bool checkIF = true;
	bool checkIFI = false;
	
	float currentFrameDead = 0;
	float currentFrame = 0;
	float speedFrame = 0.1;
	float speedFrameDead = 0.1;
	float currentFrameBlood = 0;
	float speedFrameBlood = 0.2;

	sf::Sprite enemySprite;
	sf::Sprite enemyBlood;
	std::vector<sf::Texture> texture;
	std::vector<sf::Texture> textureDead;
	std::vector<sf::Texture> textureBlood;

	sf::RectangleShape rectShape;


};
