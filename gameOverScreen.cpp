#include "gameOverScreen.h"

gameOverScreen::gameOverScreen()
{
    textureForTitle.loadFromFile("img/GameOver/gameOverScreen.png");
    image.setTexture(textureForTitle);
    image.scale(0.66f, 0.66f);
    image.setPosition(-50, 0);

    // Простая белая кнопка
    restartButton.setSize(sf::Vector2f(200, 60));  
    restartButton.setFillColor(sf::Color::Transparent);
    /*restartButton.setOutlineThickness(3);
    restartButton.setOutlineColor(sf::Color::White);  */
    restartButton.setPosition(178, 545); 
}

void gameOverScreen::DrawGameOver(sf::RenderWindow& window)
{
    window.draw(image);
    window.draw(restartButton);
}

sf::RectangleShape& gameOverScreen::GetRestartButton()
{
    return restartButton;
}


