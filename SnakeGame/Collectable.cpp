#include "Collectable.h"
#include <iostream>

Collectable::Collectable():
	shape(radius)
{	
	
}

void Collectable::Render(sf::RenderWindow & window)
{
	if (isActive) //Will only render if active
	{
		window.draw(shape);
	}

}

Collectable::Collectable(sf::Vector2f position_, int growAmount_, bool isActive_): //Each collectable has a position and growAmount
	position(position_),
	growAmount(growAmount_),
	isActive(isActive_) //Will either be active or not
{
	
	shape.setPosition(position);
	shape = sf::CircleShape(radius); //Each collectable is a circle

}

Collectable::~Collectable()
{
}

void Collectable::Spawn() 
{

	//Theses values can only be multiples of 10, so will be on the same 'grid' as snake position
	x = (rand() % 59) *10.0f; //Get random x value which is in the window
	y = (rand() % 79) *10.0f; //Get random y value which is in the window

	shape.setPosition({ x, y });

	growRandom = (rand() % 10);
	if (growRandom < 2) //A small percentage of the time growAmount will equal 2
	{
		growAmount = 2;
	}
	else //Most Collectable growAmounts will be 1
	{
		growAmount = 1;
	}

	if (growAmount == 1)
	{
		shape.setFillColor(sf::Color::Red); //Collectables with growAmount 1 are Red
	}
	else if (growAmount == 2)
	{
		shape.setFillColor(sf::Color::Yellow); //Collectables with growAmount 2 are Yellow
	}

	position = { x, y };
}

//The rest of the functions return and alter values

int Collectable::GetGrowAmount()
{
	return growAmount;
}

bool Collectable::GetActive()
{
	return isActive;
}

void Collectable::SetActive()
{
	isActive = true;
}

void Collectable::SetNotActive()
{
	isActive = false;
}

sf::Vector2f Collectable::GetPosition()
{
	return position;
}

