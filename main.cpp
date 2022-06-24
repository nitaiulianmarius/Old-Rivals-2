#include <SFML/Graphics.hpp>
#include <vector>
#include "introState.h"

#define WINDOW_NAME "Rivalii"
#define FPS_MAX 60
#define VSYNC_ENABLE true

int main()
{
    sf::RenderWindow *window = nullptr;
    std::vector<stateMachine*> myState;
    bool altTabbed = false;

    window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), WINDOW_NAME, sf::Style::Fullscreen);
    window->setFramerateLimit(FPS_MAX);
    window->setVerticalSyncEnabled(VSYNC_ENABLE);
    myState.push_back(new introState(window));

    while(window->isOpen())
    {
        if (altTabbed && window->hasFocus())
        {
            window->create(sf::VideoMode::getDesktopMode(), WINDOW_NAME, sf::Style::Fullscreen);
            window->setMouseCursorVisible(false);
            altTabbed = false;
        }

        else if (!altTabbed &&
                 sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) &&
                 sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
        {
            window->create(sf::VideoMode(0, 0), WINDOW_NAME, sf::Style::Default);
            altTabbed = true;
        }

        myState.back()->handleEvent(myState);
        myState.back()->update(myState);
        window->clear();
        myState.back()->render();
        window->display();
    }
}
