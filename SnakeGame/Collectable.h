#pragma once
#include <SFML/Graphics.hpp>
#include "Water.h"

class Collectable
{
private:
	bool isActive; //Collectable will only render if active
	float x, y, radius = 5;
	int growAmount, growRandom; //Each collectable will have grow amount 1 or 2, which is done randomly when spawned
	sf::Vector2f position;
	sf::CircleShape shape;
public:
	void Render(sf::RenderWindow& window);
	void Spawn(); //Will calculate random position and growAmount
	int GetGrowAmount();
	Collectable();
	Collectable(sf::Vector2f position, int GrowAmount, bool isActive);
	bool GetActive();
	void SetActive();
	void SetNotActive();
	sf::Vector2f GetPosition();
	~Collectable();
};
