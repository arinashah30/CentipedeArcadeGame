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



class ECE_Centipede: public sf::Sprite {
    private:
        std::list<ECE_Centipede> segments; //list to keep track of segments

    public:

        ECE_Centipede* prev; //pointer to sprite before
        ECE_Centipede* next; //pointer to sprite after
        int direction; //0 == left, 1 == right
        int alive;

        int x;
        int y;

        sf::Texture texture;

        ECE_Centipede(bool isHead);
    

    int calculateSegments(); //class to calculate segments, will redraw texture if new segment and body needs to be changed to head


    void detectCollision();

    void updateLocation();

    void updateCentipede();

    int detectMushroomCollision();
};

ECE_Centipede* createCentipede();