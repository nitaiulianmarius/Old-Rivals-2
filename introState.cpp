#include "introState.h"

void introState::handleEvent(std::vector<stateMachine*>& myState)
{
    while(window->pollEvent(event))
    {
        if(event.type == sf::Event::Closed ||
           (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
           )
            window->close();

        if(event.type == sf::Event::KeyPressed &&
           event.key.code == sf::Keyboard::Space &&
           strcmp(loadingString, "Press 'space' to continue") == 0)
           {
                myState.push_back(new menuState(window, data));
                font.~Font();
                logoFont.~Font();
           }
    }
}

void introState::update(std::vector<stateMachine*>& myState)
{
    if(rendered == true && data == nullptr && threadNotRunning)
        startLoadindThread.launch();

    if(data != nullptr)
        if(data->isReady())
        {
            strcpy(loadingString, "Press 'space' to continue");
        }
}

void introState::render()
{
    window->draw(backgroundSprite);
    window->draw(logoText);
    window->draw(logoText2);

    outtextxy(0.17*width, 0.35*height,
              "I used the SFML C++ graphics library to render images, manipulate the game window and events", sf::Color(240, 240, 240), 0.019 * width);
    outtextxy(0.13*width, 0.4*height,
              "There are 2 players who are in a room but can not see each other. Using mouse events they send projectiles",
              sf::Color(240, 240, 240), 0.019 * width);
    outtextxy(0.13*width, 0.45*height,
              "to the other half of the room to destroy the opponent. If a projectile hit the margin of the arena,", sf::Color(240, 240, 240), 0.019 * width);
    outtextxy(0.13*width, 0.5*height,
              "it will lose half of its power.", sf::Color(240, 240, 240), 0.019 * width);
    outtextxy(0.38*width, 0.55*height,
              "Technologies: C++, SFML 2.5, Algebra", sf::Color(240, 240, 240), 0.019 * width);
    outtextxy(0.39*width, 0.59*height,
              "Contact: nitaiulianmarius@gmail.com", sf::Color(240, 240, 240), 0.017 * width);
    outtextxy(0.37*width, 0.62*height,
              "For educational purpose, have fun !", sf::Color(240, 240, 240), 0.021 * width);

    outtextxy(0.1*width, 0.8*height, loadingString, sf::Color(240, 240, 240), 0.024 * width);

    rendered = true;
}

void introState::startLoading()
{
    threadNotRunning = false;
    data = new dataManager(window);
}
