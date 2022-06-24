#ifndef BUTTON_H
#define BUTTON_H

#include "windows.h"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#define nState 0
#define pState 1

class simpleButton
{
    sf::RenderWindow *window;
    sf::Font font;
    sf::Text text;
    sf::Color color;
    sf::String textString;
    sf::Sound hoverSound;
    sf::Sound clickSound;
    int x, y;
    int xMouse, yMouse;
    int width, height;
    int state;
    int size;
    bool soundWasPlayed;

public:

    simpleButton(sf::RenderWindow *_window,
                 int _x, int _y,
                 int _width, int _height,
                 sf::String _text, sf::Font _font, int _size,
                 sf::Sound _hoverSound, sf::Sound _clickSound):
    window(_window),
    font(_font),
    textString(_text),
    x(_x),
    y(_y),
    width(_width),
    height(_height),
    size(_size)
    {
        text.setFont(font);
        text.setString(textString);
        text.setCharacterSize(size);
        text.setPosition(x+0.5*(width-text.getGlobalBounds().width), y+0.4*(height-text.getGlobalBounds().height));
        hoverSound = _hoverSound;
        clickSound = _clickSound;
        soundWasPlayed = false;
    };

    void update();
    void render();
    bool wasClicked(sf::Vector2i);
    void setText(sf::String);
    sf::String getText();
};

#endif // BUTTON_H
