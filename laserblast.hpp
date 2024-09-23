// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <list>
#include <iostream>
#include <define.hpp>

#include <list>

using namespace std;

using ::cerr;
using ::endl;
// Make code easier to type with "using namespace"
using namespace sf;


class ECE_LaserBlast: public sf::Sprite {
    public:

        int x;
        int y;

        ECE_LaserBlast(int x, int y);

    void detectCollision();

    void updateLaserBlasts();
};

list<ECE_LaserBlast*> lasers();