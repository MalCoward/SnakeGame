#include "Water.h"

void Water::Render(sf::RenderWindow & window)
{
	window.draw(shape);
}

void Water::WaterDrop()
{
	position.y += 1; //Water Moves down 1 every update
	shape.setPosition(position);
}

Water::Water(sf::Vector2f position_, sf::Vector2f size_): //Water will be created in the Game.cpp
	position(position_),
	size(size_)
{
	shape = sf::RectangleShape(size);
	shape.setFillColor(sf::Color::Blue);
	shape.setPosition(position);
}

Water::~Water()
{
}

sf::Vector2f Water::GetPosition() //Returns position values
{
	return position;
}
