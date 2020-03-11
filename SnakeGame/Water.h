#pragma once
#include <SFML/Graphics.hpp>

class Water
{
private:
	sf::Vector2f size, position;
	sf::RectangleShape shape; //My Water is just a huge Rectangle
public:
	void Render(sf::RenderWindow& window); //Renders Water to window
	void WaterDrop(); //Drop Water Function
	Water(sf::Vector2f position, sf::Vector2f size);
	~Water();
	sf::Vector2f GetPosition();
};

