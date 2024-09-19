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

class ECE_Centipede: public sf::Sprite {

    public:

        ECE_Centipede* prev; //pointer to sprite before
        ECE_Centipede* next; //pointer to sprite after

        int x;
        int y;

        sf::Texture texture;

        ECE_Centipede(bool isHead);
    

    int calculateSegments(); //class to calculate segments, will redraw texture if new segment and body needs to be changed to head


    void detectCollision();
};

ECE_Centipede* createCentipede();