#pragma once
#include "SFML/Graphics.hpp"

#define MAX_NUMBER_OF_ITEMS 4

class Menu //This class creates a template for the Main Menu of the Game
{
private:
	int selectedItemIndex, i;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS]; //Create an array of text, with size equal to 'MAX_NUMBER_OF_ITEMS'
public:
	int GetPressedItem() { return selectedItemIndex; } //This function is called when 'Enter' is pressed, it returns the value of the current Menu selection
	Menu(float width, float height); //Menu function will take in width and height of the window
	~Menu();
	void Render(sf::RenderWindow &window); //Displays menu in window
	void MoveUp();
	void MoveDown();

};

