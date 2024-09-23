// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <list>
#include <iostream>
#include <centipede.hpp>
#include <define.hpp>

using std::cerr;
using std::endl;
// Make code easier to type with "using namespace"
using namespace sf;

ECE_Centipede::ECE_Centipede(bool isHead) {
            if (isHead) {
                if (!texture.loadFromFile("CentipedeHead.png")) {
                    cerr << "could not create centipede head" << endl;
                }
                setTexture(texture);
            } else {
                if (!texture.loadFromFile("CentipedeBody.png")) {
                    cerr << "could not create centipede head" << endl;
                }
                setTexture(texture); 
            }
            this->alive = 1;
}

int ECE_Centipede::calculateSegments() { //class to calculate segments, will redraw texture if new segment and body needs to be changed to head
        bool newSegment = false;

        if (!prev) { //no previous == new head
            newSegment = true;
        }

        if (newSegment) {
            sf::Texture texture;
            if (!texture.loadFromFile("CentipedeHead.png")) {
                return -1;
            }
            setTexture(texture);
        }
    }

void ECE_Centipede::detectCollision() {
        bool collision = false;

        if (collision) { //disconnect the segments
            ECE_Centipede* prevSegment = prev;
            prevSegment->next = nullptr;
            prev = nullptr;
            calculateSegments();
        }
}

int ECE_Centipede::detectMushroomCollision() {
    int mushroomCollision = -1; //0 == left, 1 == right, 2 == down
    for (ECE_Centipede const& i : segments) {

    }
    return mushroomCollision;
}

void ECE_Centipede::updateLocation() {
    //iterate through segments
    for (ECE_Centipede const& i : segments) {
        int mushroomCollision = detectMushroomCollision();
        switch (mushroomCollision)
        {
        case 0:
            //move down
            break;
        case 1:
            //move down
            break;
        case 2:
            break;
        default:
            break;
        }
    }
}

ECE_Centipede* createCentipede() {
    ECE_Centipede* head = new ECE_Centipede(true);
    ECE_Centipede* temp = head;
    for (int i = 0; i < 11; i++) { //create body
        ECE_Centipede* next = new ECE_Centipede(false);
        temp->next = next;
        next->prev = temp;
        temp = next;
    }
    return head;
}

void ECE_Centipede::updateCentipede() {
    this->updateLocation();
    this->detectCollision();
}