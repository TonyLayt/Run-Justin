#include <iostream>
#include "Player.h"

Player::Player(float setPosX, float setPosY, std::vector<Object> &objs, std::vector<Enemy> &enemy) : objs(objs), enemy(enemy)
{
	view.reset(sf::FloatRect(0, 0, 960, 640));

	for (int countFrame = 0; countFrame < 9; ++countFrame)
	{

		sf::Texture addTextureInactivit;
		if (!addTextureInactivit.loadFromFile("img/playerSprite/Idle__00" + std::to_string(countFrame) + ".png"))
		{
			std::cout << "Error load texture" << std::endl;
		}
		inactivitFrames.push_back(addTextureInactivit);

		sf::Texture addTextureRun;
		if (!addTextureRun.loadFromFile("img/playerSprite/Run__00" + std::to_string(countFrame) + ".png"))
		{
			std::cout << "Error load texture" << std::endl;
		}
		runFrames.push_back(addTextureRun);

		sf::Texture addTextureJump;
		if (!addTextureJump.loadFromFile("img/playerSprite/Jump__00" + std::to_string(countFrame) + ".png"))
		{
			std::cout << "Error load texture" << std::endl;
		}
		jumpFrames.push_back(addTextureJump);
	
	}

	for (int countFrameAt = 0; countFrameAt < 3; ++countFrameAt){
		sf::Texture addTextureAttack;
		if (!addTextureAttack.loadFromFile("img/playerSprite/Attack__00" + std::to_string(countFrameAt) + ".png"))
		{
			std::cout << "Error load texture" << std::endl;
		}
		
		attackFrames.push_back(addTextureAttack);
	}

	playerRect = sf::FloatRect(setPosX, setPosY, 50, 110);

	plySprite.setScale(0.3f, 0.3f);
	plySprite.setTexture(inactivitFrames[0]);
	plySprite.setOrigin(plySprite.getLocalBounds().width / 2, plySprite.getLocalBounds().height / 2);
}
void Player::SetAnimationSpeed(float newSpeed)
{
	speedFrame += newSpeed;
};

void Player::update()
{
	onGround = false;

	playerRect.left += goX;
	collision(false); // проверка по X

	// гравитация тянет по Y
	if (!onGround)
		goY += 0.4f;

	playerRect.top += goY;
	collision(true); // проверка по игрику

	// анимация в стоячем положении (пока не активна)
	if (inactivitAnimation)
	{
		if (currentFrame >= inactivitFrames.size())
		{
			currentFrame = 0;
		}
		plySprite.setTexture(inactivitFrames[currentFrame]);
		currentFrame += speedFrame;
		// std::cout << currentFrame << std::endl;
	}

	// анимация при движении
	if (runAnimation)
	{
		inactivitAnimation = false;
		if (currentFrame >= runFrames.size())
		{
			currentFrame = 0;
		}
		plySprite.setTexture(runFrames[currentFrame]);
		plySprite.setTextureRect(sf::IntRect(5, 5, 400, 486));
		if (goX > 0)
		{
			plySprite.setTextureRect(sf::IntRect(5, 5, 400, 486));
		}
		if (goX < 0)
		{
			plySprite.setTextureRect(sf::IntRect(400, 5, -400, 486));
		}
		currentFrame += speedFrame;
	}
	else
	{
		inactivitAnimation = true;
	}

	if (jumpAnimation)
	{
		if (currentFrame >= jumpFrames.size())
		{
			currentFrame = 0;
		}
		plySprite.setTexture(jumpFrames[currentFrame]); // анимация прыжка
		currentFrame += speedFrame;
	}
	else
	{
		inactivitAnimation = true;
	}

	if (attackAnimation)
	{
		if (currentFrameAt >= attackFrames.size())
		{
			currentFrameAt = 0;
			attackAnimation = false;
		}
		plySprite.setTexture(attackFrames[currentFrameAt]); // анимация атаки
		currentFrameAt += speedFrameAt;
		plySprite.setTextureRect(sf::IntRect(5, 5, 600, 486));
	}
	else
	{
		inactivitAnimation = true;
	}
	goX = 0;

}

bool Player::getCheckGemeOverEvents()
{
	return GemeOverEvents;
}

void Player::performAttack()
{
	checkCollisionWithEnemy = true;
	rectAttacjShape.setPosition(playerRect.left + 70, playerRect.top);
	rectAttacjShape.setSize(sf::Vector2f(playerRect.width, playerRect.height));
	rectAttacjShape.setFillColor(sf::Color::Transparent); // Прозрачный фон
	rectAttacjShape.setOutlineThickness(2);				  // Толщина границы
	rectAttacjShape.setOutlineColor(sf::Color::Yellow);	  // Цвет границы

	knifeRect = sf::FloatRect(playerRect.left + 70, playerRect.top, playerRect.width, playerRect.height);

	for (int countEnemy = 0; countEnemy < enemy.size(); countEnemy++)
	{

		if (knifeRect.intersects(sf::FloatRect(enemy[countEnemy].enemyRect)))
		{
			enemy[countEnemy].kill(true);
		}
	}
}

void Player::collision(bool dir)
{
	std::cout << "PlayerPosX " << playerRect.left << std::endl;

	bool touchGround = false;

	for (int countObject = 0; countObject < objs.size(); countObject++)
	{
		if (playerRect.top > objs[countObject].rect.top)
		{
			GemeOverEvents = false;
			std::cout << "DOOOWN" << std::endl;
		}
		if (playerRect.intersects(sf::FloatRect(objs[countObject].rect)))
		{
			if (objs[countObject].name == "TerraCol")
			{
				if (goX == 0 && dir == false)
				{
					playerRect.left = objs[countObject].rect.left - playerRect.width;
				}

				if (goX < 0 && dir == false)
				{
					playerRect.left = objs[countObject].rect.left + objs[countObject].rect.width;
				}

				if (goY > 0 && dir == true)
				{
					playerRect.top = objs[countObject].rect.top - playerRect.height;
					goY = 0;
					onGround = true;
				}

				if (goY < 0 && dir == true) // на случай если башкой ударится
				{
					goY = 0;
				}
			}
		}

		for (int countEnemy = 0; countEnemy < enemy.size(); countEnemy++)
		{

			if (playerRect.intersects(sf::FloatRect(enemy[countEnemy].enemyRect)))
			{

				std::cout << "WAAAAAAAAAAAAAAAA!" << std::endl;
			}
		}
	}
	checkCollisionWithEnemy = false;
}

bool Player::getCheckCollisionWithEnemy()
{
	return checkCollisionWithEnemy;
}

int Player::playerDraw(sf::RenderWindow &window)
{

	plySprite.setPosition(playerRect.left + 12, playerRect.top + 39);
	playecCordFORView(playerRect.left, playerRect.top); // камера

	rectShape.setPosition(playerRect.left, playerRect.top);
	rectShape.setSize(sf::Vector2f(playerRect.width, playerRect.height));
	rectShape.setFillColor(sf::Color::Transparent); // Прозрачный фон
	rectShape.setOutlineThickness(2);				// Толщина границы
	rectShape.setOutlineColor(sf::Color::Red);		// Цвет границы
	if (checkCollisionWithEnemy)
	{
		window.draw(rectAttacjShape);
	}
	window.draw(rectShape);
	window.draw(plySprite);
	window.setView(view);

	std::cout << "PLAYERDRAW" << std::endl;

	return 0;
}
