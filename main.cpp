#include <SFML/Graphics.hpp>
#include <centipede.hpp>
#include <mushroom.hpp>
#include <starship.hpp>
#include <define.hpp>

using namespace sf;
int main()
{
    while(1) {
        // Create a window
        sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Scale Image to Fit Rectangle");
        // Load an image into a texture
        sf::Texture texture;
        if (!texture.loadFromFile("StartupScreenBackGround.png")) {
            return -1; // Error loading image
        }

        while(1) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) //wait for user to press enter to start the game
            {
                break;
            }
        }
        
        // Create a sprite and set the texture
        sf::Sprite sprite;
        sprite.setTexture(texture);
        // Define the target rectangle dimensions
        sf::FloatRect targetRect(0.f, 0.f, 800.f, 600.f); // Position (x, y) and size (width, height)
        // Get the original size of the sprite
        sf::FloatRect originalSize = sprite.getGlobalBounds();
        // Calculate scale factors
        float scaleX = targetRect.width / originalSize.width;
        float scaleY = targetRect.height / originalSize.height;
        // Set the scale of the sprite to fit the target rectangle
        sprite.setScale(scaleX, scaleY);
        // Set the position of the sprite to the target rectangle's position
        sprite.setPosition(targetRect.left, targetRect.top);

        ECE_Centipede* centipede = createCentipede();
        Starship* player = new Starship();
        generateMushrooms();
        bool gameOver = false;


        // Main loop
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                window.close();
            }
            window.clear(sf::Color::White);
            window.draw(sprite);
            window.display();

            centipede->updateCentipede();

            if (player->lives == 0) {
                gameOver = true;
            } else if (!centipede->alive) {
                gameOver = true;
            }

            if (gameOver) {
                //restart();
                break;
            }
        }
    }
    return 0;
}


/*

while (entire game loop)
    while (start screen loop)
    while (playing loop) {
        break when game over
    }
*/