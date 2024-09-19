// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <list>
#include <iostream>

using std::cerr;
using std::endl;
// Make code easier to type with "using namespace"
using namespace sf;

class Starship: public sf::Sprite {

    public:

        int x;
        int y;

        int lives;

        sf::Texture texture;



    void detectCollision() {
        bool collision = false;

        if (collision) {
            lives -= 1;
        }
    }

    void move() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            if (x - 1 >= 0) {
                x = x - 1;
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            if (x + 1 <= 800) {
                x = x + 1;
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            if (y + 1 <= 600) {
                y = y + 1;
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down))
        {
            if (y - 1 >= 0) {
                y = y - 1;
            }
        }
    }

    void shoot() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {

        }
    }

    
};





