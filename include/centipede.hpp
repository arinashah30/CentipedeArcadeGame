/*
Author: Arina Shah
Class: ECE4122
Last Date Modified: 9/29/2024
Description: This file defines the ECE_CentipedeSegment and ECE_Centipede classes, which represent the individual segments of the centipede and manage the overall centipede behavior in the game.
*/

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <list>
#include <iostream>
#include <define.hpp>

using std::cerr;
using std::endl;
using namespace sf;

/**
 * @class ECE_CentipedeSegment
 * @brief Represents one segment of the centipede, either a body or head segment.
 * 
 * The ECE_CentipedeSegment class manages the functionality of each individual segment of the centipede, whether it be the head or a body segment. 
 * It handles movement, collision detection with mushrooms, and segment erasure.
 */
class ECE_CentipedeSegment : public sf::Sprite
{
public:
    bool isHead;  ///< A boolean flag indicating if the segment is a head segment.
    CENTIPEDE_DIRECTION horizontalDirection;  ///< The horizontal movement direction of the segment.
    CENTIPEDE_DIRECTION verticalDirection;    ///< The vertical movement direction of the segment.
    int x;                                    ///< The current X coordinate of the segment.
    int y;                                    ///< The current Y coordinate of the segment.
    int segmentNum;                           ///< The segment number in the centipede's chain.
    int oldX;                                 ///< The previous X coordinate before movement.
    int oldY;                                 ///< The previous Y coordinate before movement.
    sf::Texture texture;                      ///< The texture applied to the segment (head or body).

    /**
     * @brief Constructor for the ECE_CentipedeSegment class.
     * @param isHead If this segment is the head or not.
     * @param index The index of this segment in the overall centipede.
     * 
     * This constructor initializes the centipede segment, either as the head or as a body segment, 
     * and sets its position based on the segment index.
     */
    ECE_CentipedeSegment(bool isHead, int index);

    /**
     * @brief Detects if the centipede segment has collided with a mushroom.
     * 
     * This function checks for an intersection between the segment's bounding box and the mushrooms' bounding boxes.
     * 
     * @return True if a collision has occurred, otherwise false.
     */
    bool detectMushroomCollision();

    /**
     * @brief Erases the current segment by drawing over its old position.
     * 
     * This function removes the visual representation of the segment by drawing a black rectangle at its old position. 
     * It is useful when segments move, as the old image needs to be erased.
     */
    void eraseSegment();

    /**
     * @brief Updates the movement of the centipede head.
     * 
     * This function moves the head segment of the centipede. It handles mushroom collisions, direction changes, and boundary detection.
     * The movement is determined by the current direction and the boundaries of the game window.
     */
    void updateHead();
};

/**
 * @class ECE_Centipede
 * @brief Represents the entire centipede, made up of a series of segments (head and body).
 * 
 * The ECE_Centipede class is responsible for controlling the movement, collision detection, drawing, and updates for the entire centipede chain.
 */
class ECE_Centipede : public sf::Sprite
{
private:
    std::list<ECE_CentipedeSegment *> segments;  ///< A list of segments that make up the centipede.

public:
    int alive;  ///< A flag that indicates whether the centipede is alive or not (1 for alive, 0 for dead).

    /**
     * @brief Constructor for the ECE_Centipede class.
     * 
     * Initializes the centipede by creating the head and body segments, and adding them to the segments list.
     */
    ECE_Centipede();

    /**
     * @brief Updates the movement and state of the centipede.
     * 
     * This function is called in the game loop to ensure the centipede moves and interacts with the environment correctly.
     * It moves all the segments, handles collisions, and updates the centipede's overall behavior.
     */
    void updateCentipede();

    /**
     * @brief Detects if the centipede has collided with the player.
     * @param playerBounds The bounding box of the player's character for collision detection.
     * 
     * This function checks if any segment of the centipede intersects with the player's bounding box.
     * 
     * @return True if a collision has occurred, otherwise false.
     */
    bool detectPlayerCollision(FloatRect playerBounds);

    /**
     * @brief Draws the centipede on the screen.
     * 
     * This function iterates over all the segments of the centipede and draws them using the window object.
     */
    void drawCentipede();

    /**
     * @brief Detects if a laser has collided with the centipede.
     * @param laserBounds The bounding box of the laser for collision detection.
     * 
     * This function checks if any segment of the centipede intersects with a laser's bounding box. 
     * If a segment is hit, it either gets removed or turns into a new head.
     */
    void detectLaserCollision(FloatRect laserBounds);

    /**
     * @brief Updates the 'alive' status of the centipede.
     * 
     * This function checks if there are any segments left in the centipede. If the list is empty, it marks the centipede as dead.
     */
    void updateAlive();

    /**
     * @brief Moves the centipede segments following the head.
     * @param head The head of the centipede.
     * 
     * This function moves the body segments of the centipede in such a way that they follow the head's movements.
     * Each segment follows the segment in front of it.
     */
    void moveSegment(ECE_CentipedeSegment *head);

    int frameCounter = 0;  ///< Keeps track of the frames to control the update frequency.
    const int updateFrequency = 100;  ///< Controls how frequently the centipede is updated.
};

// External declaration for the centipede object.
extern ECE_Centipede *centipede;