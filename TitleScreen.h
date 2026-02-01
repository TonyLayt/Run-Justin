#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;


class TitleScreen
{
    public:
        TitleScreen();
        void DrawTitle(sf::RenderWindow& window);
        Sprite GetStartButton();

    protected:

    private:
        Texture textureForTitle;
        Texture textureButton;
        Sprite imageTitle;
        Sprite startButton;

};


