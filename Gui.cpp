#include "Gui.h"

CountGui::CountGui()
{
    textureCount.loadFromFile("img/GUI/numbs.png"); 
}

void CountGui::setKills(int kills)
{
	kills_count = kills;

    str = std::to_string(kills_count);

    for (int strCount = 0; strCount < str.size(); strCount++) {
        
        int digit = str[strCount] - '0';

        Sprite spriteCount;
        spriteCount.setTexture(textureCount);
        spriteCount.setTextureRect(IntRect(digit * 157 + 64, 364, 157, 210));

        spriteCount.setPosition(0, 0);
        spriteCounts.push_back(spriteCount);
    }
}

void CountGui::drawGui(sf::RenderWindow &window)
{
    for (auto& CountKills : spriteCounts) {
        window.draw(CountKills);
    }

}
