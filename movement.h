#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <stdlib.h>
#include "SFML/Graphics.hpp"
#include "math.h"

class Movement
{
    sf::Vector2f start, finish;
    sf::Vector2f vectDiff, normalizedVector;
    sf::Sound *sound;
    float angle;
    float lenght;
    float speed;
    int lastUpdate;
    bool moving;
    bool hitLeftB;
    bool hitRightB;
    bool hitUpB;
    bool hitDownB;
    bool reverseHorizontalB;
    bool changedAngleAfterCollision;
    bool soundIsPlaying;

public:
    Movement()
    {
        moving = false;
        hitLeftB = false;
        hitRightB = false;
        hitUpB = false;
        hitDownB = false;
        soundIsPlaying = false;
    };

    void init(sf::Vector2f _start, sf::Vector2f  _finish, float _speed, sf::Sound *_sound = NULL)
    {
        start = _start;
        finish = _finish;
        speed = _speed;
        sound = _sound;

        if(sound != NULL)
        {
            sound->play();
            soundIsPlaying = true;
        }

        vectDiff = finish - start;
        lenght = sqrt( pow(finish.x - start.x, 2) + pow(finish.y - start.y, 2) );
        if(lenght > 0.01*speed)
        {
            normalizedVector = (sf::Vector2f)vectDiff / lenght;
            moving = true;
            lastUpdate = clock();
            hitLeftB = false;
            hitRightB = false;
            hitUpB = false;
            hitDownB = false;
            reverseHorizontalB = false;
            changedAngleAfterCollision = false;
        }

        angle = acos(normalizedVector.y) * 180 / 3.14159f;
        if(start.x < finish.x)
            angle *= -1;
    };

    float calculateAngle(float x1, float y1, float x2, float y2)
    {
        sf::Vector2f up(0, 1);
        sf::Vector2f p0(x1, y1);
        sf::Vector2f p1(x2, y2);
        sf::Vector2f q = p1 - p0;
        float q_length = sqrtf(q.x * q.x + q.y * q.y);
        q.x /= q_length;
        q.y /= q_length;
        float scalar_product = q.y;
        float angle = acos(scalar_product) * 180.0f / 3.14159f;
        if (x2 - x1 < 0.0f)
            return angle;
        else
            return -angle;
    }

    sf::Vector2f update(sf::Vector2f position)
    {
        if(moving == true)
        {
            sf::Vector2f tempVect = normalizedVector;
            int hitCount = 0;

            if(hitLeftB)
            {
                tempVect.x *= -1, hitCount++;
                if(!changedAngleAfterCollision)
                {
                    angle = -angle;
                    changedAngleAfterCollision = true;
                }
            }

            if(hitRightB)
            {
                tempVect.x *= -1, hitCount++;
                if(!changedAngleAfterCollision)
                {
                    angle = -angle;
                    changedAngleAfterCollision = true;
                }
            }

            if(hitUpB)
            {
                tempVect.y *= -1, hitCount++;
                if(!changedAngleAfterCollision)
                {
                    angle = 180-angle;
                    changedAngleAfterCollision = true;
                }
            }

            if(hitDownB)
            {
                tempVect.y *= -1, hitCount++;
                if(!changedAngleAfterCollision)
                {
                    angle = 180-angle;
                    changedAngleAfterCollision = true;
                }
            }

            if(hitCount >= 2)
            {
                moving = false;
                if(sound && soundIsPlaying == true)
                {
                    sound->stop();
                    soundIsPlaying = false;
                }
            }

            if(reverseHorizontalB)
                tempVect.x *= -1;

            tempVect.x *= speed*(clock()-lastUpdate)/1000.;
            tempVect.y *= speed*(clock()-lastUpdate)/1000.;

            lastUpdate = clock();

            return position+tempVect;
        }

        else
        {
            if(sound && soundIsPlaying == true)
            {
                sound->stop();
                soundIsPlaying = false;
            }
        }

        return sf::Vector2f(0, 0);
    };

    bool getExist()
    {
        return moving;
    }

    void setExist(bool exist)
    {
        moving = exist;
        if(!exist && sound && soundIsPlaying == true)
        {
            sound->stop();
            soundIsPlaying = false;
        }
    }

    void setVolume(int volume)
    {
        sound->setVolume(volume);
    }

    void updateAfterPause(DWORD elapsedTime)
    {
        lastUpdate += elapsedTime;
    }

    sf::Vector2f getStart()
    {
        return start;
    }

    sf::Vector2f getFinish()
    {
        return finish;
    }

    void hitLeft()
    {
        hitLeftB = true;
    }

    void hitRight()
    {
        hitRightB = true;
    }

    void hitUp()
    {
        hitUpB = true;
    }

    void hitDown()
    {
        hitDownB = true;
    }

    bool getHitLeft()
    {
        return hitLeftB;
    }

    bool getHitRight()
    {
        return hitRightB;
    }

    bool getHitUp()
    {
        return hitUpB;
    }

    bool getHitDown()
    {
        return hitDownB;
    }

    float getAngle()
    {
        return angle;
    }

    void reverseHorizontal()
    {
        reverseHorizontalB = true;
    }
};
#endif // MOVEMENT_H
