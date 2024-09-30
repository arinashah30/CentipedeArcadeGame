/*
Author: Arina Shah
Class: ECE4122
Last Date Modified: 9/29/2024
Description: This file defines the functions that are part of the ECE_CentipedeSegment and ECE_Centipede classes and any necessary helper functions.
*/
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <list>
#include <iostream>
#include <centipede.hpp>
#include <mushroom.hpp>
#include <starship.hpp>

ECE_Centipede *centipede;

int segmentCounter = 0;
int rowSize = 20;
float segmentGap = 20.0f;

bool isMushroomAtPosition(float x, float y);

void drawBoundingBox(sf::FloatRect bounds)
{
    sf::RectangleShape boundingBox(sf::Vector2f(bounds.width, bounds.height));

    boundingBox.setPosition(bounds.left, bounds.top);

    boundingBox.setFillColor(sf::Color::Transparent);
    boundingBox.setOutlineColor(sf::Color::Red);
    boundingBox.setOutlineThickness(1.0f);

    window.draw(boundingBox);
}

ECE_CentipedeSegment::ECE_CentipedeSegment(bool isHead, int index)
{
    int headX = 200;

    if (isHead)
    {
        if (!texture.loadFromFile("../assets/CentipedeHead.png"))
        {
            cerr << "could not create centipede head" << endl;
        }
        setTexture(texture);
        this->isHead = true;
        x = headX;
        y = TOP_BOUNDARY;
        oldX = x;
        oldY = y;
        segmentNum = segmentCounter;
        horizontalDirection = C_RIGHT;
        verticalDirection = C_DOWN;
    }
    else
    {
        if (!texture.loadFromFile("../assets/CentipedeBody.png"))
        {
            cerr << "could not create centipede body" << endl;
        }
        setTexture(texture);
        this->isHead = false;
        x = headX - (index * segmentGap);
        y = TOP_BOUNDARY;
        oldX = x;
        oldY = y;
        segmentNum = segmentCounter;
        horizontalDirection = C_RIGHT;
        verticalDirection = C_DOWN;
    }

    setPosition(x, y);
    setOrigin(getGlobalBounds().width / 2, getGlobalBounds().height / 2);
}

bool ECE_CentipedeSegment::detectMushroomCollision()
{
    bool collision = false;

    //Iterate through all mushrooms and check for a collision with this segment.
    for (Mushroom *i : mushrooms)
    {
        if (getGlobalBounds().intersects(i->getGlobalBounds()))
        {
            collision = true;
            cout << "Centipede mushroom collision detected" << endl;
            break;
        }
    }

    if (collision)
    {  
        //Move the centipede back to its starting location and down
        if (verticalDirection == C_DOWN)
        {
            if (!isMushroomAtPosition(x, y + rowSize)) {
                y += rowSize;
                if (horizontalDirection == C_RIGHT)
                {
                    x -= segmentGap;
                    horizontalDirection = C_LEFT;
                    cout << "direction set to left 1" << endl;
                }
                else if (horizontalDirection == C_LEFT)
                {
                    x += segmentGap;
                    horizontalDirection = C_RIGHT;
                    cout << "direction set to right 1" << endl;
                }
            } else {
                if (horizontalDirection == C_RIGHT)
                {
                    x -= segmentGap;
                    horizontalDirection = C_LEFT;
                    cout << "direction set to left 1" << endl;
                }
                else if (horizontalDirection == C_LEFT)
                {
                    x += segmentGap;
                    horizontalDirection = C_RIGHT;
                    cout << "direction set to right 1" << endl;
                }
            }
        }
        //Move the centipede back to its starting location and up
        else if (verticalDirection == C_UP)
        {
            if (!isMushroomAtPosition(x, y - rowSize)) {
                y -= rowSize;
                if (horizontalDirection == C_RIGHT)
                {
                    x -= segmentGap;
                    horizontalDirection = C_LEFT;
                }
                else if (horizontalDirection == C_LEFT)
                {
                    x += segmentGap;
                    horizontalDirection = C_RIGHT;
                }
            } else {
                if (horizontalDirection == C_RIGHT)
                {
                    x -= segmentGap;
                    horizontalDirection = C_LEFT;
                }
                else if (horizontalDirection == C_LEFT)
                {
                    x += segmentGap;
                    horizontalDirection = C_RIGHT;
                }
            }
        }
    }

    return collision;
}

bool ECE_Centipede::detectPlayerCollision(FloatRect playerBounds)
{
    bool collision = false;

    //Iterate through all segments to see if any of them collided with the player
    for (ECE_CentipedeSegment *i : segments)
    {
        if (i->getGlobalBounds().intersects(playerBounds))
        {
            collision = true;
            break;
        }
    }
    return collision;
}

void ECE_Centipede::detectLaserCollision(FloatRect laserBounds)
{
    ECE_CentipedeSegment *prev = segments.front();
    ECE_CentipedeSegment *collisionSegment = nullptr;

    //Iterate through all segments to see if any of them collided with the laser passed in
    for (ECE_CentipedeSegment *i : segments)
    {
        if (i != nullptr)
        {
            if (i->getGlobalBounds().intersects(laserBounds))
            {
                collisionSegment = i;
                break;
            }
            prev = i;
        }
        else
        {
            std::cerr << "Null pointer found in Centipede::detectLaserCollision!" << std::endl;
        }
    }

    if (collisionSegment != nullptr)
    {
        //If there was a collision, update the player's score based on the segment it collided with
        if (collisionSegment->isHead)
        {
            player->increaseScore(100);
        }
        else
        {
            player->increaseScore(10);
        }

        std::list<ECE_CentipedeSegment *>::iterator it = std::find(segments.begin(), segments.end(), collisionSegment);

        //If it was a collision with the last segment just remove it
        if (collisionSegment == segments.back())
        {
            collisionSegment->eraseSegment();
            segments.remove(collisionSegment);
        }
        else
        {
            // Check if the segment was found
            if (it != segments.end())
            {
                it++;
                if (it != segments.end())
                {
                    //Create a new centipede head at the segment after the one with the collision
                    ECE_CentipedeSegment *newHead = *it;
                    newHead->isHead = true;
                    if (!newHead->texture.loadFromFile("../assets/CentipedeHead.png"))
                    {
                        cerr << "could not create centipede head" << endl;
                    }
                    setTexture(newHead->texture);
                    segmentCounter++;
                    newHead->segmentNum = segmentCounter;
                    it++;

                    //Iterate through the segments after the new head to mark them as part of the new body until another head is found
                    if (it != segments.end())
                    {
                        for (; it != segments.end(); ++it)
                        {
                            ECE_CentipedeSegment *segment = *it;
                            if (segment->isHead)
                            {
                                break;
                            }
                            segment->segmentNum = segmentCounter;
                        }
                    }
                }
            }
            else
            {
                std::cerr << "Segment not found in detect laser coll!" << std::endl;
            }

            //Remove the segment that had a collision
            collisionSegment->eraseSegment();
            segments.remove(collisionSegment);
        }

        updateAlive();
    }
}

void ECE_CentipedeSegment::updateHead()
{

    bool atHorizontalBounds = false;
    if (horizontalDirection == C_LEFT)
    {
        x -= segmentGap;
        // Change direction when hitting the left boundary
        if (x <= 0)
        {
            horizontalDirection = C_RIGHT;
            x += segmentGap;
            atHorizontalBounds = true;
        }
    }
    else if (horizontalDirection == C_RIGHT)
    {
        x += segmentGap;
        // Change direction when hitting the right boundary
        if (x >= SCREEN_WIDTH - 20)
        {
            horizontalDirection = C_LEFT;
            x -= segmentGap;
            atHorizontalBounds = true;
        }
    }

    //If we're at a wall move vertically
    if (verticalDirection == C_DOWN && atHorizontalBounds)
    {
        y += rowSize;
        if (y >= BOTTOM_SECTION_BOUNDARY)
        {
            verticalDirection = C_UP;
            y -= rowSize;
        }
    }
    else if (verticalDirection == C_UP && atHorizontalBounds)
    {
        y -= rowSize;
        if (y <= TOP_BOUNDARY)
        {
            verticalDirection = C_DOWN;
            y += rowSize;
        }
    }

    detectMushroomCollision();
    setPosition(x, y);
}

void ECE_Centipede::moveSegment(ECE_CentipedeSegment *head)
{
    head->oldX = head->x;
    head->oldY = head->y;
    head->updateHead();

    ECE_CentipedeSegment *prev = head;
    int headSegmentNum = head->segmentNum;
    std::list<ECE_CentipedeSegment *>::iterator it = std::find(segments.begin(), segments.end(), head);

    if (it != segments.end())
    {
        it++;
        
        //Iterate through all segments that are a part of the body for this head and update their positions
        if (it != segments.end())
        {
            for (; it != segments.end(); ++it)
            {
                ECE_CentipedeSegment *segment = *it;
                if (segment->segmentNum != headSegmentNum || segment->isHead)
                {
                    break;
                }

                segment->oldX = segment->x;
                segment->oldY = segment->y;

                segment->x = prev->oldX;
                segment->y = prev->oldY;
                segment->horizontalDirection = prev->horizontalDirection;
                segment->verticalDirection = prev->verticalDirection;
                segment->setPosition(segment->x, segment->y);
                prev = segment;
            }
        }
    }
    else
    {
        std::cerr << "Segment not found!" << std::endl;
    }
}

void ECE_CentipedeSegment::eraseSegment()
{
    // Erase the current segment by drawing a black rectangle over its position
    sf::RectangleShape backgroundRect(sf::Vector2f(getGlobalBounds().width, getGlobalBounds().height));
    backgroundRect.setFillColor(sf::Color::Black);

    backgroundRect.setPosition(x, y);

    window.draw(backgroundRect);
}

ECE_Centipede::ECE_Centipede()
{
    segments.clear();
    ECE_CentipedeSegment *head = new ECE_CentipedeSegment(true, 0);
    segments.push_front(head);

    // Create body segments
    for (int i = 1; i < 11; i++)
    {
        ECE_CentipedeSegment *next = new ECE_CentipedeSegment(false, i);
        segments.push_back(next);
    }
    alive = 1;
}

void ECE_Centipede::updateAlive()
{
    if (segments.empty())
    {
        alive = 0;
    }
    else
    {
        alive = 1;
    }
}

void ECE_Centipede::updateCentipede()
{
    frameCounter++;

    if (frameCounter >= updateFrequency)
    {
        ECE_CentipedeSegment *prevSegment = nullptr;

        //Erase the previous positions of all segments
        for (ECE_CentipedeSegment *segment : segments)
        {
            segment->eraseSegment();
        }

        //Move the body for each head
        for (ECE_CentipedeSegment *segment : segments)
        {
            if (segment->isHead)
            {
                moveSegment(segment);
            }
            else
            {
                continue;
            }
        }

        updateAlive();
        frameCounter = 0;
    }
}

void ECE_Centipede::drawCentipede()
{
    for (ECE_CentipedeSegment *i : segments)
    {
        window.draw(*i);
    }
}

/**
 * @brief Checks if there is a mushroom at a given (x, y) position.
 * 
 * This function iterates through all the mushrooms in the game and checks if 
 * any mushroom's global bounds contain the provided (x, y) coordinates.
 * 
 * @param x The x-coordinate to check.
 * @param y The y-coordinate to check.
 * @return True if a mushroom is present at (x, y), false otherwise.
 */
bool isMushroomAtPosition(float x, float y)
{
    for (Mushroom* mushroom : mushrooms)
    {
        // Check if the mushroom's global bounds contain the given (x, y) coordinates
        if (mushroom->getGlobalBounds().contains(x, y))
        {
            return true; // Found a mushroom at the position
        }
    }
    
    return false;
}