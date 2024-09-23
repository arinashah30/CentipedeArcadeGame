// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <list>
#include <iostream>
#include <starship.hpp>
#include <define.hpp>

using std::cerr;
using std::endl;
// Make code easier to type with "using namespace"
using namespace sf;

Starship::Starship() {
    this->lives = 3;
    this->score = 0;
    if (!texture.loadFromFile("StarShip.png")) {
        cerr << "could not create starship" << endl;
    }
    setTexture(texture);
    this->x = SCREEN_WIDTH / 2;
    this->y = BOTTOM_SECTION_BOUNDARY;
}

void Starship::detectCollision() {
        bool collision = false;

        if (collision) {
            this->lives -= 1;
        }
}

void Starship::move() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            if (x - 1 >= 0) {
                x = x - 1;
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            if (x + 1 <= SCREEN_WIDTH) {
                x = x + 1;
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            if (y + 1 <= PLAYER_Y_MAX) {
                y = y + 1;
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down))
        {
            if (y - 1 >= BOTTOM_SECTION_BOUNDARY) {
                y = y - 1;
            }
        }
    }

void Starship::shoot() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {

        }
    }





