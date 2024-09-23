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



class Spider: public sf::Sprite {
    private:
        

    public:

        int alive;

        int x;
        int y;

        sf::Texture texture;


    void updateLocation();

};