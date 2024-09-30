/*
Author: Arina Shah
Class: ECE4122
Last Date Modified: 9/29/2024
Description: This file defines the ECE_LaserBlast class which represents a laser blast fired by the player in the game.
*/

#ifndef LASERBLAST_HPP
#define LASERBLAST_HPP

// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <list>
#include <iostream>
#include <define.hpp>
#include <mushroom.hpp>

#include <list>

using namespace std;
using ::cerr;
using ::endl;
using namespace sf;

/**
 * @class ECE_LaserBlast
 * @brief Represents a laser blast fired by the player in the game.
 * 
 * The ECE_LaserBlast class manages the position, collision detection, and drawing of laser blasts
 * that interact with various objects (mushrooms, centipedes, spiders) in the game.
 */
class ECE_LaserBlast : public sf::Drawable
{
public:
    int x; ///< The X-coordinate of the laser's position.
    int y; ///< The Y-coordinate of the laser's position.
    int id; ///< Unique identifier for each laser blast.
    sf::RectangleShape laserShape; ///< The shape of the laser used for rendering and collision detection.

    /**
     * @brief Constructor for the ECE_LaserBlast class.
     * @param x The initial X-coordinate of the laser.
     * @param y The initial Y-coordinate of the laser.
     * 
     * Initializes the position and shape of the laser blast, and prepares it for drawing and collision detection.
     */
    ECE_LaserBlast(int x, int y);

    /**
     * @brief Detects collision between the laser and mushrooms.
     * 
     * If the laser hits a mushroom, the mushroom takes damage and may be removed from the game.
     */
    void detectMushroomCollision();

    /**
     * @brief Detects collision between the laser and centipede segments.
     * 
     * If the laser hits a centipede segment, that segment is removed or turned into a head.
     */
    void detectCentipedeCollision();

    /**
     * @brief Detects collision between the laser and spiders.
     * 
     * If the laser hits a spider, the spider is killed and removed from the game.
     */
    void detectSpiderCollision();

    /**
     * @brief Updates the position of the laser blast.
     * 
     * Moves the laser in the game world and returns whether the laser is still active or has left the screen.
     * @return True if the laser is still within the game bounds, false if it should be removed.
     */
    bool updatePosition();

    /**
     * @brief Updates the laser's state.
     * 
     * This function manages the laser's movement, collision detection, and whether it should remain active.
     */
    void update();

    /**
     * @brief Draws the laser blast on the screen.
     * 
     * @param target The render target to draw the laser on.
     * @param states The current render states.
     */
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override
    {
        target.draw(laserShape, states);
    }

    /**
     * @brief Draws the laser.
     * 
     * This method handles rendering the laser blast on the game window.
     */
    void drawLaser();

    /**
     * @brief Erases the laser's last position on the screen.
     * 
     * This function ensures that the previous position of the laser is cleared before drawing it in its new position.
     */
    void eraseLastPosition();
};

/**
 * @brief Updates the state of all lasers.
 * 
 * Moves lasers, checks for collisions, and removes any that are no longer needed.
 */
void updateLasers();

#endif