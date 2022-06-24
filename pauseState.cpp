#include "pauseState.h"
#include "menuState.h"

void pauseState::handleEvent(std::vector<stateMachine*>& myState)
{
    while(window->pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            window->close();
        }

        if(event.type == sf::Event::MouseButtonPressed &&
           event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2i mouseCoordinate(sf::Mouse::getPosition(*window));

            for(unsigned int i=0; i<button.size(); i++)
            {
                if(button[i]->wasClicked(mouseCoordinate))
                {
                    if(button[i]->getText() == "Inapoi la joc")
                    {
                        stateMachine* currentState = myState[myState.size()-1];
                        myState.pop_back();
                        delete currentState;
                        break;
                    }

                    if (button[i]->getText() == "Meniu")
                    {
                        stateMachine* currentState = myState[myState.size()-1];
                        stateMachine* lastState = myState[myState.size()-2];
                        myState.pop_back();
                        myState.pop_back();
                        delete currentState;
                        delete lastState;
                        break;
                    }

                    if(button[i]->getText() == "Inchide")
                        window->close();
                }
            }
        } // mouseButtonPressed
    } // pollEvent
}

void pauseState::update(std::vector<stateMachine*>&)
{
    unsigned int numberOfButton = button.size();
    for(unsigned int i=0; i < numberOfButton; i++)
        button[i]->update();

    mouseSprite.setPosition((sf::Vector2f)sf::Mouse::getPosition(*window));
}

void pauseState::render()
{
    unsigned int numberOfButton = button.size();
    for(unsigned int i=0; i < numberOfButton; i++)
        button[i]->render();

    window->draw(logoText);
    window->draw(logoText2);

    window->draw(mouseSprite);
}
