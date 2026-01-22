#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "TestLoadTitleMap.h"
#include "camera.h"

//#include "mapObject.h"
#include "Enemy.h"

class Player {

public:
    bool onGround;
    float verticalVelocity = 0.0f;
	bool fif = false;
	float goX;
	float goY;
	float BoxPosX;
	float BoxPosY;
	

	bool inactivitAnimation = false;
	bool runAnimation;
	bool jumpAnimation;
	bool attackAnimation;

    sf::Sprite plySprite;
    sf::FloatRect playerRect;


	sf::RectangleShape rectShape;
	sf::RectangleShape rectShapeEnemy;
	sf::FloatRect knifeRect;

	Player(float setPosX, float setPosY, std::vector<Object>& objs, std::vector<Enemy>& enemy);
	void SetAnimationSpeed(float newSpeed);
	void update();
	void collision(bool dir);
	bool getCheckCollisionWithEnemy();
	bool getCheckGemeOverEvents();
	void setCheckGemeOverEvents(bool bool_flag);
	void performAttack();
	int playerDraw(sf::RenderWindow& window);

private:
	sf::RectangleShape rectAttacjShape;

	std::vector<sf::Texture> downFrames;
	std::vector<sf::Texture> runFrames;
	std::vector<sf::Texture> jumpFrames;
	std::vector<sf::Texture> attackFrames;
	sf::Texture TextureIdle;
	//std::vector<Properti> templMap;
	std::vector<Object>& objs;
	std::vector<Enemy>& enemy;
	bool GemeOverEvents = true;
	bool checkCollisionWithEnemy = false;
	float currentFrame = 0;
	float currentFrameAt = 0;
	float currentFrameDw = 0;
	float currentFrameJmp = 0;
	float speedFrame = 0.2f;
	float speedFrameDw = 0.2f;
	float speedFrameJmp = 0.2f;
	float speedFrameAt = 0.2f;
	float Xcon = 10.0;
	const float gravity = 0;
};
