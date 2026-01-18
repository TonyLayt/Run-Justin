#include "Enemy.h"


Enemy::Enemy()
{

	for (int countFrame = 0; countFrame < 6; ++countFrame) {

		sf::Texture addTexture;
		if (!addTexture.loadFromFile("img/zombieSprite/Zombie1/animation/Walk" + std::to_string(countFrame+1) + ".png")) {
			std::cout << "Error load texture" << std::endl;
		}
		texture.push_back(addTexture);

		sf::Texture addTextureDead;
		if (!addTexture.loadFromFile("img/zombieSprite/Zombie1/animation/Dead" + std::to_string(countFrame + 1) + ".png")) {
			std::cout << "Error load texture" << std::endl;
		}
		textureDead.push_back(addTexture);
	}

	for (int countFrameBL = 0; countFrameBL < 3; ++countFrameBL) {

		sf::Texture addTextureBL;
		if (!addTextureBL.loadFromFile("img/zombieSprite/Zombie1/animation/blood/blood" + std::to_string(countFrameBL + 1) + ".png")) {
			std::cout << "Error load texture" << std::endl;
		}
		textureBlood.push_back(addTextureBL);
	}

	//enemySprite.setTexture(texture[0]);
	enemySprite.setScale(0.3f, 0.3f);
	enemyBlood.setScale(0.1f, 0.1f);

}

void Enemy::kill(bool status)
{
	if (checkStatusLife == false) {
		checkStatusLife = status;
	}
}

void Enemy::reset(bool status)
{
	if (checkStatusLife == true) {
		checkStatusLife = status;
	}
}



void Enemy::enemySpawn(int platformX, int platformY) // утановить точку для обекта зомби
{
    enemyX = platformX;
	enemyY = platformY;

	std::cout << "ForX " << platformX << std::endl;

	std::cout << "ForEnemyX " << enemyX << std::endl;

	enemyX -= movSpeed;

	// animation
	if (!checkStatusLife) {
		if (currentFrame >= texture.size())
		{
			currentFrame = 0;
		}

		enemySprite.setTexture(texture[currentFrame]);
		currentFrame += speedFrame;
		speedFrameDead = 0.2f;
		currentFrameDead = 0;
	    variablePositionTexture = -20;
		
	}else { 
		
		if (currentFrameDead >= textureDead.size()-1)
		{
			speedFrameDead = 0;
		}

		enemySprite.setTexture(textureDead[currentFrameDead]);
		currentFrameDead += speedFrameDead;
	}
	// ________

	if (enemyX + 300 > platformX && checkIF && !checkStatusLife)
	{
		movSpeed++;
		enemySprite.setTextureRect(sf::IntRect(280, 5, -280, 370));
		checkIFI = false;
	}
	else { checkIF = false;
		
		if (variablePositionTexture > -240) {
				variablePositionTexture -= 7;
				movSpeed--;
		}

		if (!checkIFI) {
			enemySprite.setTextureRect(sf::IntRect(380, variablePositionTexture, -480, 370)); //240
		}else { enemySprite.setTextureRect(sf::IntRect(5, variablePositionTexture, 480, 370)); }
		
	}

	if (!checkIF && enemyX + 400 < platformX + 500 && !checkStatusLife)
	{
	
		enemySprite.setTextureRect(sf::IntRect(5, 5, 280, 370));
		movSpeed--;
		checkIFI = true;
	}
	else  { checkIF = true;	}

	if (checkStatusLife) {

		if (currentFrameBlood >= textureBlood.size()-1)
		{
			speedFrameBlood = 0;
		}
		
		enemyBlood.setPosition(enemyX + 400, enemyY);
		enemyBlood.setColor(sf::Color(255, 255, 255, 180));
		enemyBlood.setTexture(textureBlood[currentFrameBlood]);
		currentFrameBlood += speedFrameBlood;

	}
	else { speedFrameBlood = 0.2; currentFrameBlood = 0; }

	enemyRect = sf::FloatRect(enemyX + 420, enemyY + 20, 50, 75);
}


void Enemy::enemyDraw(sf::RenderWindow& window)
{
    enemySprite.setPosition(enemyX + 400, enemyY);
    window.draw(enemySprite);
    //std::cout << "XUUUUU" << std::endl;

	if (checkStatusLife && speedFrameBlood)
	{
		window.draw(enemyBlood);
	}

    rectShape.setPosition(enemyRect.left, enemyRect.top);
	rectShape.setSize(sf::Vector2f(enemyRect.width, enemyRect.height));
	rectShape.setFillColor(sf::Color::Transparent); // Прозрачный фон
	rectShape.setOutlineThickness(2); // Толщина границы
	rectShape.setOutlineColor(sf::Color::Blue); // Цвет границы

	window.draw(rectShape);
}
