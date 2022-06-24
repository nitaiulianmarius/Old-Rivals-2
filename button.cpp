#include "button.h"

void simpleButton::update()
{
    sf::Vector2i mouseCoordinate = sf::Mouse::getPosition(*window);

    xMouse = mouseCoordinate.x;
    yMouse = mouseCoordinate.y;

    if (x < xMouse && xMouse < x + width && y < yMouse && yMouse < y + height)
    {
        color = sf::Color(200, 0, 0);
        state = pState;
        if(soundWasPlayed == false)
        {
            hoverSound.play();
            soundWasPlayed = true;
        }
    }

    else
    {
        color = sf::Color(240, 240, 240);
        state = nState;
        if(hoverSound.getStatus() == sf::Sound::Status::Playing)
            hoverSound.stop();
        soundWasPlayed = false;
    }
}

void simpleButton::render()
{
    if(state == pState)
    {
        sf::RectangleShape rectangle(sf::Vector2f(width,height));
        rectangle.setPosition(x,y);
        rectangle.setFillColor(sf::Color(0,0,0,50));
        window->draw(rectangle);
    }

    text.setFillColor(color);
    window->draw(text);
}

bool simpleButton::wasClicked(sf::Vector2i _mP)
{
    xMouse = _mP.x;
    yMouse = _mP.y;

    if(x < xMouse && xMouse < x + width && y < yMouse && yMouse < y + height)
    {
        clickSound.play();
        Sleep(50);
        return 1;
    }
    return 0;
}

void simpleButton::setText(sf::String newText)
{
    textString = newText;
    text.setString(textString);
    text.setPosition(x+0.5*(width-text.getGlobalBounds().width), y+0.4*(height-text.getGlobalBounds().height));
}

sf::String simpleButton::getText()
{
    return textString;
}
