/*
Author: Arina Shah
Class: ECE4122
Last Date Modified: 9/29/2024
Description: This file has global definitions and variables used throughout the game.
*/

#ifndef DEFINE_HPP
#define DEFINE_HPP

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define BOTTOM_SECTION_BOUNDARY 500
#define LASER_WIDTH 5
#define LASER_HEIGHT 20
#define PLAYER_Y_MAX 300
#define TOP_BOUNDARY 100

enum PLAYER_DIRECTION
{
    LEFT,
    RIGHT,
    UP,
    DOWN,
    NONE
};

enum CENTIPEDE_DIRECTION
{
    C_LEFT,
    C_RIGHT,
    C_DOWN,
    C_UP
};

extern sf::RenderWindow window;

class Starship;
extern Starship *player;

class ECE_LaserBlast;
extern std::list<ECE_LaserBlast *> lasers;

#endif