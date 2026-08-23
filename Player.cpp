#include <iostream>
#include "Player.h"

Player::Player(float setPosX, float setPosY, std::vector<Object> &objs, std::vector<Enemy> &enemy) : objs(objs), enemy(enemy)
{
	view.reset(sf::FloatRect(0, 0, 960, 640));
;
	if (!TextureIdle.loadFromFile("img/playerSprite/Idle__000.png"))
	{
		std::cout << "Error load texture" << std::endl;
	}
	for (int countFrame = 0; countFrame < 9; ++countFrame)
	{
		sf::Texture addTextureDown;
		if (!addTextureDown.loadFromFile("img/playerSprite/Dead__00" + std::to_string(countFrame) + ".png"))
		{
			std::cout << "Error load texture" << std::endl;
		}
		downFrames.push_back(addTextureDown);

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

	buffer_knife.loadFromFile("sound/swing.wav");
	sound_knife.setBuffer(buffer_knife);

	playerRect = sf::FloatRect(setPosX, setPosY, 50, 110);

	plySprite.setScale(0.3f, 0.3f);
	plySprite.setTexture(TextureIdle);
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

	// анимация упал 
	if (inactivitAnimation)
	{
		playerRect.left -= Xcon;
		Xcon *= 0.85f; // Быстрое затухание
		if (currentFrameDw >= downFrames.size() - 1)
		{
			speedFrameDw = 0;
			Xcon = 0;
		}
		plySprite.setTexture(downFrames[currentFrameDw]);
		currentFrameDw += speedFrameDw;
	}

	// анимация при движении
	if (runAnimation && GemeOverEvents)
	{
		inactivitAnimation = false;
		if (currentFrame >= runFrames.size())
		{
			currentFrame = 0;
		}
		plySprite.setTexture(runFrames[currentFrame]);
		plySprite.setTextureRect(sf::IntRect(5, 5, 500, 486));

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
		if (currentFrameJmp >= jumpFrames.size()-1)
		{
			speedFrameJmp = 0;

		}
		plySprite.setTexture(jumpFrames[currentFrameJmp]); // анимация прыжка
		currentFrameJmp += speedFrameJmp;
	}
	else { speedFrameJmp = 0.1; currentFrameJmp = 0;}
	

	if (attackAnimation && onGround)
	{
		if (currentFrameAt >= attackFrames.size())
		{
			currentFrameAt = 0;
			attackAnimation = false;
		}
		plySprite.setTexture(attackFrames[currentFrameAt]); // анимация атаки
		currentFrameAt += speedFrameAt;
		sound_knife.play();
		plySprite.setTextureRect(sf::IntRect(5, 5, 600, 486));
	}
	
	goX = 0;
	playerGui.setKills(kills);
}

bool Player::getCheckGemeOverEvents()
{
	return GemeOverEvents;
}

void Player::setCheckGemeOverEvents(bool boolflag)
{
	 GemeOverEvents = boolflag;
}

void Player::performAttack()
{
	checkCollisionWithEnemy = true;
	rectAttacjShape.setPosition(playerRect.left + 50, playerRect.top);
	rectAttacjShape.setSize(sf::Vector2f(playerRect.width + 40, playerRect.height));
	rectAttacjShape.setFillColor(sf::Color::Transparent); // Прозрачный фон
	rectAttacjShape.setOutlineThickness(2);				  // Толщина границы
	rectAttacjShape.setOutlineColor(sf::Color::Yellow);	  // Цвет границы

	knifeRect = sf::FloatRect(playerRect.left + 50, playerRect.top, playerRect.width + 40, playerRect.height);

	for (int countEnemy = 0; countEnemy < enemy.size(); countEnemy++)
	{

		if (knifeRect.intersects(sf::FloatRect(enemy[countEnemy].enemyRect)) && onGround)
		{
			enemy[countEnemy].kill(true);
		}

		if (enemy[countEnemy].getStatusLife() && !enemy[countEnemy].checkKillPush) {
			enemy[countEnemy].checkKillPush = true;
			kills++;
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
				if (!enemy[countEnemy].getStatusLife()) {
					enemy[countEnemy].setAttack(true);
					GemeOverEvents = false;
				}
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
	/*if (checkCollisionWithEnemy && onGround)
	{
		window.draw(rectAttacjShape);
	}
	window.draw(rectShape);*/
	window.draw(plySprite);
	window.setView(view);
	playerGui.drawGui(window);
	std::cout << "PLAYERDRAW" << std::endl;

	return 0;
}

int Player::getKills()
{
	return kills;
}
