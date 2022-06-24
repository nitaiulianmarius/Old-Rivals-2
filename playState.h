#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "windows.h"
#include "stateMachine.h"
#include "pauseState.h"
#include "player.h"
#include "movement.h"
#include "algorithm"

#define STRING_MAX_LENGTH 16
#define FIRE_MAX_LENGTH 16
#define SHIELDTIME_ACTIVE 3000
#define SHIELDTIME_COOLDOWN 8000
#define SLEEPTIME_WINLOSE 3000

const int myDamageMax       = 12;
const int rivalDamageMax    = 12;
const int fireTimeMax       = 2500;
const int rivalFireTimeMax  = 2500;
const int powerTimeMax      = 800;
const int rivalPowerTimeMax = 600;

class playState:public stateMachine
{
    sf::Sprite backgroundSprite;
    sf::Sprite shieldSprite;
    sf::Sprite heartSprite;
    sf::Sprite cooldownSprite;
    sf::Sprite powerSprite;
    sf::Sprite fireSprite;
    sf::Sprite rivalSprite;
    sf::Sprite playerOnShield;
    sf::RectangleShape lifeShape, lifeRectangle;
    sf::RectangleShape rivalLifeShape, rivalLifeRectangle;
    sf::RectangleShape fireShape, fireRectangle;
    sf::RectangleShape powerShape, powerRectangle;
    sf::RectangleShape scorShape;
    sf::ConvexShape mainBlackShape;
    sf::Music *backgroungMusic;
    sf::Music *winSound;
    sf::Music *loseSound;
    sf::Sound fireSound;
    sf::Sound rivalSound;
    sf::Sound explosionSound;
    sf::Clock frameClock;
    sf::Clock rivalFrameClock;
    sf::Time fireFrameTime;
    sf::Time rivalFrameTime;
    Animation fireAnimation;
    Animation rivalAnimation;
    std::vector<AnimatedSprite> fireAnimatedSprite;
    std::vector<AnimatedSprite> rivalAnimatedSprite;
    std::vector<Movement> fireMovement;
    std::vector<Movement> rivalMovement;
    std::vector<float> myDamage;
    std::vector<float> rivalDamage;
    Player *player;
    DWORD fireTime, powerTime;
    DWORD rivalTime;
    DWORD shieldTime;
    DWORD shieldCooldownTime;
    DWORD outOfFocusTime;
    float lifeShapeLenght;
    float fireShapeLenght;
    float powerShapeLenght;
    float rivalShapeLenght;
    float rivalHealth;
    char scorString[STRING_MAX_LENGTH];
    char lifeString[STRING_MAX_LENGTH];
    char rivalLifeString[STRING_MAX_LENGTH];
    char fireString[STRING_MAX_LENGTH];
    char powerString[STRING_MAX_LENGTH];
    bool isPressedOk;
    bool lostGame;
    bool winGame;
    bool shield;
    bool rendered;
    bool soundOn;
    int scorPlayer;
    int scorRival;
    int nextRivalFireTime;

public:
    playState(sf::RenderWindow *_window, dataManager *_data, bool soundSetting)
    {
        window = _window;
        data = _data;

        width = window->getSize().x;
        height = window->getSize().y;

        text.setFont(data->font);

        backgroundSprite    = data->sprite[GAMEBACKGROUND];
        mouseSprite         = data->sprite[MOUSE];
        shieldSprite        = data->sprite[SHIELD];
        heartSprite         = data->sprite[HEART];
        cooldownSprite      = data->sprite[COOLDOWN];
        powerSprite         = data->sprite[POWER];
        fireSprite          = data->sprite[FIRE];
        rivalSprite         = data->sprite[RIVALFIRE];
        playerOnShield      = data->sprite[PLAYERONSHIELD];

        lifeShape           = data->shape[LIFESHAPE];
        rivalLifeShape      = data->shape[RIVALLIFESHAPE];
        fireShape           = data->shape[FIRESHAPE];
        powerShape          = data->shape[POWERSHAPE];
        scorShape           = data->shape[SCORSHAPE];
        lifeRectangle       = data->shape[LIFERECTANGLE];
        rivalLifeRectangle  = data->shape[RIVALLIFERECTANGLE];
        fireRectangle       = data->shape[FIRERECTANGLE];
        powerRectangle      = data->shape[POWERRECTANGLE];
        mainBlackShape      = data->mainShape;

        fireAnimation       = data->animation[FIREANIMATION];
        rivalAnimation      = data->animation[RIVALANIMATION];

        soundOn = soundSetting;
        if(soundOn == true)
        {
            backgroungMusic = &data->backgroungMusic;
            winSound        = &data->winSound;
            loseSound       = &data->loseSound;
            fireSound       = data->sound[FIRESOUND];
            rivalSound      = data->sound[FIRESOUND];
            explosionSound  = data->sound[EXPLOSIONSOUND];
        }

        logoFont.loadFromFile("data/font/Bleeding_Cowboys.ttf");
        logoText.setFont(logoFont);
        logoText2.setFont(logoFont);

        logoText.setString("Rivalii");
        logoText2.setString("Joc de actiune dezvoltat in C++");

        logoText.setCharacterSize(0.04 * width);
        logoText2.setCharacterSize(0.02 * width);

        logoText.setFillColor(sf::Color(200, 0, 0));
        logoText2.setFillColor(sf::Color::White);

        logoText.setPosition (0.5*(width-logoText.getGlobalBounds().width), 0.45*height);
        logoText2.setPosition(0.5*(width-logoText2.getGlobalBounds().width), 0.52*height);

        srand(time(NULL));
        player              = new Player(window, data);
        player              ->setHealth(100);
        rivalHealth         = 100;
        rivalTime           = clock();
        shieldTime          = clock();
        shieldCooldownTime  = clock();
        fireTime            = 0;
        powerTime           = 0;
        shield              = false;
        lostGame            = false;
        winGame             = false;
        isOutOfFocus        = false;
        scorPlayer          = 0;
        scorRival           = 0;
        nextRivalFireTime   = rivalFireTimeMax;
        if(soundSetting == true)
        {
            backgroungMusic->setVolume(8);
            backgroungMusic->play();
        }
    };

        ~playState()
        {
            delete player;
            if(soundOn)
            {
                backgroungMusic->stop();
                winSound->stop();
                loseSound->stop();
                fireSound.stop();
                rivalSound.stop();
                explosionSound.stop();
            }
        }

    void handleEvent(std::vector<stateMachine*>&);
    void update(std::vector<stateMachine*>&);
    void render();
    void loadAfterPause();
};

#endif // INTROSTATE_H
