// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <list>
#include <iostream>
#include <spider.hpp>
#include <define.hpp>

using std::cerr;
using std::endl;
// Make code easier to type with "using namespace"
using namespace sf;

Spider::Spider() {
    if (!texture.loadFromFile("spider.png")) {
        cerr << "could not create spider" << endl;
    }
    setTexture(texture);
}