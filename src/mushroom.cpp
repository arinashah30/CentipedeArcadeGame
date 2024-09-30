/*
Author: Arina Shah
Class: ECE4122
Last Date Modified: 9/29/2024
Description: This file defines the functions that are part of the Mushroom class and any necessary helper functions.
*/
#include <random>
#include "mushroom.hpp"
#include <list>
#include <define.hpp>

using namespace std;

list<Mushroom *> mushrooms;
default_random_engine mushroomGenerator;

/**
 * @brief Helper function to draw bounding box of mushroom
 * @param bounds The global bounds of the mushroom
 * 
 * This function draws the bounding box of the mushroom in red with the bounds passed in.
 */
void drawBoundingBoxMush(sf::FloatRect bounds) {
    sf::RectangleShape boundingBox(sf::Vector2f(bounds.width, bounds.height));

    boundingBox.setPosition(bounds.left, bounds.top);

    boundingBox.setFillColor(sf::Color::Transparent);
    boundingBox.setOutlineColor(sf::Color::Red);
    boundingBox.setOutlineThickness(1.0f);

    window.draw(boundingBox);
}


Mushroom::Mushroom(int x, int y)
{
    if (!texture.loadFromFile("../assets/Mushroom0.png"))
    {
        cerr << "could not create mushroom" << endl;
    }
    setTexture(texture);
    this->x = x;
    this->y = y;
    this->hitTimes = 0;
    setPosition(x, y);
    setOrigin(getGlobalBounds().width / 2, getGlobalBounds().height / 2);
}

void generateMushrooms()
{
    uniform_int_distribution<int> distribution_x(0, SCREEN_WIDTH);
    uniform_int_distribution<int> distribution_y(TOP_BOUNDARY, BOTTOM_SECTION_BOUNDARY - 20);
    const int restrictedXStart = 0;
    const int restrictedXEnd = 300;
    const int restrictedYStart = TOP_BOUNDARY;
    const int restrictedYEnd = 200;

    //Generate 30 mushrooms in random x and y locations
    for (int i = 0; i < 30; i++)
    {
        int x = distribution_x(mushroomGenerator);
        int y = distribution_y(mushroomGenerator);

        // Keep generating new x, y until they're outside the restricted area
        while (x >= restrictedXStart && x <= restrictedXEnd && y >= restrictedYStart && y <= restrictedYEnd)
        {
            x = distribution_x(mushroomGenerator);
            y = distribution_y(mushroomGenerator);
        }

        // Once we have valid x, y, create the mushroom
        Mushroom *newMushroom = new Mushroom(x, y);
        mushrooms.push_front(newMushroom);
    }
}

void Mushroom::spiderCollision()
{
    eraseMushroom();
}

bool Mushroom::laserHit(int laserId)
{
    bool removed = false;
    // Only update if it hasn't been hit by this laser before
    if (this->laserId != laserId)
    {
        this->laserId = laserId;
        hitTimes++;
        if (hitTimes == 1)
        {
            if (!texture.loadFromFile("../assets/Mushroom1.png"))
            {
                cerr << "could not create mushroom" << endl;
            }
            setTexture(texture);
        }
        else if (hitTimes == 2)
        {
            removed = true;
        }
    }
    return removed;
}

void drawMushrooms()
{
    for (Mushroom *mushroom : mushrooms)
    {
        if (mushroom != nullptr)
        {
            window.draw(*mushroom);
        }
    }
}

void Mushroom::eraseMushroom()
{
    sf::RectangleShape backgroundRect(sf::Vector2f(getGlobalBounds().width, getGlobalBounds().height));
    backgroundRect.setFillColor(sf::Color::Black);
    backgroundRect.setPosition(getPosition());

    window.draw(backgroundRect);
}