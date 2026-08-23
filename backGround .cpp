#include "backGround .h"

backGround ::backGround()
{
        string image[4] = {"img/backGroundSprite/BG_origin.png", "img/backGroundSprite/segment_3.png", "img/backGroundSprite/segment_2.png",
                           "img/backGroundSprite/segment_1.png"};

        int countCopie = 1;

        forTestSprite.setSize(sf::Vector2f(960, 640)); // обов’язково вказати розмір
        forTestSprite.setFillColor(sf::Color::White);
        forTestSprite.setPosition(-200, 0);

        //    mainBackgraund
        texture[0].loadFromFile(image[0]);
        Sprite sprite;
        sprite.setTexture(texture[0]);
        sprite.scale(0.39f, 0.39f);
        segments.push_back(sprite);
        //    mainBackgraund

        for (int num = 1; num < 4; num++)
        {
                texture[num].loadFromFile(image[countCopie]);
                for (int iteratNum = 0; iteratNum < 2; iteratNum++)
                {
                        Sprite sprite;
                        sprite.setTexture(texture[countCopie]);
                        sprite.scale(0.52f, 0.56f);
                        sprite.setPosition(iteratNum * sprite.getGlobalBounds().width - 50, 0);
                        segments.push_back(sprite);
                        cout << "WADFFSG" << countCopie << endl;
                }
                countCopie++;
        }
}

void backGround::speedBG(float speed)
{
        if (speed > speedLim)
        {
			speedLim += 20;
			muve += 1;
        }
        segments[1].move(-muve + 4, 0); // 4
        segments[2].move(-muve + 4, 0);

        segments[3].move(-muve + 3, 0); // 3
        segments[4].move(-muve + 3, 0);

        segments[5].move(-muve + 1, 0); // 1
        segments[6].move(-muve + 1, 0);

        if (segments[5].getPosition().x + segments[5].getGlobalBounds().width < -50 && checkMovement)
        {
                cout << "Segment 5 moved" << endl;
                // Ставим сегмент 5 СПРАВА от сегмента 6
                segments[5].setPosition(segments[6].getPosition().x + segments[6].getGlobalBounds().width, 0);
                checkMovement = false;
        }
        if (segments[6].getPosition().x + segments[6].getGlobalBounds().width < -50 && checkMovement)
        {
                cout << "Segment 6 moved" << endl;
                // Ставим сегмент 6 СПРАВА от сегмента 5
                segments[6].setPosition(segments[5].getPosition().x + segments[5].getGlobalBounds().width, 0);
                checkMovement = false;
        }

        
        if (segments[3].getPosition().x + segments[3].getGlobalBounds().width < -50 && checkMovement)
        {

                cout << "<00000<" << endl;
                segments[3].setPosition(segments[4].getPosition().x + segments[4].getGlobalBounds().width, 0);
                checkMovement = false;
        }
        if (segments[4].getPosition().x + segments[4].getGlobalBounds().width < -50 && checkMovement)
        {

                cout << "<00000<" << endl;
                segments[4].setPosition(segments[3].getPosition().x + segments[3].getGlobalBounds().width, 0);
                checkMovement = false;
        }

        if (segments[1].getPosition().x + segments[1].getGlobalBounds().width < -50 && checkMovement)
        {

                cout << "<00000<" << endl;
                segments[1].setPosition(segments[2].getPosition().x + segments[2].getGlobalBounds().width, 0);
                checkMovement = false;
        }
        if (segments[2].getPosition().x + segments[2].getGlobalBounds().width < -50 && checkMovement)
        {

                cout << "<00000<" << endl;
                segments[2].setPosition(segments[1].getPosition().x + segments[1].getGlobalBounds().width, 0);
                checkMovement = false;
        }

        checkMovement = true;
}

void backGround ::DrawBG(sf::RenderWindow &window)
{

        // window.draw(forTestSprite);

        for (auto &item : segments)
        {
                window.draw(item);
        }
}
