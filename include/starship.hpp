/*
Author: Arina Shah
Class: ECE4122
Last Date Modified: 9/29/2024
Description: This file defines the Starship class which represents the player-controlled character in the game.
*/

#ifndef STARSHIP_HPP
#define STARSHIP_HPP 

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <list>
#include <iostream>
#include <define.hpp>
#include <laserblast.hpp>

using std::cerr;
using std::endl;
using namespace sf;

/**
 * @class Starship
 * @brief Represents the player-controlled starship in the game.
 * 
 * The Starship class is responsible for managing the player's character, including movement, collision detection, lives, and score. 
 * It inherits from SFML's Sprite class to represent the starship as a drawable object in the game world.
 */
class Starship : public sf::Sprite {

    public:
        int x;  ///< The x-coordinate of the starship's current position
        int y;  ///< The y-coordinate of the starship's current position

        int lives; ///< The number of lives the player has remaining
        int score = 0; ///< The player's current score in the game

        sf::Texture texture; ///< Texture used to represent the starship

        /**
         * @brief Constructor for the Starship class.
         * 
         * Initializes the starship by loading the texture and setting the initial position.
         */
        Starship();

        /**
         * @brief Detects if the starship has collided with an object.
         * 
         * @param bounds The bounding box of the object to check for collision.
         * @return true if a collision is detected, false otherwise.
         */
        bool detectCollision(FloatRect bounds);

        /**
         * @brief Moves the starship in the given direction.
         * 
         * @param direction The direction to move the starship, based on the player's input.
         */
        void move(int direction);

        /**
         * @brief Increases the player's score.
         * 
         * @param points The number of points to add to the player's score.
         */
        void increaseScore(int points);

        /**
         * @brief Decreases the player's lives by one.
         * 
         * Reduces the number of lives the player has remaining. If lives reach zero, the player loses the game.
         */
        void decreaseLives();

        /**
         * @brief Resets the starship's state.
         * 
         * This function resets the starship's position, lives, and other properties to their initial state.
         */
        void reset();
};

#endif
