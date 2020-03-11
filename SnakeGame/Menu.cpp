#include "Menu.h"

Menu::Menu(float width, float height) //Width and Height of the window
{

	if (!font.loadFromFile("arial.ttf")) //Loads font used for menu
	{
		//handle error
	}

	menu[0].setFont(font);
	menu[0].setColor(sf::Color::Red); //First option in menu set to Red by default as this will be the current selected option
	menu[0].setString("One Player");
	menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 1)); //Set position of first menu item

	menu[1].setFont(font);
	menu[1].setColor(sf::Color::White); //The rest of the menu options set to White by default, this will be changed to Red upon arrow key movement
	menu[1].setString("Two Player");
	menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	menu[2].setFont(font);
	menu[2].setColor(sf::Color::White);
	menu[2].setString("One Player VS CPU");
	menu[2].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));

	menu[3].setFont(font);
	menu[3].setColor(sf::Color::White);
	menu[3].setString("Quit");
	menu[3].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 4));

	selectedItemIndex = 0; //Selected Item is first in array by default

}

Menu::~Menu()
{
}

void Menu::Render(sf::RenderWindow &window)
{

	for (i = 0; i < MAX_NUMBER_OF_ITEMS; i++) //For Each item is Menu array
	{
		window.draw(menu[i]);
	}

}

void Menu::MoveUp() //When Up arrow key is pressed
{

	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex--; //Selected Item 'Moves Up' to next item in array
		menu[selectedItemIndex].setColor(sf::Color::Red);
	}

}

void Menu::MoveDown() //When Down arrow key is pressed
{

	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex++; //Selected Item 'Moves Down' to next item in array
		menu[selectedItemIndex].setColor(sf::Color::Red);
	}

}
