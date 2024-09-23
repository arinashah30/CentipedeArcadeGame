// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <list>
#include <iostream>
#include <define.hpp>

using std::cerr;
using std::endl;
// Make code easier to type with "using namespace"
using namespace sf;

class Starship: public sf::Sprite {

    public:

        int x;
        int y;

        int lives;
        int score = 0;

        sf::Texture texture;

        void detectCollision();

        void move();

        void shoot();
    
};





