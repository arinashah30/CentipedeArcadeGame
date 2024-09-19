// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <list>
#include <iostream>

using std::cerr;
using std::endl;
// Make code easier to type with "using namespace"
using namespace sf;

std::list<sf::Sprite> segments; //list to keep track of segments

class Mushroom: public sf::Sprite {

    public:

        int x;
        int y;

        sf::Texture texture;

        Mushroom();
    

    void detectCollision();
};

bool generateMushrooms();