#include "menuState.h"

void menuState::handleEvent(std::vector<stateMachine*>& myState)
{
    while(window->pollEvent(event))
    {
        if(event.type == sf::Event::Closed ||
           (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
           )
            window->close();

        if(event.type == sf::Event::MouseButtonPressed &&
           event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2i mouseCoordinate(sf::Mouse::getPosition(*window));

            if(!hostState && !connectState && !howToPlayState)
                for(unsigned int i=0; i<button.size(); i++)
                {
                    if(button[i]->wasClicked(mouseCoordinate))
                    {
                        if(button[i]->getText() == "Start")
                            myState.push_back(new playState(window, data, soundOn));

                        if (button[i]->getText() == "Sunet pornit")
                        {
                            button[i]->setText("Sunet oprit");
                            soundOn = false;
                        }

                        else if (button[i]->getText() == "Sunet oprit")
                        {
                            button[i]->setText("Sunet pornit");
                            soundOn = true;
                        }

                        if(button[i]->getText() == "Cum se joaca")
                        {
                            howToPlayState = true;

                            howToButton.push_back(new simpleButton(window, 0.16*width, 0.84*height,
                                                                           0.25*width, 0.1*height,
                                                                           "< Inapoi", font, 0.026 * width,
                                                                           hoverBtnSound, clickBtnSound));
                        }

                        if(button[i]->getText() == "Inchide")
                            window->close();
                    }
                }

            if(howToPlayState)
                for(unsigned int i=0; i<howToButton.size(); i++)
                    if(howToButton[i]->wasClicked(mouseCoordinate))
                    {
                        if(howToButton[i]->getText() == "< Inapoi")
                        {
                            howToButton.clear();
                            howToPlayState = false;
                        }
                    }
        } // mouseButtonPressed

        if(event.type == sf::Event::TextEntered && connectState)
        {
            // backspace
            if(event.text.unicode == 8)
            {
                if(keyPressedIP.isEmpty() == 0)
                    keyPressedIP.erase(keyPressedIP.getSize() - 1);
            }

            else
            {
                if(keyPressedIP.getSize() < 15)
                    keyPressedIP.insert(keyPressedIP.getSize(), event.text.unicode);
            }
        }
    } // pollEvent
}

void menuState::update(std::vector<stateMachine*>& myState)
{
    if(!hostState && !connectState && !howToPlayState)
        for(unsigned int i=0; i<button.size(); i++)
            button[i]->update();

    if(howToPlayState == true)
    {
        for(unsigned int i=0; i<howToButton.size(); i++)
            howToButton[i]->update();
    }

    mouseSprite.setPosition(sf::Mouse::getPosition(*window).x-0.5*mouseSprite.getGlobalBounds().width,
                            sf::Mouse::getPosition(*window).y-0.5*mouseSprite.getGlobalBounds().height);
}

void menuState::render()
{
    window->draw(backgroundSprite);

    sf::RectangleShape rectangleForLogo(sf::Vector2f(width, 0.05*height + logoText.getGlobalBounds().height));
    rectangleForLogo.setPosition(0, 0);
    rectangleForLogo.setFillColor(sf::Color(0, 0, 0, 120));
    window->draw(rectangleForLogo);
    window->draw(logoText);
    window->draw(logoText2);

    if(!hostState && !connectState && !howToPlayState)
        for(unsigned int i=0; i<button.size(); i++)
            button[i]->render();

    if(howToPlayState == true)
    {
        sf::RectangleShape rectangle(sf::Vector2f(0.7*width, 0.65*height));
        rectangle.setPosition(0.15*width, 0.3*height);
        rectangle.setFillColor(sf::Color(0, 0, 0, 100));
        window->draw(rectangle);

        outtextxy(0.2*width, 0.35*height, "W", sf::Color(200,0,0), 0.026 * width);
        outtextxy(0.2*width, 0.35*height, "    - Misca-te in sus", sf::Color(240, 240, 240), 0.026 * width);
        outtextxy(0.42*width, 0.35*height, "A", sf::Color(200,0,0), 0.026 * width);
        outtextxy(0.42*width, 0.35*height, "    - Misca-te in stanga", sf::Color(240, 240, 240), 0.026 * width);
        outtextxy(0.2*width, 0.45*height, "S", sf::Color(200,0,0), 0.026 * width);
        outtextxy(0.2*width, 0.45*height, "   - Misca-te in jos", sf::Color(240, 240, 240), 0.026 * width);
        outtextxy(0.42*width, 0.45*height, "D", sf::Color(200,0,0), 0.026 * width);
        outtextxy(0.42*width, 0.45*height, "    - Misca-te in dreapta", sf::Color(240, 240, 240), 0.026 * width);
        outtextxy(0.2*width, 0.55*height, "Click stanga", sf::Color(200,0,0), 0.026 * width);
        outtextxy(0.2*width, 0.55*height, "              - Ataca", sf::Color(240, 240, 240), 0.026 * width);
        outtextxy(0.2*width, 0.65*height, "Click dreapta", sf::Color(200,0,0), 0.026 * width);
        outtextxy(0.2*width, 0.65*height, "                - Scut", sf::Color(240, 240, 240), 0.026 * width);

        for(unsigned int i=0; i<howToButton.size(); i++)
            howToButton[i]->render();
    }

    window->draw(mouseSprite);
}
