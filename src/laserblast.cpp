/*
Author: Arina Shah
Class: ECE4122
Last Date Modified: 9/29/2024
Description: This file defines the functions that are part of the ECE_LaserBlast class and any necessary helper functions.
*/
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <list>
#include <iostream>
#include <define.hpp>
#include <laserblast.hpp>
#include <starship.hpp>
#include <spider.hpp>
#include <centipede.hpp>

#include <list>

using namespace std;

using ::cerr;
using ::endl;
using namespace sf;


list<ECE_LaserBlast*> lasers; //list to allow for multiple lasers
int laserId = 0; //ID associated with each laser

ECE_LaserBlast::ECE_LaserBlast(int x, int y) {
    this->x = x;
    this->y = y;

    laserShape = sf::RectangleShape(sf::Vector2f(LASER_WIDTH, LASER_HEIGHT));
    laserShape.setFillColor(sf::Color::Red);
    laserShape.setPosition(x, y);
    this->id = laserId;
    laserId++;
}

void ECE_LaserBlast::detectMushroomCollision() {
    int points = 0;
    
    //Iterate through all the mushrooms and check if a mushroom collided with this laser
    for (auto it = mushrooms.begin(); it != mushrooms.end(); ) {
        Mushroom* mushroom = *it;
        if (mushroom != nullptr) {
            if (laserShape.getGlobalBounds().intersects(mushroom->getGlobalBounds())) {

                //If the mushroom has been hit twice, it is removed
                bool removed = mushroom->laserHit(this->id);
                if (removed) {
                    points++;
                    mushroom->eraseMushroom();
                    delete mushroom;
                    it = mushrooms.erase(it); 
                    std::cout << "Mushroom removed" << std::endl;
                } else {
                    ++it;
                }
            } else {
                ++it;
            }
        } else {
            std::cerr << "Null pointer found in LaserBlast::detectMushroomCollision!" << std::endl;
            //it = mushrooms.erase(it); 
        }
    }

    player->increaseScore(points); 
}

void ECE_LaserBlast::detectCentipedeCollision() {
    centipede->detectLaserCollision(laserShape.getGlobalBounds());
}

void ECE_LaserBlast:: detectSpiderCollision() {
    //If the laser collided with the spider kill the spider and increase the player's points
    if (laserShape.getGlobalBounds().intersects(spider->getGlobalBounds())) {
        if (spider->alive) {
            spider->kill();
            player->increaseScore(300);
        } 
    }
}

bool ECE_LaserBlast::updatePosition() {
    bool removed = false;
    y--;

    //If the laser passes the top boundary remove it
    if (y <= TOP_BOUNDARY) {
        removed = true;
    }
    laserShape.setPosition(x, y);
    return removed;
}

void updateLasers() {
    //Iterate through all the lasers to erase their last position, update their new position, remove them if necessary, detect collisions, and draw them.
    if (!lasers.empty()) {
        for (auto it = lasers.begin(); it != lasers.end(); ) {
            ECE_LaserBlast* laser = *it;
            if (laser != nullptr) {
                laser->eraseLastPosition();
                bool removed = laser->updatePosition();
                if (removed) {
                    delete laser;
                    it = lasers.erase(it);
                    std::cout << "Laser removed" << std::endl;
                } else {
                    laser->detectMushroomCollision();
                    laser->detectCentipedeCollision();
                    laser->detectSpiderCollision();
                    laser->drawLaser();
                    ++it;
                }
            } else {
                std::cerr << "Null pointer found in LaserBlast::updateLasers!" << std::endl;
                ++it;
            }
        }
    }
}

void ECE_LaserBlast::drawLaser() {
    window.draw(laserShape);
}

void ECE_LaserBlast::eraseLastPosition() {
    // Create a rectangle representing the last position of the laser
    sf::RectangleShape backgroundRect(sf::Vector2f(LASER_WIDTH, LASER_HEIGHT));
    backgroundRect.setFillColor(sf::Color::Black);
    backgroundRect.setPosition(x, y);

    window.draw(backgroundRect);
}