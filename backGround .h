#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class backGround
{
    public:
        backGround ();

        void DrawBG (sf::RenderWindow& window);
        void speedBG(float speed);


    protected:

    private:
        int speedLim = 20;
        int speed = 0;
        int muve = 5;
        bool checkMovement = true;
        RectangleShape forTestSprite;
        Texture texture[7];
        vector <Sprite> segments;
};


