#include "playState.h"

void playState::handleEvent(std::vector<stateMachine*>& myState)
{
    if(window->hasFocus() && isOutOfFocus)
    {
        loadAfterPause();
        return;
    }

    while(window->pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            window->close();

        if((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) ||
            event.type == sf::Event::LostFocus)
        {
            outOfFocusTime = clock();
            isOutOfFocus = true;
            if(soundOn)
            {
                backgroungMusic->pause();
                winSound->stop();
                loseSound->stop();
                fireSound.stop();
                rivalSound.stop();
                explosionSound.stop();
            }

            if(window->hasFocus())
                myState.push_back(new pauseState(window, data));
            break;
        }

        else if((event.type == sf::Event::GainedFocus ||
                 window->hasFocus()) &&
                 isOutOfFocus)
        {
            loadAfterPause();
            break;
        }

        if(event.type == sf::Event::MouseButtonPressed &&
           event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2i mouseCoordinate(sf::Mouse::getPosition(*window));

            // daca apas click stanga in arena, pornesc timer-ul pentru puterea atacului
            // folosesc isPressedOk pentru a putea stii cand se calculeaza corect puterea atacului
            if(mouseCoordinate.x < 0.9*width && int(clock()-fireTime) >= rivalFireTimeMax)
            {
                powerTime = clock();
                isPressedOk = true;
            }

            if(0.915*width <= mouseCoordinate.x && mouseCoordinate.x <= 0.985*width &&
               0.4*height <= mouseCoordinate.y && mouseCoordinate.y <= 0.5*height &&
               clock() - shieldCooldownTime > SHIELDTIME_COOLDOWN &&
               !shield)
            {
                shield = true;
                shieldTime = clock();
            }
        }

        if(event.type == sf::Event::MouseButtonReleased &&
           event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f mouseCoordinate(sf::Mouse::getPosition(*window));

            // daca am lasat click stanga in arena si asta s-a intamplat dupa ce am apasat click stanga in arena (isPressedOk = true)
            // creez imaginea de atac prin fireMovement (guverneaza miscarea in totalitate a atacului)
            // fireAnimatedSprite reprezinta doar imaginea bilei
            if(mouseCoordinate.x < 0.9*width && int(clock()-fireTime) >= rivalFireTimeMax && isPressedOk)
            {
                sf::Vector2f tempPosition = player->getPosition();
                isPressedOk = false;

                AnimatedSprite fireAnimatedSpriteTemp = data->animatedSprite[FIREANIMATEDSPRITE];
                fireAnimatedSpriteTemp.setPosition(tempPosition);
                fireAnimatedSprite.push_back(fireAnimatedSpriteTemp);

                Movement fireMovementTemp;
                fireMovementTemp.init(tempPosition, mouseCoordinate, 0.4 * width, &fireSound);
                fireMovement.push_back(fireMovementTemp);

                myDamage.push_back(myDamageMax * powerShapeLenght/(0.1 * width));
                // cu cat tin mai mult click apasat, cu atat atac mai puternic
                // cu cat e atacul mai puternic, cu atat dureaza mai mult pana la generarea urmatorului atac
                fireTime = clock() - rivalFireTimeMax * (1.-(float)powerShapeLenght/(0.1 * width));
            }
        }

        if(event.type == sf::Event::MouseButtonPressed &&
           event.mouseButton.button == sf::Mouse::Right)
        {
            if(clock() - shieldCooldownTime > SHIELDTIME_COOLDOWN &&
               !shield)
            {
                shield = true;
                shieldTime = clock();
            }
        }
    }

    if(player->getHealth() <= 0 && !lostGame)
    {
        lostGame = true, rendered = false;
        scorRival ++;
    }

    if(rivalHealth <= 0 && !winGame)
    {
        winGame = true;
        rendered = false;
        scorPlayer ++;
        player->winImage();
    }
}

void playState::update(std::vector<stateMachine*>& myState)
{
    if(isOutOfFocus == true)
        return;

    fireFrameTime = frameClock.restart();
    rivalFrameTime = rivalFrameClock.restart();
    // lungimile barilor din stanga sus pentru viata, timpul intre atacuri si puterea atacului
    lifeShapeLenght = std::max(0, (int)(0.1*width*player->getHealth()/100));
    fireShapeLenght = std::min(0.1*width, 0.1*width*(clock()-fireTime)/rivalFireTimeMax);
    powerShapeLenght = sf::Mouse::isButtonPressed(sf::Mouse::Left) && isPressedOk ? std::min(0.1*width, 0.1*width*(clock()-powerTime+1)/powerTimeMax) : 0;
    rivalShapeLenght = std::max(0, (int)(0.1*width*rivalHealth/100));

    lifeShape.setSize(sf::Vector2f(lifeShapeLenght, 0.011 * height));
    fireShape.setSize(sf::Vector2f(fireShapeLenght, 0.011 * height));
    powerShape.setSize(sf::Vector2f(powerShapeLenght, 0.011 * height));
    rivalLifeShape.setSize(sf::Vector2f(rivalShapeLenght, 0.011 * height));

    sprintf(lifeString, "%d%%", std::max(0, (int)player->getHealth()));
    int value = fireShapeLenght * 100 / (0.1 * width);
    if(value >= 99)
    {
        value = 100;
        powerRectangle.setOutlineColor(sf::Color(230, 230, 0));
    }
    else
    {
        powerRectangle.setOutlineColor(sf::Color::Red);
    }
    sprintf(fireString, "%d%%", value);
    value = powerShapeLenght * 100 / (0.1 * width);
    if(value >= 99)
        value = 100;
    sprintf(powerString, "%d%%", value);
    sprintf(rivalLifeString, "%d%%", std::max(0, (int)rivalHealth));

    player->update(winGame || lostGame);

    // daca am generat un atac
    for(unsigned int i = 0; i < fireMovement.size(); i++)
    {
        if(fireMovement[i].getExist())
        {
            // fac update la bila de atac
            fireAnimatedSprite[i].play(fireAnimation);
            fireAnimatedSprite[i].setPosition(fireMovement[i].update(fireAnimatedSprite[i].getPosition()));
            fireAnimatedSprite[i].update(fireFrameTime);
            fireAnimatedSprite[i].setRotation(fireMovement[i].getAngle());

            sf::Vector2f distance_vector = fireAnimatedSprite[i].getPosition() - player->getPosition();
            float distance_fire_player = sqrt( pow(distance_vector.x, 2) +
                                               pow(distance_vector.y, 2) );
            fireMovement[i].setVolume(100 - distance_fire_player * 100. / width * 2);

            // verific coliziunea cu marginile arenei
            if(fireAnimatedSprite[i].getPosition().x < 0.09*width)
                fireMovement[i].hitLeft(), myDamage[i] *= 0.5;

            if(fireAnimatedSprite[i].getPosition().x > 0.91*width)
                fireMovement[i].hitRight(), myDamage[i] *= 0.5;

            if(fireAnimatedSprite[i].getPosition().y > 0.81*height)
                fireMovement[i].hitDown(), myDamage[i] *= 0.5;

            if(fireAnimatedSprite[i].getPosition().y < -0.2*height)
            {
                // daca bila ajunge in partea de sus, ajunge la rival
                fireMovement[i].setExist(false);
                // daca joc singleplayer, lovesc un rival fictiv cu o sansa de 75%
                if(rand()%100+1 <= 75)
                    rivalHealth -= myDamage[i];
            }
        }
        else
        {
            fireMovement.erase(fireMovement.begin() + i);
            fireAnimatedSprite.erase(fireAnimatedSprite.begin() + i);
            myDamage.erase(myDamage.begin() + i);
            i--;
        }
    }

    // daca joc singleplayer, fac cpu sa "atace"
    if(int(clock()-rivalTime) >= nextRivalFireTime)
    {
        sf::Vector2f _start;
        sf::Vector2f _finish;

        _start.x = rand()%((int)(0.7*width)) + 0.15*width;
        _start.y = 0.1*height;

        _finish.x = rand()%((int)(0.7*width)) + 0.15*width;
        _finish.y = 0.75*height;

        rivalTime = clock();

        Movement rivalMovementTemp;
        rivalMovementTemp.init(_start, _finish, 0.4 * width, &rivalSound);
        rivalMovement.push_back(rivalMovementTemp);

        // damage-ul poate fi random intre 1 si MAX
        // acest lucru influenteaza si timpul intre atacuri
        // puterea rivalului este direct proportionala cu nivelul jocului (scortul utilizatorului)
        rivalDamage.push_back(rand()%(rivalDamageMax*(scorPlayer+1))+1);
        nextRivalFireTime = (float)(rivalDamage.back()/(scorPlayer+1)/rivalDamageMax) * (rivalFireTimeMax/(1+0.1*scorPlayer+1) + rivalPowerTimeMax);

        AnimatedSprite rivalAnimatedSpriteTemp;
        /*
        data->animatedSprite[RIVALANIMATEDSPRITE].setScale(0.0005*width * rivalDamage.back()/10,
                                                           0.00097*height * rivalDamage.back()/10);
                                                           */
        rivalAnimatedSpriteTemp = data->animatedSprite[RIVALANIMATEDSPRITE];
        rivalAnimatedSpriteTemp.setPosition(_start);
        rivalAnimatedSprite.push_back(rivalAnimatedSpriteTemp);
    }

    // daca am primit un atac din partea rivalului, fac update la fel ca si atacului generat de mine
    for(unsigned int i = 0; i < rivalMovement.size(); i++)
    {
        if(rivalMovement[i].getExist())
        {
            rivalAnimatedSprite[i].play(rivalAnimation);
            rivalAnimatedSprite[i].setPosition(rivalMovement[i].update(rivalAnimatedSprite[i].getPosition()));
            rivalAnimatedSprite[i].update(rivalFrameTime);
            rivalAnimatedSprite[i].setRotation(rivalMovement[i].getAngle());

            sf::Vector2f distance_vector = rivalAnimatedSprite[i].getPosition() - player->getPosition();
            float distance_fire_player = sqrt( pow(distance_vector.x, 2) +
                                               pow(distance_vector.y, 2) );
            rivalMovement[i].setVolume(100 - distance_fire_player * 100. / width * 2);

            if(rivalAnimatedSprite[i].getPosition().x < 0.15*width)
                rivalMovement[i].hitLeft(), rivalDamage[i] *= 0.5;

            if(rivalAnimatedSprite[i].getPosition().x > 0.85*width)
                rivalMovement[i].hitRight(), rivalDamage[i] *= 0.5;

            if(rivalAnimatedSprite[i].getPosition().y > 0.75*height)
                rivalMovement[i].hitDown(), rivalDamage[i] *= 0.5;

            if(rivalAnimatedSprite[i].getPosition().y < -0.2*height)
                rivalMovement[i].setExist(false);

            // coliziunea dintre atacul rival si mine
            sf::Rect<float> tempIntersectRect( rivalAnimatedSprite[i].getPosition().x - 0.03*width,
                                               rivalAnimatedSprite[i].getPosition().y - 0.05*height,
                                               0.06*width,
                                               0.1*height);
            if(player->getSpriteBounds().intersects(tempIntersectRect))
            {
                if(!shield)
                {
                    player->setHealth(player->getHealth() - rivalDamage[i]);
                    explosionSound.play();
                }
                rivalMovement[i].setExist(false);
            }
        }
        else
        {
            rivalMovement.erase(rivalMovement.begin() + i);
            rivalAnimatedSprite.erase(rivalAnimatedSprite.begin() + i);
            rivalDamage.erase(rivalDamage.begin() + i);
            i--;
        }
    }

    // s-a terminat timpul de efect pentru powerup
    if(shield && clock() - shieldTime > SHIELDTIME_ACTIVE)
    {
        shield = false;
        shieldCooldownTime = clock();
    }

    if((lostGame || winGame) && rendered)
    {
        if(soundOn)
        {
            backgroungMusic->setVolume(0);
            if(lostGame)
                loseSound->play();
            else
                winSound->play();
        }
        Sleep(SLEEPTIME_WINLOSE);

        if(soundOn)
        {
            loseSound->stop();
            winSound->stop();
            backgroungMusic->setVolume(8);
        }

        player->setHealth(100);
        rivalHealth = 100;
        rivalTime = clock();
        fireTime = 0;
        powerTime = clock();
        shieldTime = clock();
        shieldCooldownTime = clock();
        srand(time(NULL));
        for(unsigned int i = 0; i < fireMovement.size(); i++)
            fireMovement[i].setExist(false);
        for(unsigned int i = 0; i < rivalMovement.size(); i++)
            rivalMovement[i].setExist(false);
        shield = false;
        lostGame = false;
        winGame = false;
    }

    mouseSprite.setPosition((sf::Vector2f)sf::Mouse::getPosition(*window));
}

void playState::render()
{
    if(isOutOfFocus == true)
    {
        window->draw(logoText);
        window->draw(logoText2);
        return;
    }

    window->draw(backgroundSprite);
    if(!shield)
        player->render();
    else
    {
        playerOnShield.setPosition(player->getPosition());
        window->draw(playerOnShield);
    }

    for(unsigned int i = 0; i < fireMovement.size(); i++)
        if(fireMovement[i].getExist())
            window->draw(fireAnimatedSprite[i]);
    for(unsigned int i = 0; i < rivalMovement.size(); i++)
        if(rivalMovement[i].getExist())
            window->draw(rivalAnimatedSprite[i]);

    window->draw(mainBlackShape);
    window->draw(scorShape);

    outtextxy(0.785*width, 0.015*height, "Rival:", sf::Color(240, 240, 240), 0.019 * width);

    sprintf(scorString, "%d   |   %d", scorPlayer, scorRival);
    outtextxy(0.65*width, 0.02*height, scorString, sf::Color(240, 240, 240), 0.015 * width);

    window->draw(shieldSprite);
    heartSprite.setPosition(0.02*width, 0.02*height);
    window->draw(heartSprite);
    heartSprite.setPosition(0.82*width, 0.02*height);
    window->draw(heartSprite);
    window->draw(cooldownSprite);
    window->draw(powerSprite);
    window->draw(lifeShape);
    window->draw(lifeRectangle);
    window->draw(rivalLifeShape);
    window->draw(rivalLifeRectangle);
    window->draw(fireShape);
    window->draw(fireRectangle);
    window->draw(powerShape);
    window->draw(powerRectangle);

    outtextxy(0.16 * width, 0.04 * height,
              lifeString, sf::Color(240, 240, 240), 0.012 * width);
    outtextxy(0.96 * width, 0.04 * height,
              rivalLifeString, sf::Color(240, 240, 240), 0.012 * width);
    outtextxy(0.32 * width, 0.04 * height,
              fireString, sf::Color(240, 240, 240), 0.012 * width);
    outtextxy(0.48 * width, 0.04 * height,
              powerString, sf::Color(240, 240, 240), 0.012 * width);

    if(shield)
    {
        sf::RectangleShape shape;
        shape.setFillColor(sf::Color(0, 0, 0, 150));
        shape.setPosition(0.917*width, 0.5*height);
        shape.setSize(sf::Vector2f(0.1*width, -0.0789*height*(clock()-shieldTime)/SHIELDTIME_ACTIVE));
        window->draw(shape);
    }

    if(!shield && clock()-shieldCooldownTime < SHIELDTIME_COOLDOWN)
    {
        sf::RectangleShape shape;
        shape.setFillColor(sf::Color(0, 0, 0, 150));
        shape.setPosition(0.917*width, 0.5*height);
        shape.setSize(sf::Vector2f(0.1*width, -0.0789*height*(SHIELDTIME_COOLDOWN-clock()+shieldCooldownTime)/SHIELDTIME_COOLDOWN));
        window->draw(shape);
    }

    window->draw(mouseSprite);
    rendered = true;
}

void playState::loadAfterPause()
{
    fireTime                += clock() - outOfFocusTime;
    powerTime               += clock() - outOfFocusTime;
    rivalTime               += clock() - outOfFocusTime;
    shieldTime              += clock() - outOfFocusTime;
    shieldCooldownTime      += clock() - outOfFocusTime;
    for(unsigned int i = 0; i < fireMovement.size(); i++)
        if(fireMovement[i].getExist())
        {
            fireMovement[i]         .updateAfterPause(clock() - outOfFocusTime);
            fireAnimatedSprite[i]   .updateAfterPause(sf::milliseconds(clock() - outOfFocusTime));
        }
    for(unsigned int i = 0; i < rivalMovement.size(); i++)
        if(rivalMovement[i].getExist())
        {
            rivalMovement[i]        .updateAfterPause(clock() - outOfFocusTime);
            rivalAnimatedSprite[i]  .updateAfterPause(sf::milliseconds(clock() - outOfFocusTime));
        }
    isOutOfFocus = false;
    if(soundOn)
        backgroungMusic->play();
}
