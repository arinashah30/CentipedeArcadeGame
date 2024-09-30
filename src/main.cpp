/*
Author: Arina Shah
Class: ECE4122
Last Date Modified: 9/29/2024
Description: This file defines the main game loop and updates each component of the game.
*/
#include <SFML/Graphics.hpp>
#include <centipede.hpp>
#include <mushroom.hpp>
#include <starship.hpp>
#include <define.hpp>
#include <spider.hpp>

#include <unistd.h>
#include <limits.h>
#include <iostream>

using namespace sf;

int getPlayerInputs();
void gameReset();
void playerDied();

sf::Clock delayClock;
sf::Clock centipedeClock;
RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "ECE Centipede Game");
Font font;
Starship *player = new Starship();
Spider *spider;
float laserCooldown = 0.5f;
float timeSinceLastShot = 0.0f;

void shoot();

int main()
{
    if (!font.loadFromFile("../assets/Roboto-Regular.ttf"))
    {
        cerr << "Error loading font" << endl;
        return -1;
    }

    Texture texture;
    Sprite sprite;
    if (!texture.loadFromFile("../assets/StartupScreenBackGround.png"))
    {
        return -1; // Error loading image
    }

    sprite.setTexture(texture);
    // Define the target rectangle dimensions
    FloatRect targetRect(0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT); // Position (x, y) and size (width, height)
    // Get the original size of the sprite
    FloatRect originalSize = sprite.getGlobalBounds();
    // Calculate scale factors
    float scaleX = targetRect.width / originalSize.width;
    float scaleY = targetRect.height / originalSize.height;
    // Set the scale of the sprite to fit the target rectangle
    sprite.setScale(scaleX, scaleY);
    // Set the position of the sprite to the target rectangle's position
    sprite.setPosition(targetRect.left, targetRect.top);

    // Window loop
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        if (!texture.loadFromFile("../assets/StartupScreenBackGround.png"))
        {
            return -1; // Error loading image
        }

        sprite.setTexture(texture);
        window.clear(Color::White);
        window.draw(sprite);
        window.display();

        while (1)
        {
            if (Keyboard::isKeyPressed(Keyboard::Enter)) // wait for user to press enter to start the game
            {
                break;
            }
        }
        window.clear(Color::Black);
        window.display();

        //Create game elements and define variables
        centipede = new ECE_Centipede();
        spider = new Spider();
        if (spider == nullptr)
        {
            std::cerr << "Failed to create Spider!" << std::endl;
            return -1;
        }
        generateMushrooms();
        bool gameOver = false;

        //Create score and lives text elements
        Text scoreText;
        Text livesText;
        scoreText.setFont(font);
        livesText.setFont(font);
        scoreText.setString("Score: 0");
        livesText.setString("Lives: " + std::to_string(player->lives));
        scoreText.setFillColor(Color::White);
        livesText.setFillColor(Color::White);
        scoreText.setPosition((SCREEN_WIDTH / 2) - 130, 10);
        livesText.setPosition((SCREEN_WIDTH / 2) + 50, 10);

        //Main game loop
        while (1)
        {
            //Clear window then draw elements
            window.clear(Color::Black);
            window.draw(scoreText);
            window.draw(livesText);
            drawMushrooms();
            centipede->drawCentipede();
            window.draw(*player);
            if (spider->alive)
            {
                window.draw(*spider);
            }

            //Update clocks
            float deltaTime = delayClock.restart().asSeconds();
            timeSinceLastShot += deltaTime;
            float centipedeDT = centipedeClock.restart().asSeconds(); // Calculate delta time for each frame

            //Update elements and check for player input
            centipede->updateCentipede();
            int playerDirection = getPlayerInputs();
            player->move(playerDirection);
            if (centipede->detectPlayerCollision(player->getGlobalBounds()))
            {
                playerDied();
            }
            if (Keyboard::isKeyPressed(Keyboard::Space) && timeSinceLastShot >= laserCooldown) // wait for user to press enter to start the game
            {
                shoot();
                timeSinceLastShot = 0.0f;
            }
            updateLasers();
            if (spider != nullptr)
            {
                spider->update();
            }
            if (spider->checkPlayerCollision())
            {
                playerDied();
            }

            //Update score and lives text
            scoreText.setString("Score: " + std::to_string(player->score));
            livesText.setString("Lives: " + std::to_string(player->lives));

            //Check if the game is over
            if (player->lives == 0)
            {
                gameOver = true;
            }
            else if (!centipede->alive)
            {
                gameOver = true;
            }

            //If the game is over, reset the game, break, and go back to the start screen
            if (gameOver)
            {
                gameReset();
                break;
            }
            window.display();
        }
    }
    return 0;
}

int getPlayerInputs()
{
    if (Keyboard::isKeyPressed(Keyboard::Left))
    {
        return LEFT;
    }
    else if (Keyboard::isKeyPressed(Keyboard::Right))
    {
        return RIGHT;
    }
    else if (Keyboard::isKeyPressed(Keyboard::Up))
    {
        return UP;
    }
    else if (Keyboard::isKeyPressed(Keyboard::Down))
    {
        return DOWN;
    }
    return NONE;
}

void shoot()
{
    if (player != nullptr)
    {
        ECE_LaserBlast *newLaser = new ECE_LaserBlast(player->x, player->y);
        lasers.push_front(newLaser);
        std::cout << "Laser shot from position: (" << player->x << ", " << player->y << ")" << std::endl;
    }
    else
    {
        std::cerr << "Player is null!" << std::endl;
    }
}

void gameReset()
{
    mushrooms.clear();
    player->reset();
}

void playerDied()
{
    player->decreaseLives();
    centipede = new ECE_Centipede();
    player->x = SCREEN_WIDTH / 2;
    player->y = BOTTOM_SECTION_BOUNDARY;
    spider->reset();
}