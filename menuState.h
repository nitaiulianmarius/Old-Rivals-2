#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "windows.h"
#include "stateMachine.h"
#include "playState.h"
#include "button.h"

class menuState:public stateMachine
{
    bool howToPlayState = false;
    bool hostState = false;
    bool connectState = false;
    bool soundOn = true;
    std::vector<simpleButton*> button;
    std::vector<simpleButton*> howToButton;
    sf::Sound hoverBtnSound;
    sf::Sound clickBtnSound;
    sf::Sprite backgroundSprite;
    sf::String globalIP;
    sf::String localIP;
    sf::String keyPressedIP;
    sf::Thread *waitServerThread = nullptr;
    sf::Thread *waitClientThread = nullptr;

public:
    menuState(sf::RenderWindow *_window, dataManager *_data)
    {
        window = _window;
        data = _data;
        window->setMouseCursorVisible(false);

        width = window->getSize().x;
        height = window->getSize().y;

        font = data->font;
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

        backgroundSprite = data->sprite[MENUBACKGROUND];
        mouseSprite = data->sprite[MOUSE];

        hoverBtnSound = data->sound[HOVERBTNSOUND];
        clickBtnSound = data->sound[CLICKBTNSOUND];
        button.push_back(new simpleButton(window, 0.35*width, 0.4*height,
                                                  0.25*width, 0.1*height,
                                                  "Start", font, 0.026 * width,
                                                  hoverBtnSound, clickBtnSound));
        button.push_back(new simpleButton(window, 0.35*width, 0.5*height,
                                                  0.25*width, 0.1*height,
                                                  "Sunet pornit", font, 0.026 * width,
                                                  hoverBtnSound, clickBtnSound));
        button.push_back(new simpleButton(window, 0.35*width, 0.6*height,
                                                  0.25*width, 0.1*height,
                                                  "Cum se joaca", font, 0.026 * width,
                                                  hoverBtnSound, clickBtnSound));
        button.push_back(new simpleButton(window, 0.35*width, 0.7*height,
                                                  0.25*width, 0.1*height,
                                                  "Inchide", font, 0.026 * width,
                                                  hoverBtnSound, clickBtnSound));
    };

    void handleEvent(std::vector<stateMachine*>&);
    void update(std::vector<stateMachine*>&);
    void render();
};

#endif // MENUSTATE_H
