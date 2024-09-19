// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <list>
#include <iostream>

using std::cerr;
using std::endl;
// Make code easier to type with "using namespace"
using namespace sf;

class ECE_Centipede: public sf::Sprite {

    public:

        ECE_Centipede* prev; //pointer to sprite before
        ECE_Centipede* next; //pointer to sprite after

        int x;
        int y;

        sf::Texture texture;

        ECE_Centipede(bool isHead) {
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
        }

    

    int calculateSegments() { //class to calculate segments, will redraw texture if new segment and body needs to be changed to head
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


    void detectCollision() {
        bool collision = false;

        if (collision) { //disconnect the segments
            ECE_Centipede* prevSegment = prev;
            prevSegment->next = nullptr;
            prev = nullptr;
            calculateSegments();
        }
    }

    
};

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
