// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <list>
#include <iostream>
#include <define.hpp>
#include <laserblast.hpp>

#include <list>

using namespace std;

using ::cerr;
using ::endl;
// Make code easier to type with "using namespace"
using namespace sf;

ECE_LaserBlast::ECE_LaserBlast(int x, int y) {
    this->x = x;
    this->y = y;

    sf::RectangleShape laserShape(sf::Vector2f(LASER_WIDTH, LASER_HEIGHT));
    laserShape.setFillColor(sf::Color::Red);
    laserShape.setPosition(x, y);


    setTextureRect(sf::IntRect(0, 0, LASER_WIDTH, LASER_HEIGHT)); 
    setPosition(x, y);
}


void ECE_LaserBlast:: detectCollision() {
        bool collision = false;

        //check if collision with mushroom or centipede

        if (collision) { //disconnect the segments

        }
    }

void ECE_LaserBlast:: detectMushroomCollision() {
    bool collision = true;
    for (Mushroom* i : mushrooms) {
        if (getGlobalBounds().intersects(i->getGlobalBounds())) {
            i->laserHit();
        }
    }
    
}

void ECE_LaserBlast::detectCentipedeCollision() {

}

void ECE_LaserBlast:: detectSpiderCollision() {

}

void ECE_LaserBlast::update() {
    
}


