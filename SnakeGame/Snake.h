#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include<list>

enum class EDirection //Created EDirections so it's not as complicated whilst coding
{
	eNorth,
	eEast,
	eSouth,
	eWest,
	eNoDirection,
};

class Snake
{
private:
	float x, y;
	int growAmount, snakeSize, snakeBreath = 300;
	sf::Vector2f breathPos, size, position;
	bool isAlive; //Snake will not be Rendered to the window if it is not Alive
	EDirection direction, desiredDirection;
	sf::Color colour;
	sf::RectangleShape shape; //My Snake Segments are Rectangles
	std::list<sf::Vector2f> snakeSegments; //Create a list of all Segments in Snake
public:
	void Render(sf::RenderWindow& window); //Displays Snake
	Snake();
	Snake(sf::Vector2f position, bool IsAlive, int SnakeBreath, int BreathYPos); //Each Snake has a positon and will be Alive or not, it will also have 'Breath' which will be displayed at a certain position on-screen
	~Snake();
	void ResetSnake(); //Used when Game is reset, resets all values of Snake
	void ResetBreath();
	void SetBreathPos(sf::Vector2f Pos); //Sets position of breath display on the Window
	void LoseBreath();
	void Grow(int growAmount); //When a Snake eats a Collectable it will grow in size
	void Spawn();
	void SnakeOneDirection(); //Player One Movement controls
	void SnakeTwoDirection(); //Player Two Movement controls
	void SnakeAIMovement(sf::Vector2f CollectPos); //Movement for AI Snake
	void Update();
	void Sink(); //Used When Snake goes to top of water
	bool CheckOtherSnakeCollision(const Snake& other) const; //Collisions with other Snakes
	bool CheckSelfCollision(); //Collisions with own tail

	//The rest of the functions return and alter values
	int GetBreath();
	sf::Vector2f GetPosition();
	void SetAlive();
	void SetNotAlive();
	sf::Vector2f GetBreathPos();
	bool GetAlive();
	int GetSnakeSize();
};

