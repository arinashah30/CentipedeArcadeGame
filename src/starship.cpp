
/*
Author: Arina Shah
Class: ECE4122
Last Date Modified: 9/29/2024
Description: This file defines the functions that are part of the Starship class and any necessary helper functions.
*/
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <list>
#include <iostream>
#include <starship.hpp>
#include <define.hpp>

using std::cerr;
using std::endl;
using namespace sf;

Starship::Starship()
{
    this->lives = 3;
    this->score = 0;
    if (!texture.loadFromFile("../assets/StarShip.png"))
    {
        cerr << "could not create starship" << endl;
    }
    setTexture(texture);
    this->x = SCREEN_WIDTH / 2;
    this->y = BOTTOM_SECTION_BOUNDARY;
    setPosition(x, y);
}

bool Starship::detectCollision(FloatRect bounds)
{
    bool collision = false;

    if (this->getGlobalBounds().intersects(bounds))
    {
        collision = true;
        this->lives -= 1; // either collided with spider or centipede
    }
    return collision;
}

void Starship::move(int direction)
{
    //Allow the starship to keep moving until it tries to move out of bounds
    if (direction == LEFT)
    {
        if (x - 1 >= 0)
        {
            x = x - 1;
        }
    }
    else if (direction == RIGHT)
    {
        if (x + 1 <= (SCREEN_WIDTH - 20))
        {
            x = x + 1;
        }
    }
    else if (direction == UP)
    {
        if (y - 1 >= PLAYER_Y_MAX)
        {
            y = y - 1;
        }
    }
    else if (direction == DOWN)
    {
        if (y + 1 <= BOTTOM_SECTION_BOUNDARY)
        {
            y = y + 1;
        }
    }
    setPosition(x, y);
}

void Starship::increaseScore(int points)
{
    score += points;
}

void Starship::decreaseLives()
{
    lives -= 1;
}

void Starship::reset()
{
    lives = 3;
    score = 0;
    this->x = SCREEN_WIDTH / 2;
    this->y = BOTTOM_SECTION_BOUNDARY;
    setPosition(x, y);
}