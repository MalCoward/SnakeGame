/*
  Games Development with C++ GAV1031-N
  Snake Game ICA Project 
  Malachi Leon Dade Coward
  V8009688
*/

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
	
	std::cout << "SnakeGame: Starting" << std::endl;

	Game game;
	game.Run(); //Run Start Menu

    std::cout << "SnakeGame: Finished" << std::endl;

    return 0;
}
