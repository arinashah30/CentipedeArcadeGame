/*
Author: Arina Shah
Class: ECE4122
Last Date Modified: 9/29/2024
Description: This file defines the Spider class, which handles the movement, collision, and state of the spider enemy in the game.
*/

#ifndef SPIDER_HPP
#define SPIDER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <list>
#include <iostream>
#include <define.hpp>
#include <chrono>
#include <random>

using std::cerr;
using std::endl;
using namespace sf;

/**
 * @class Spider
 * @brief Represents the spider enemy in the game.
 * 
 * The Spider class handles movement, random direction changes, collisions with mushrooms and the player, 
 * and controls when the spider is killed or respawned.
 */
class Spider : public sf::Sprite
{
private:
    // Private members can be added here if needed

public:
    int alive; ///< Flag indicating whether the spider is alive (1 = alive, 0 = dead).

    int x; ///< X-coordinate of the spider's position.
    int y; ///< Y-coordinate of the spider's position.

    int xdirection; ///< Movement direction on the X-axis (-1 for left, 1 for right).
    int ydirection; ///< Movement direction on the Y-axis (-1 for up, 1 for down).

    int directionChangeCounter; ///< Counter to track direction changes.

    int frameCounter = 0; ///< Frame counter to control update frequency.
    const int updateFrequency = 5; ///< Frequency for spider updates, defining how often the spider moves or changes direction.

    Texture texture; ///< Texture used to display the spider sprite.

    /**
     * @brief Constructor for the Spider class.
     * 
     * Initializes the spider with a random starting position and direction, and loads its texture.
     */
    Spider();

    /**
     * @brief Kills the spider.
     * 
     * Marks the spider as dead and logs that it was killed. The spider will respawn after some time.
     */
    void kill();

    /**
     * @brief Randomly changes the spider's direction.
     * 
     * This function generates a new random direction for the spider to move in, ensuring that it keeps moving and doesn't stop.
     */
    void newDirection();

    /**
     * @brief Resets the spider's state.
     * 
     * This function respawns the spider at a random position with new random directions after it has been killed.
     */
    void reset();

    /**
     * @brief Checks if the spider has collided with any mushrooms.
     * 
     * If the spider intersects with a mushroom, the mushroom is removed from the game.
     */
    void checkMushroomCollision();

    /**
     * @brief Checks if the spider has collided with the player.
     * 
     * Detects if the spider has collided with the player, potentially ending the player's life.
     * @return True if the spider collides with the player, false otherwise.
     */
    bool checkPlayerCollision();

    /**
     * @brief Updates the spider's position.
     * 
     * Moves the spider based on its current direction and handles bouncing off boundaries by reversing directions.
     */
    void updateLocation();

    /**
     * @brief Updates the spider's state.
     * 
     * This function controls the spider's movement, handles collisions, and determines when to change directions.
     * It is called every frame to update the spider's behavior.
     */
    void update();
};

extern Spider *spider; ///< Global pointer to the spider object.

#endif