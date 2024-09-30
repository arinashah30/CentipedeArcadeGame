/*
Author: Arina Shah
Class: ECE4122
Last Date Modified: 9/29/2024
Description: This file defines the functions that are part of the Spider class and any necessary helper functions.
*/
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <list>
#include <iostream>
#include <spider.hpp>
#include <define.hpp>
#include <mushroom.hpp>
#include <thread>
#include <starship.hpp>

using std::cerr;
using std::endl;
using namespace sf;

int getRandomDirection();
sf::Clock directionChangeClock;
sf::Clock killedClock;
const float directionChangeInterval = 1.0f;
const float killDelay = 3.0f;
default_random_engine generator;
bool spiderCollision = false;

Spider::Spider()
{
    if (!texture.loadFromFile("../assets/spider.png"))
    {
        cerr << "could not create spider" << endl;
    }
    setTexture(texture);
    alive = 1;
    xdirection = getRandomDirection();
    ydirection = getRandomDirection();
    directionChangeClock.restart();

    default_random_engine generator;
    uniform_int_distribution<int> distribution_x(0, SCREEN_WIDTH);
    uniform_int_distribution<int> distribution_y(300, BOTTOM_SECTION_BOUNDARY);
    x = distribution_x(generator);
    y = distribution_y(generator);

    setPosition(x, y);
}

void Spider::kill()
{ 
    // Killed by laser
    alive = 0;
    killedClock.restart();
}

void Spider::updateLocation()
{
    //Update in the xdirection, if it's out of bounds switch xdirection
    if (0 < (x + xdirection) && (x + xdirection) < SCREEN_WIDTH)
    {
        x += xdirection;
    }
    else
    {
        xdirection = -xdirection;
    }

    //Update in the ydirection, if it's out of bounds switch ydirection
    if (BOTTOM_SECTION_BOUNDARY > (y + ydirection) && (y + ydirection) > 300)
    {
        y += ydirection;
    }
    else
    {
        ydirection = -ydirection;
    }

    setPosition(x, y);
}

void Spider::checkMushroomCollision()
{
    //Iterate through all mushrooms and check for a collision, if there is a collision remove the mushroom
    for (auto it = mushrooms.begin(); it != mushrooms.end();)
    {
        Mushroom *mushroom = *it;
        if (mushroom != nullptr)
        {
            if (getGlobalBounds().intersects(mushroom->getGlobalBounds()))
            {
                mushroom->eraseMushroom();
                delete mushroom;
                it = mushrooms.erase(it);
            }
            else
            {
                ++it;
            }
        }
        else
        {
            std::cerr << "Null pointer found in LaserBlast::detectMushroomCollision!" << std::endl;
            it = mushrooms.erase(it);
        }
    }
}

bool Spider::checkPlayerCollision()
{
    if (getGlobalBounds().intersects(player->getGlobalBounds()))
    {
        if (!spiderCollision)
        {
            spiderCollision = true;
            return true;
        }
    }
    else
    {
        spiderCollision = false;
    }
    return false;
}

void Spider::newDirection()
{
    this->xdirection = getRandomDirection();
    this->ydirection = getRandomDirection();

    //If x and y directions are both 0 the spider won't move, so keep generating a new direction until this isn't true
    while (this->xdirection == 0 && this->ydirection == 0)
    {
        this->xdirection = getRandomDirection();
        this->ydirection = getRandomDirection();
    }
}

int getRandomDirection()
{
    uniform_int_distribution<int> distribution(-1, 1);
    int num = distribution(generator);
    return num;
}

void Spider::reset()
{
    xdirection = getRandomDirection();
    ydirection = getRandomDirection();

    uniform_int_distribution<int> distribution_x(0, SCREEN_WIDTH);
    uniform_int_distribution<int> distribution_y(300, BOTTOM_SECTION_BOUNDARY);
    x = distribution_x(generator);
    y = distribution_y(generator);
    alive = 1;
    setPosition(x, y);
}

void Spider::update()
{
    if (alive)
    {
        frameCounter++;

        // Only update the spider's position every 'updateFrequency' frames
        if (frameCounter >= updateFrequency)
        {
            //Change the direction every 'directionChangeInterval' seconds
            if (directionChangeClock.getElapsedTime().asSeconds() >= directionChangeInterval)
            {
                newDirection();                 
                directionChangeClock.restart();
            }

            updateLocation();
            checkPlayerCollision();
            frameCounter = 0;
            checkMushroomCollision();
        }
    }
    else
    {
        //If the spider was killed wait til 'killDelay' seconds have passed to respawn
        if (killedClock.getElapsedTime().asSeconds() >= killDelay)
        {
            reset();
            killedClock.restart();
        }
    }
}