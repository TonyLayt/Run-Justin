#include "gameOverScreen.h"

gameOverScreen::gameOverScreen()
{
    textureForTitle.loadFromFile("img/GameOver/gameOverScreen.png");
    image.setTexture(textureForTitle);
    image.scale(0.66f, 0.66f);
    image.setPosition(-50, 0);

	textureForTitleKill_st.loadFromFile("img/GameOver/kill_st.png");
	imageKill_st.setTexture(textureForTitleKill_st);
    imageKill_st.scale(0.4f, 0.4f);
    imageKill_st.setPosition(140, 80);

    // Простая белая кнопка
    restartButton.setSize(sf::Vector2f(200, 60));  
    restartButton.setFillColor(sf::Color::Transparent);
    /*restartButton.setOutlineThickness(3);
    restartButton.setOutlineColor(sf::Color::White);  */
    restartButton.setPosition(178, 545);

    // Простая белая кнопка
    exitButton.setSize(sf::Vector2f(200, 60));
    exitButton.setFillColor(sf::Color::Transparent);
    /*exitButton.setOutlineThickness(3);
    exitButton.setOutlineColor(sf::Color::White); */ 
    exitButton.setPosition(530, 545);

    textureCount_st.loadFromFile("img/GameOver/numbs_st.png");
    
    spriteCounts_st.reserve(10);

    for (int numCount_st = 0; numCount_st < 10; numCount_st++) {

        sf::Sprite AddSpriteCount_st;
        AddSpriteCount_st.setTexture(textureCount_st);
        AddSpriteCount_st.setTextureRect(sf::IntRect(advance[numCount_st], 400, 146, 201));
        AddSpriteCount_st.setPosition(0, 0);
        AddSpriteCount_st.setScale(0.5f, 0.5f);

        spriteCounts_st.push_back(AddSpriteCount_st);
    }
}

void gameOverScreen::setKillsST(int killsST)
{
    kills_count_st = killsST;

    str_st = std::to_string(kills_count_st);

    numCountsST.clear();
    numCountsST.reserve(str_st.size());

   if (kills_count_st >= shiftNumForKillST){
       shiftNumForKillST *= 10;
	   posX -= spacing/2;
   }

    float x = posX;

    for (int strCountST = 0; strCountST < str_st.size(); strCountST++) {

        int digitST = str_st[strCountST] - '0';

        if (digitST < 0 || digitST > 9) continue;

        sf::Sprite s = spriteCounts_st[digitST];
        s.setPosition(x, posY);

        numCountsST.push_back(s);

        x += spacing;
    }
}

void gameOverScreen::DrawGameOver(sf::RenderWindow& window)
{
    window.draw(image);
    window.draw(imageKill_st);

    for (auto& CountKillsST : numCountsST) {
        window.draw(CountKillsST);
    }
}

sf::RectangleShape& gameOverScreen::GetRestartButton()
{
    return restartButton;
}

sf::RectangleShape& gameOverScreen::GetExitButton()
{
	return exitButton;
}


