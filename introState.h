/*
Incarca si asteapta afisarea datelor pe ecran pentru intro (rendered = true) iar apoi se asteapta
 incarcarea tuturor datelor necesare pe toata durata de executie a jocului
Face legatura cu menuState
*/

#ifndef INTROSTATE_H
#define INTROSTATE_H

#include "SFML/Graphics.hpp"
#include "stateMachine.h"
#include "menuState.h"
#include "dataManager.h"

class introState:public stateMachine
{
    char loadingString[32];
    sf::Thread startLoadindThread;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    bool rendered;
    bool threadNotRunning;

public:
    introState(sf::RenderWindow *_window):startLoadindThread(&introState::startLoading, this)
    {
        window = _window;
        window->setMouseCursorVisible(false);

        width = window->getSize().x;
        height = window->getSize().y;

        backgroundTexture.loadFromFile("data/image/introBackground.jpg");
        backgroundSprite.setTexture(backgroundTexture);
        backgroundSprite.setScale(width/backgroundSprite.getGlobalBounds().width,
                                  height/backgroundSprite.getGlobalBounds().height);


        strcpy(loadingString, "loading...");
        rendered = false;
        threadNotRunning = true;

        font.loadFromFile("data/font/Rudiment.ttf");
        text.setFont(font);

        logoFont.loadFromFile("data/font/Bleeding_Cowboys.ttf");
        logoText.setFont(logoFont);
        logoText2.setFont(logoFont);

        logoText.setString("Old Rivals 2");

        logoText.setCharacterSize(0.04 * width);
        logoText2.setCharacterSize(0.02 * width);

        logoText.setFillColor(sf::Color(200, 0, 0));
        logoText2.setFillColor(sf::Color::White);

        logoText.setPosition (0.5*(width-logoText.getGlobalBounds().width), 0.05*height);
        logoText2.setPosition(0.5*(width-logoText2.getGlobalBounds().width), 0.12*height);

        data = nullptr;
    };

    void handleEvent(std::vector<stateMachine*>&);
    void update(std::vector<stateMachine*>&);
    void render();
    void startLoading();
};

#endif // INTROSTATE_H
