#include "player.h"

void Player::update(bool inPause)
{
    frameTime = frameClock.restart();
    sf::Vector2f movement(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
        animatedSprite.getPosition().y > 0.25*height &&
        !inPause)
    {
        currentAnimation = &walkingAnimationUp;
        movement.y -= speed;
        noKeyWasPressed = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
        animatedSprite.getPosition().y < 0.8*height &&
        !inPause)
    {
        currentAnimation = &walkingAnimationDown;
        movement.y += speed;
        noKeyWasPressed = false;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
       animatedSprite.getPosition().x > 0.1*width &&
        !inPause)
    {
        currentAnimation = &walkingAnimationLeft;
        movement.x -= speed;
        noKeyWasPressed = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
        animatedSprite.getPosition().x < 0.9*width &&
        !inPause)
    {
        currentAnimation = &walkingAnimationRight;
        movement.x += speed;
        noKeyWasPressed = false;
    }

    if(health <= 0)
        currentAnimation = &loseSprite;

    animatedSprite.play(*currentAnimation);
    animatedSprite.move(movement * frameTime.asSeconds());

    if (noKeyWasPressed)
        animatedSprite.stop();

    noKeyWasPressed = true;
    animatedSprite.update(frameTime);
}

void Player::render()
{
    window->draw(animatedSprite);
}

void Player::winImage()
{
    currentAnimation = &winSprite;
}

void Player::setHealth(float h)
{
    health = h;
}

float Player::getHealth()
{
    return health;
}

sf::FloatRect Player::getSpriteBounds()
{
    return animatedSprite.getGlobalBounds();
}

sf::Vector2f Player::getPosition()
{
    return animatedSprite.getPosition();
}
