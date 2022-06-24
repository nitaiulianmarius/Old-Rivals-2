#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include <vector>
#include "stateMachine.h"
#include "button.h"

class pauseState:public stateMachine
{
    std::vector<simpleButton*> button;
    sf::Sound hoverBtnSound;
    sf::Sound clickBtnSound;

public:
    pauseState(sf::RenderWindow *_window, dataManager *_data)
    {
        window = _window;
        data = _data;
        window->setMouseCursorVisible(false);

        width = window->getSize().x;
        height = window->getSize().y;

        font = data->font;
        text.setFont(font);

        mouseSprite = data->sprite[MOUSE];


        hoverBtnSound = data->sound[HOVERBTNSOUND];
        clickBtnSound = data->sound[CLICKBTNSOUND];
        button.push_back(new simpleButton(window, 0.15*width, 0.7*height,
                                                  0.2*width, 0.1*height,
                                                  "Inapoi la joc", font, 0.026 * width,
                                                  hoverBtnSound, clickBtnSound));
        button.push_back(new simpleButton(window, 0.4*width, 0.7*height,
                                                  0.2*width, 0.1*height,
                                                  "Meniu", font, 0.026 * width,
                                                  hoverBtnSound, clickBtnSound));
        button.push_back(new simpleButton(window, 0.65*width, 0.7*height,
                                                  0.2*width, 0.1*height,
                                                  "Inchide", font, 0.026 * width,
                                                  hoverBtnSound, clickBtnSound));

        logoFont.loadFromFile("data/font/Bleeding_Cowboys.ttf");
        logoText.setFont(logoFont);
        logoText2.setFont(logoFont);

        logoText.setString("Old Rivals 2");

        logoText.setCharacterSize(0.04 * width);
        logoText2.setCharacterSize(0.02 * width);

        logoText.setFillColor(sf::Color(200, 0, 0));
        logoText2.setFillColor(sf::Color::White);

        logoText.setPosition (0.5*(width-logoText.getGlobalBounds().width), 0.45*height);
        logoText2.setPosition(0.5*(width-logoText2.getGlobalBounds().width), 0.52*height);
    };

    void handleEvent(std::vector<stateMachine*>&);
    void update(std::vector<stateMachine*>&);
    void render();
};

#endif // PAUSESTATE_H
