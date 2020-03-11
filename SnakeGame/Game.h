#pragma once
#include "Collectable.h"
#include "Snake.h"
#include "Water.h"
#include "Menu.h"
#include <string>
#include <fstream>

class Game
{
private:
	Water waterLevel;
	int x, z, i, j, highScore, winScore, totalDistance, minDistance = 1400; //minDistance = Screen Height + Screen Width
	bool onePlayer, twoPlayer, playerAI, playerOneDied, playerTwoDied, hasTarget = false;
	Collectable collectables[5], closestCollect; //Create Collectable array
	Snake snakes[2]; //Create an array for all Snakes in Game
	sf::Vector2f position, targetPos, breathPosition, breathSize = { x, 10 };
	sf::RectangleShape breathOne, breathTwo; //Create Snake Breath displays in window
	sf::Font font;
	sf::Text text, textTwo, winText;
	std::string score1, score2, scoreDisplay;
public:
	void Collisions(); //Test different Collisions for Snake
	void Run();
	void OnePlayerGame(); //Create Snake and values for One Player Game
	void TwoPlayerGame(); //Create Snakes and values for Two Player Game
	void PlayerAIGame(); //Create Snakes and values for AI Game
	void StartGame();
	Game();
	~Game();
};

