#include "Gui.h"

CountGui::CountGui()
{
    textureCount.loadFromFile("img/GUI/numbs.png");

	textureZombieHeadIco.loadFromFile("img/GUI/zombie_head_ico.png");
    spriteZombieHeadIco.setTexture(textureZombieHeadIco);
	spriteZombieHeadIco.setPosition(0, 0);
    spriteZombieHeadIco.setScale(0.1f, 0.1f);

    spriteCounts.reserve(10);

    for (int numCount = 0; numCount < 10; numCount++) {

        Sprite spriteCount;
        spriteCount.setTexture(textureCount);
        spriteCount.setTextureRect(IntRect(advance[numCount], 400, 146, 201));
        spriteCount.setPosition(0, 0);
        spriteCount.setScale(0.5f, 0.5f);

        spriteCounts.push_back(spriteCount);
    }
}

void CountGui::setKills(int kills)
{
	kills_count = kills;

    str = std::to_string(kills_count);

    numCounts.clear();
    numCounts.reserve(str.size());

    float x = posX;

    for (int strCount = 0; strCount < str.size(); strCount++) {
        
        int digit = str[strCount] - '0';

        if (digit < 0 || digit > 9) continue;

        sf::Sprite s = spriteCounts[digit];
        s.setPosition(x, posY);

        numCounts.push_back(s);

        x += spacing;
    }
}

void CountGui::drawGui(sf::RenderWindow &window)
{
    for (auto& CountKills : numCounts) {
        window.draw(CountKills);
    }
    window.draw(spriteZombieHeadIco);
}
