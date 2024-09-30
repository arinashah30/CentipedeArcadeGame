/*
Author: Arina Shah
Class: ECE4122
Last Date Modified: 9/29/2024
Description: This file defines the Mushroom class, which represents mushrooms in the game world. It handles collision detection, rendering, and changes based on hits from lasers or spiders.
*/
#ifndef MUSHROOM_HPP
#define MUSHROOM_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <list>
#include <iostream>
#include <define.hpp>
#include <laserblast.hpp>

using std::cerr;
using std::endl;
using namespace sf;
using namespace std;

/**
 * @class Mushroom
 * @brief Represents a mushroom in the game world.
 * 
 * The Mushroom class handles rendering and interaction with the game world. Mushrooms can be hit by lasers and interacted with by centipedes or spiders. They are represented as textured sprites.
 */
class Mushroom : public sf::Sprite
{
public:
    int x;             ///< The x-position of the mushroom.
    int y;             ///< The y-position of the mushroom.
    int hitTimes;      ///< Tracks how many times the mushroom has been hit by a laser.
    int laserId;       ///< The ID of the laser that last hit the mushroom.

    sf::Texture texture; ///< The texture applied to the mushroom.

    /**
     * @brief Constructor for the Mushroom class.
     * @param x The x-position of the mushroom.
     * @param y The y-position of the mushroom.
     * 
     * Initializes the mushroom at the given x and y coordinates and loads the default texture.
     */
    Mushroom(int x, int y);

    /**
     * @brief Handles collision with a spider.
     * 
     * If the mushroom collides with a spider, this function will handle removing the mushroom and other relevant effects. Typically, this will erase the mushroom from the game world.
     */
    void spiderCollision();

    /**
     * @brief Detects if the mushroom has been hit by a laser.
     * @param laserId The ID of the laser that hit the mushroom.
     * @return True if the mushroom should be removed, otherwise false.
     * 
     * This function tracks laser hits by storing the laser ID to prevent multiple hits from the same laser. After two hits, the mushroom will be marked for removal.
     */
    bool laserHit(int laserId);

    /**
     * @brief Erases the mushroom from the screen.
     * 
     * This function erases the mushroom visually by covering its location with a black rectangle, removing it from the rendered game screen.
     */
    void eraseMushroom();

    /**
     * @brief Draws a smaller vertical bounding box for the mushroom.
     * @return FloatRect A smaller bounding box that is 75% of the original height.
     * 
     * This function overrides the default getGlobalBounds to return a bounding box that is smaller in height, ensuring more precise collision detection.
     */
    virtual FloatRect getGlobalBounds() const {
        FloatRect bounds = sf::Sprite::getGlobalBounds();
        float shrinkFactor = 0.75f;
        bounds.top += bounds.height * (1.0f - shrinkFactor) / 2;
        bounds.height *= shrinkFactor; 
        return bounds;
    }
};

extern list<Mushroom *> mushrooms; ///< A global list that holds all the mushrooms in the game world.

/**
 * @brief Generates a collection of mushrooms at random locations.
 * 
 * This function creates multiple mushrooms in random locations on the screen and adds them to the global list of mushrooms. The number of mushrooms generated is predetermined by game rules.
 */
void generateMushrooms();

/**
 * @brief Draws all the mushrooms in the game world.
 * 
 * This function iterates through the global mushroom list and draws each mushroom on the screen, making them visible to the player.
 */
void drawMushrooms();

#endif
