/*
La inceputul executiei programului incarc toate datele necesare rularii acestuia
Prin clasa dataManager retin permanent un pointer catre adresa de memorie a fiecarei data, astfel nu mai sunt nevoit
 sa dealoc memoria la terminarea unei anumite stari de joc, iar mai apoi sa o realoc
 (de la startGameState->menuState->startGameState si tot asa)
Aceasta varianta de alocare a memoriei este eficienta pentru jocuri care ocupa, in general, putina memorie !!
*/

#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Animation.h"
#include "AnimatedSprite.h"

// sprite
#define SPRITE_MAX_NUMBER 13
#define FONT 0
#define MENUBACKGROUND 1
#define GAMEBACKGROUND 2
#define INTROBACKGROUND 3
#define PLAYERONSHIELD 4
#define PLAYER 5
#define MOUSE 6
#define SHIELD 7
#define HEART 8
#define FIRE 9
#define POWER 10
#define COOLDOWN 11
#define RIVALFIRE 12

// animation
#define ANIMATION_MAX_NUMBER 8
#define WALKINGANIMATIONDOWN 0
#define WALKINGANIMATIONLEFT 1
#define WALKINGANIMATIONRIGHT 2
#define WALKINGANIMATIONUP 3
#define LOSESPRITE 4
#define WINSPRITE 5
#define FIREANIMATION 6
#define RIVALANIMATION 7

// animated sprite
#define ANIMATED_SPRITE_MAX_NUMBER 3
#define PLAYERANIMATEDSPRITE 0
#define FIREANIMATEDSPRITE 1
#define RIVALANIMATEDSPRITE 2

// shape
#define SHAPE_MAX_NUMBER 9
#define LIFESHAPE 0
#define RIVALLIFESHAPE 1
#define FIRESHAPE 2
#define POWERSHAPE 3
#define SCORSHAPE 4
#define LIFERECTANGLE 5
#define RIVALLIFERECTANGLE 6
#define FIRERECTANGLE 7
#define POWERRECTANGLE 8

// sounds
#define SOUND_MAX_NUMBER 4
#define HOVERBTNSOUND 0
#define CLICKBTNSOUND 1
#define FIRESOUND 2
#define EXPLOSIONSOUND 3

class dataManager
{
public:
    sf::Font            font;
    sf::Sprite          sprite[SPRITE_MAX_NUMBER];
    sf::Texture         texture[SPRITE_MAX_NUMBER];
    Animation           animation[ANIMATION_MAX_NUMBER];
    AnimatedSprite      animatedSprite[ANIMATED_SPRITE_MAX_NUMBER];
    sf::RectangleShape  shape[SHAPE_MAX_NUMBER];
    sf::ConvexShape     mainShape;
    sf::SoundBuffer     soundBuffer[SOUND_MAX_NUMBER];
    sf::Sound           sound[SOUND_MAX_NUMBER];
    sf::Music           backgroungMusic;
    sf::Music           winSound;
    sf::Music           loseSound;
    int                 width;
    int                 height;
    bool                loaded;

    dataManager(sf::RenderWindow *window)
    {
        loaded = false;

        width = window->getSize().x;
        height = window->getSize().y;

        font.loadFromFile("data/font/Rudiment.ttf");

        texture[MENUBACKGROUND]     .loadFromFile("data/image/menuBackground.jpg");
        sprite[MENUBACKGROUND]      .setTexture(texture[MENUBACKGROUND]);
        sprite[MENUBACKGROUND]      .setScale(width/sprite[MENUBACKGROUND].getGlobalBounds().width,
                                              height/sprite[MENUBACKGROUND].getGlobalBounds().height);
        texture[GAMEBACKGROUND]     .loadFromFile("data/image/gameBackground.png");
        sprite[GAMEBACKGROUND]      .setTexture(texture[GAMEBACKGROUND]);
        sprite[GAMEBACKGROUND]      .setScale(width/sprite[GAMEBACKGROUND].getGlobalBounds().width,
                                              0.9*height/sprite[GAMEBACKGROUND].getGlobalBounds().height);
        sprite[GAMEBACKGROUND]      .setPosition(0, 0.1*height);
        texture[PLAYERONSHIELD]     .loadFromFile("data/image/shieldOn.png");
        sprite[PLAYERONSHIELD]      .setTexture(texture[PLAYERONSHIELD]);
        sprite[PLAYERONSHIELD]      .setOrigin(0.5*sprite[PLAYERONSHIELD].getGlobalBounds().width,
                                               0.5*sprite[PLAYERONSHIELD].getGlobalBounds().height);
        sprite[PLAYERONSHIELD]      .setScale(0.06*width/148,
                                              0.14*height/192);
        texture[PLAYER]             .loadFromFile("data/image/player.png");
        texture[MOUSE]              .loadFromFile("data/image/mouse.png");
        sprite[MOUSE]               .setTexture(texture[MOUSE]);
        sprite[MOUSE]               .setOrigin(0.5*sprite[MOUSE].getGlobalBounds().width,
                                               0.5*sprite[MOUSE].getGlobalBounds().height);
        sprite[MOUSE]               .setScale(0.018 * width/sprite[MOUSE].getGlobalBounds().width,
                                              0.018 * width/sprite[MOUSE].getGlobalBounds().height);
        texture[SHIELD]             .loadFromFile("data/image/shield.png");
        sprite[SHIELD]              .setTexture(texture[SHIELD]);
        sprite[SHIELD]              .setScale(0.054*width/sprite[SHIELD].getGlobalBounds().width,
                                              0.1*height/sprite[SHIELD].getGlobalBounds().height);
        sprite[SHIELD]              .setPosition(0.92*width, 0.4*height);
        texture[HEART]              .loadFromFile("data/image/heart.png");
        sprite[HEART]               .setTexture(texture[HEART]);
        sprite[HEART]               .setScale(0.04*width/sprite[HEART].getGlobalBounds().width,
                                              0.04*height/sprite[HEART].getGlobalBounds().height);
        texture[COOLDOWN]           .loadFromFile("data/image/cooldown.png");
        sprite[COOLDOWN]            .setTexture(texture[COOLDOWN]);
        sprite[COOLDOWN]            .setScale(0.02*width/sprite[COOLDOWN].getGlobalBounds().width,
                                              0.04*height/sprite[COOLDOWN].getGlobalBounds().height);
        sprite[COOLDOWN]            .setPosition(0.2*width, 0.02*height);
        texture[POWER]              .loadFromFile("data/image/power.png");
        sprite[POWER]               .setTexture(texture[POWER]);
        sprite[POWER]               .setScale(0.02*width/sprite[POWER].getGlobalBounds().width,
                                              0.04*height/sprite[POWER].getGlobalBounds().height);
        sprite[POWER]               .setPosition(0.36*width, 0.014*height);
        texture[FIRE]               .loadFromFile("data/image/fire.png");
        sprite[FIRE]                .setTexture(texture[FIRE]);
        sprite[FIRE]                .setOrigin(0.5*sprite[FIRE].getGlobalBounds().width,
                                               0.5*sprite[FIRE].getGlobalBounds().height);
        texture[RIVALFIRE]          .loadFromFile("data/image/rivalFire.png");
        sprite[RIVALFIRE]           .setTexture(texture[RIVALFIRE]);
        sprite[RIVALFIRE]           .setOrigin(0.5*sprite[RIVALFIRE].getGlobalBounds().width,
                                               0.5*sprite[RIVALFIRE].getGlobalBounds().height);

        animation[WALKINGANIMATIONDOWN].setSpriteSheet(texture[PLAYER]);
        animation[WALKINGANIMATIONDOWN].addFrame(sf::IntRect(1, 1, 27, 34));
        animation[WALKINGANIMATIONDOWN].addFrame(sf::IntRect(33, 1, 27, 34));
        animation[WALKINGANIMATIONDOWN].addFrame(sf::IntRect(65, 1, 27, 34));
        animation[WALKINGANIMATIONDOWN].addFrame(sf::IntRect(97, 1, 27, 36));
        animation[WALKINGANIMATIONDOWN].addFrame(sf::IntRect(129, 1, 27, 34));
        animation[WALKINGANIMATIONDOWN].addFrame(sf::IntRect(161, 1, 27, 34));
        animation[WALKINGANIMATIONDOWN].addFrame(sf::IntRect(193, 1, 27, 34));
        animation[WALKINGANIMATIONDOWN].addFrame(sf::IntRect(224, 1, 27, 34));
        animation[WALKINGANIMATIONDOWN].addFrame(sf::IntRect(257, 1, 27, 36));
        animation[WALKINGANIMATIONDOWN].addFrame(sf::IntRect(289, 1, 27, 35));
        animation[WALKINGANIMATIONRIGHT].setSpriteSheet(texture[PLAYER]);
        animation[WALKINGANIMATIONRIGHT].addFrame(sf::IntRect(1, 41, 27, 34));
        animation[WALKINGANIMATIONRIGHT].addFrame(sf::IntRect(33, 41, 27, 34));
        animation[WALKINGANIMATIONRIGHT].addFrame(sf::IntRect(65, 41, 27, 34));
        animation[WALKINGANIMATIONRIGHT].addFrame(sf::IntRect(97, 41, 27, 34));
        animation[WALKINGANIMATIONRIGHT].addFrame(sf::IntRect(129, 41, 27, 34));
        animation[WALKINGANIMATIONRIGHT].addFrame(sf::IntRect(161, 41, 27, 34));
        animation[WALKINGANIMATIONRIGHT].addFrame(sf::IntRect(193, 41, 27, 34));
        animation[WALKINGANIMATIONRIGHT].addFrame(sf::IntRect(224, 41, 27, 34));
        animation[WALKINGANIMATIONRIGHT].addFrame(sf::IntRect(257, 41, 27, 34));
        animation[WALKINGANIMATIONRIGHT].addFrame(sf::IntRect(289, 41, 27, 34));
        animation[WALKINGANIMATIONLEFT].setSpriteSheet(texture[PLAYER]);
        animation[WALKINGANIMATIONLEFT].addFrame(sf::IntRect(289, 79, 27, 34));
        animation[WALKINGANIMATIONLEFT].addFrame(sf::IntRect(257, 79, 27, 34));
        animation[WALKINGANIMATIONLEFT].addFrame(sf::IntRect(224, 79, 27, 34));
        animation[WALKINGANIMATIONLEFT].addFrame(sf::IntRect(193, 79, 27, 34));
        animation[WALKINGANIMATIONLEFT].addFrame(sf::IntRect(161, 79, 27, 34));
        animation[WALKINGANIMATIONLEFT].addFrame(sf::IntRect(129, 79, 27, 34));
        animation[WALKINGANIMATIONLEFT].addFrame(sf::IntRect(97, 79, 27, 34));
        animation[WALKINGANIMATIONLEFT].addFrame(sf::IntRect(65, 79, 27, 34));
        animation[WALKINGANIMATIONLEFT].addFrame(sf::IntRect(33, 79, 27, 34));
        animation[WALKINGANIMATIONLEFT].addFrame(sf::IntRect(1, 79, 27, 34));
        animation[WALKINGANIMATIONUP].setSpriteSheet(texture[PLAYER]);
        animation[WALKINGANIMATIONUP].addFrame(sf::IntRect(289, 1, 27, 35));
        animation[WALKINGANIMATIONUP].addFrame(sf::IntRect(257, 1, 27, 36));
        animation[WALKINGANIMATIONUP].addFrame(sf::IntRect(224, 1, 27, 34));
        animation[WALKINGANIMATIONUP].addFrame(sf::IntRect(193, 1, 27, 34));
        animation[WALKINGANIMATIONUP].addFrame(sf::IntRect(161, 1, 27, 34));
        animation[WALKINGANIMATIONUP].addFrame(sf::IntRect(129, 1, 27, 34));
        animation[WALKINGANIMATIONUP].addFrame(sf::IntRect(97, 1, 27, 36));
        animation[WALKINGANIMATIONUP].addFrame(sf::IntRect(65, 1, 27, 34));
        animation[WALKINGANIMATIONUP].addFrame(sf::IntRect(33, 1, 27, 34));
        animation[WALKINGANIMATIONUP].addFrame(sf::IntRect(1, 1, 27, 34));
        animation[WINSPRITE].setSpriteSheet(texture[PLAYER]);
        animation[WINSPRITE].addFrame(sf::IntRect(1, 119, 27, 28));
        animation[LOSESPRITE].setSpriteSheet(texture[PLAYER]);
        animation[LOSESPRITE].addFrame(sf::IntRect(39, 119, 33, 28));
        animation[FIREANIMATION].setSpriteSheet(texture[FIRE]);
        animation[FIREANIMATION].addFrame(sf::IntRect(187, 84, 240, 370));
        animation[FIREANIMATION].addFrame(sf::IntRect(787, 86, 240, 370));
        animation[FIREANIMATION].addFrame(sf::IntRect(1385, 87, 240, 370));
        animation[FIREANIMATION].addFrame(sf::IntRect(1987, 85, 240, 370));
        animation[FIREANIMATION].addFrame(sf::IntRect(2582, 85, 240, 370));
        animation[FIREANIMATION].addFrame(sf::IntRect(3185, 86, 340, 370));
        animation[FIREANIMATION].addFrame(sf::IntRect(3787, 87, 240, 370));
        animation[FIREANIMATION].addFrame(sf::IntRect(4390, 85, 240, 370));
        animation[RIVALANIMATION].setSpriteSheet(texture[RIVALFIRE]);
        animation[RIVALANIMATION].addFrame(sf::IntRect(187, 84, 240, 370));
        animation[RIVALANIMATION].addFrame(sf::IntRect(787, 86, 240, 370));
        animation[RIVALANIMATION].addFrame(sf::IntRect(1385, 87, 240, 370));
        animation[RIVALANIMATION].addFrame(sf::IntRect(1987, 85, 240, 370));
        animation[RIVALANIMATION].addFrame(sf::IntRect(2582, 85, 240, 370));
        animation[RIVALANIMATION].addFrame(sf::IntRect(3185, 86, 340, 370));
        animation[RIVALANIMATION].addFrame(sf::IntRect(3787, 87, 240, 370));
        animation[RIVALANIMATION].addFrame(sf::IntRect(4390, 85, 240, 370));

        animatedSprite[PLAYERANIMATEDSPRITE] = AnimatedSprite(sf::seconds(0.08), true, false);
        animatedSprite[PLAYERANIMATEDSPRITE].setOrigin(0.5*animation[WALKINGANIMATIONDOWN].getFrame(0).width,
                                                       0.5*animation[WALKINGANIMATIONDOWN].getFrame(0).height);
        animatedSprite[PLAYERANIMATEDSPRITE].setPosition(sf::Vector2f(0.5*width, 0.5*height));
        animatedSprite[PLAYERANIMATEDSPRITE].setScale(0.002*width, 0.0037*height);
        animatedSprite[FIREANIMATEDSPRITE] = AnimatedSprite(sf::seconds(0.05), true, false);
        animatedSprite[FIREANIMATEDSPRITE].setOrigin(0.5*animation[FIREANIMATION].getFrame(0).width,
                                                     0.5*animation[FIREANIMATION].getFrame(0).height);
        animatedSprite[FIREANIMATEDSPRITE].setScale(0.0005*width, 0.00097*height);
        animatedSprite[RIVALANIMATEDSPRITE] = AnimatedSprite(sf::seconds(0.05), true, false);
        animatedSprite[RIVALANIMATEDSPRITE].setOrigin(0.5*animation[RIVALANIMATION].getFrame(0).width,
                                                      0.5*animation[RIVALANIMATION].getFrame(0).height);
        animatedSprite[RIVALANIMATEDSPRITE].setScale(0.0005*width, 0.00097*height);

        shape[LIFESHAPE]            .setPosition(0.08*width, 0.031*height);
        shape[LIFESHAPE]            .setFillColor(sf::Color::Red);
        shape[RIVALLIFESHAPE]       .setPosition(0.88*width, 0.031*height);
        shape[RIVALLIFESHAPE]       .setFillColor(sf::Color::Red);
        shape[FIRESHAPE]            .setPosition(0.24*width, 0.031*height);
        shape[FIRESHAPE]            .setFillColor(sf::Color(137, 107, 73));
        shape[POWERSHAPE]           .setPosition(0.4*width, 0.031*height);
        shape[POWERSHAPE]           .setFillColor(sf::Color::Yellow);
        shape[SCORSHAPE]            .setPosition(0.63*width, 0.01*height);
        shape[SCORSHAPE]            .setSize(sf::Vector2f(0.09*width, 0.05*height));
        shape[SCORSHAPE]            .setFillColor(sf::Color(8, 8, 8));
        shape[SCORSHAPE]            .setOutlineColor(sf::Color(32, 32, 32));
        shape[SCORSHAPE]            .setOutlineThickness(0.0012 * width);
        shape[LIFERECTANGLE]        .setPosition(0.08*width, 0.031*height);
        shape[LIFERECTANGLE]        .setFillColor(sf::Color(0, 0, 0, 0));
        shape[LIFERECTANGLE]        .setOutlineColor(sf::Color::Red);
        shape[LIFERECTANGLE]        .setOutlineThickness(1);
        shape[LIFERECTANGLE]        .setSize(sf::Vector2f(0.1 * width, 0.011 * height));
        shape[RIVALLIFERECTANGLE]   .setPosition(0.88*width, 0.031*height);
        shape[RIVALLIFERECTANGLE]   .setFillColor(sf::Color(0, 0, 0, 0));
        shape[RIVALLIFERECTANGLE]   .setOutlineColor(sf::Color::Red);
        shape[RIVALLIFERECTANGLE]   .setOutlineThickness(1);
        shape[RIVALLIFERECTANGLE]   .setSize(sf::Vector2f(0.1 * width, 0.011 * height));
        shape[FIRERECTANGLE]        .setPosition(0.24*width, 0.031*height);
        shape[FIRERECTANGLE]        .setFillColor(sf::Color(0, 0, 0, 0));
        shape[FIRERECTANGLE]        .setOutlineColor(sf::Color(107, 77, 43));
        shape[FIRERECTANGLE]        .setOutlineThickness(1);
        shape[FIRERECTANGLE]        .setSize(sf::Vector2f(0.1 * width, 0.011 * height));
        shape[POWERRECTANGLE]       .setPosition(0.4*width, 0.031*height);
        shape[POWERRECTANGLE]       .setFillColor(sf::Color(0, 0, 0, 0));
        shape[POWERRECTANGLE]       .setOutlineColor(sf::Color(230, 230, 0));
        shape[POWERRECTANGLE]       .setOutlineThickness(1);
        shape[POWERRECTANGLE]       .setSize(sf::Vector2f(0.1 * width, 0.011 * height));
        mainShape                   .setPointCount(6);
        mainShape                   .setPoint(0, sf::Vector2f(0, 0));
        mainShape                   .setPoint(1, sf::Vector2f(width, 0));
        mainShape                   .setPoint(2, sf::Vector2f(width, 0.08*height));
        mainShape                   .setPoint(3, sf::Vector2f(0.92*width, 0.18*height));
        mainShape                   .setPoint(4, sf::Vector2f(0.08*width, 0.18*height));
        mainShape                   .setPoint(5, sf::Vector2f(0, 0.08*height));
        mainShape                   .setFillColor(sf::Color::Black);

        soundBuffer[HOVERBTNSOUND]  .loadFromFile("data/sound/hoverBtnSound.wav");
        sound[HOVERBTNSOUND]        .setBuffer(soundBuffer[HOVERBTNSOUND]);

        soundBuffer[CLICKBTNSOUND]  .loadFromFile("data/sound/clickBtnSound.wav");
        sound[CLICKBTNSOUND]        .setBuffer(soundBuffer[CLICKBTNSOUND]);
        sound[CLICKBTNSOUND]        .setPitch(1.6);
        soundBuffer[FIRESOUND]      .loadFromFile("data/sound/fireSound.wav");
        sound[FIRESOUND]            .setBuffer(soundBuffer[FIRESOUND]);
        sound[FIRESOUND]            .setLoop(true);

        soundBuffer[EXPLOSIONSOUND] .loadFromFile("data/sound/explosionSound.wav");
        sound[EXPLOSIONSOUND]       .setBuffer(soundBuffer[EXPLOSIONSOUND]);
        sound[EXPLOSIONSOUND]       .setVolume(8);

        backgroungMusic             .openFromFile("data/sound/playBackgroundMusic.wav");
        backgroungMusic             .setLoop(true);
        winSound                    .openFromFile("data/sound/winSound.wav");
        loseSound                   .openFromFile("data/sound/loseSound.wav");

        loaded = true;
    }

    bool isReady()
    {
        return loaded;
    }
};

#endif // DATAMANAGER_H
