#include <random>
#include "mushroom.hpp"
#include <list>
#include <define.hpp>

using namespace std;

Mushroom::Mushroom(int x, int y) {
            if (!texture.loadFromFile("Mushroom0.png")) {
                cerr << "could not create mushroom" << endl;
            }
            setTexture(texture);
            this->x = x;
            this->y = y;
            this->hitTimes = 0;
}

void Mushroom::detectCollision() {
        bool collision = false;

        if (collision) {
            hitTimes++;
            if (hitTimes == 1) {
                if (!texture.loadFromFile("Mushroom1.png")) {
                    cerr << "could not create mushroom" << endl;
                }
                setTexture(texture);
            } else if (hitTimes == 2) {
                mushrooms.remove(this);
            }
        }
}


bool generateMushrooms() {
    default_random_engine generator;
    uniform_int_distribution<int> distribution_x(0,SCREEN_WIDTH);
    uniform_int_distribution<int> distribution_y(BOTTOM_SECTION_BOUNDARY,SCREEN_HEIGHT);

    for (int i = 0; i < 30; i++) {
        int x = distribution_x(generator);
        int y = distribution_y(generator);
        Mushroom* newMushroom = new Mushroom(x, y);

        mushrooms.push_front(newMushroom);
    }
}

void Mushroom::updateMushrooms() {

    for (Mushroom const& i : mushrooms) {
        detectCollision();
    }
}