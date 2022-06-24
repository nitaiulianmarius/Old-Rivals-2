#ifndef PLAYER_H
#define PLAYER_H

#include "SFML/Graphics.hpp"
#include "dataManager.h"

class Player
{
    sf::Clock frameClock;
    sf::Time frameTime;
    sf::RenderWindow *window;
    dataManager *data;
    Animation walkingAnimationDown;
    Animation walkingAnimationLeft;
    Animation walkingAnimationRight;
    Animation walkingAnimationUp;
    Animation loseSprite;
    Animation winSprite;
    Animation* currentAnimation;
    AnimatedSprite animatedSprite;
    float speed;
    float health;
    bool noKeyWasPressed;
    int width, height;

public:
    Player(){};

    Player(sf::RenderWindow *_window, dataManager *_data)
    {
        window = _window;
        data = _data;

        width = window->getSize().x;
        height = window->getSize().y;

        walkingAnimationDown    = data->animation[WALKINGANIMATIONDOWN];
        walkingAnimationRight   = data->animation[WALKINGANIMATIONRIGHT];
        walkingAnimationLeft    = data->animation[WALKINGANIMATIONLEFT];
        walkingAnimationUp      = data->animation[WALKINGANIMATIONUP];
        winSprite               = data->animation[WINSPRITE];
        loseSprite              = data->animation[LOSESPRITE];
        currentAnimation        = &walkingAnimationDown;
        animatedSprite          = data->animatedSprite[PLAYERANIMATEDSPRITE];

        speed = 0.2 * width;
        health = 100;
        noKeyWasPressed = true;
    };

    void update(bool);
    void render();
    void winImage();
    void setHealth(float h);
    float getHealth();
    sf::FloatRect getSpriteBounds();
    sf::Vector2f getPosition();

};
#endif // PLAYER_H
