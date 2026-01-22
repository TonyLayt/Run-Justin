#pragma once

#include <SFML/Graphics.hpp>

class gameOverScreen
{
public:
    gameOverScreen();
    void DrawGameOver(sf::RenderWindow& window);
    sf::RectangleShape& GetRestartButton();

private:
    sf::Texture textureForTitle;
    sf::Sprite image;
    sf::RectangleShape restartButton;
};

