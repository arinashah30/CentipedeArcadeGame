#include <random>
#include <mushroom.hpp>
#include <list>

using namespace std;


class Mushroom: public sf::Sprite {

    int x;
    int y;

    sf::Texture texture;

    public:
        Mushroom(int x, int y) {
            if (!texture.loadFromFile("Mushroom0.png")) {
                cerr << "could not create mushroom" << endl;
            }
            setTexture(texture);
            this->x = x;
            this->y = y;
        }

    void detectCollision() {

    }
};

list<Mushroom*> mushrooms(30);

bool generateMushrooms() {
    default_random_engine generator;
    uniform_int_distribution<int> distribution_x(0,800);
    uniform_int_distribution<int> distribution_y(0,600);

    for (int i = 0; i < 30; i++) {
        int x = distribution_x(generator);
        int y = distribution_y(generator);
        Mushroom* newMushroom = new Mushroom(x, y);

        mushrooms.push_front(newMushroom);
    }
}