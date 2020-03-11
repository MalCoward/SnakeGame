#include "Game.h"
using namespace std;

Game::Game() :
	waterLevel(sf::Vector2f(0, 100), sf::Vector2f(600, 800)) //Create Water 
{
	
}

void Game::Run()
{
	
	sf::RenderWindow window(sf::VideoMode(600, 800), "C++ Snake ICA : "); //Create window for Main Menu

	//Display Title 
	font.loadFromFile("arial.ttf");
	text.setFont(font);
	text.setFillColor(sf::Color::White);
	text.setStyle(sf::Text::Bold);
	text.setPosition(20, 20);
	text.setCharacterSize(40);
	text.setString("Snake Game \nMalachi Leon Dade Coward \nV8009688");

	ifstream scoreFile; 
	scoreFile.open("HighScore.txt"); //I have a file which contains high score for Game

	if (scoreFile.fail()) //If HighScore.txt cannot be opened 
	{
		cerr << "Error Opening File" << endl; 
		exit(1);
	}

	scoreFile >> highScore;
	scoreDisplay = to_string(highScore);

	textTwo.setFont(font);
	textTwo.setFillColor(sf::Color::White);
	textTwo.setStyle(sf::Text::Bold);
	textTwo.setPosition(20, 300);
	textTwo.setCharacterSize(40);
	textTwo.setString("High Score:\n" + scoreDisplay); //High Score displayed on Main Menu and is updated whenever High Score changes

	//Display Start menu
	Menu menu(window.getSize().x, window.getSize().y); //Create Menu in the window
	while (window.isOpen())
	{

		// Handle any pending SFML events
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up: //Move up selected in Menu
					menu.MoveUp();
					break;
				case sf::Keyboard::Down: //Move up selected in Menu
					menu.MoveDown();
					break;
				case sf::Keyboard::Return: //When Enter pressed
					switch (menu.GetPressedItem())
					{
					case 0: //If One Player pressed
						onePlayer = true;
						twoPlayer = false;
						playerAI = false;
						window.close();
						OnePlayerGame(); //Create Snake and values for One Player Game
						StartGame(); //Start Game
						break;
					case 1: //If Two Player pressed
						twoPlayer = true;
						onePlayer = false;
						playerAI = false;
						window.close();
						TwoPlayerGame(); //Create Snakes and values for Two Player Game
						StartGame(); //Start Game
						break;
					case 2: //If One Player VS CPU pressed
						playerAI = true;
						onePlayer = false;
						twoPlayer = false;
						window.close();
						PlayerAIGame(); //Create Snakes and values for AI Game
						StartGame(); //Start Game
						break;
					case 3: //If Quit pressed
						window.close();
						break;
					}
					window.close();
					break;
				}
				
				break;
			case sf::Event::Closed:
				window.close();
				break;
			default:
				break;
			}

		}

		window.clear();

		window.draw(text);
		window.draw(textTwo);
		menu.Render(window); //Render Menu to window

		window.display(); //Display window

	}

}

void Game::OnePlayerGame() //For One Player Game
{

	//Spawn Snake
	for (i = 0; i < 1; i++)
	{
		snakes[i].Spawn();
		snakes[i].SetAlive();
		snakes[i].ResetBreath();
	}

	//Snake Breath Set Position
	snakes[0].SetBreathPos({ 10,10 });
	breathOne.setPosition(snakes[0].GetBreathPos());

}

void Game::TwoPlayerGame() //For Two Player Game
{

	//Spawn Snakes
	for (Snake& s : snakes)
	{
		s.Spawn();
		s.SetAlive();
		s.ResetBreath();
	}

	//Snake Breath Set Position
	snakes[0].SetBreathPos({ 10,10 });
	breathOne.setPosition(snakes[0].GetBreathPos());
	snakes[1].SetBreathPos({ 10,30 });
	breathTwo.setPosition(snakes[1].GetBreathPos());

}

void Game::PlayerAIGame() //For AI Game
{

	//Spawn Snakes
	for (Snake& s : snakes)
	{
		s.Spawn();
		s.SetAlive();
		s.ResetBreath();
	}

	//Snake Breath Set Position
	snakes[0].SetBreathPos({ 10,10 });
	breathOne.setPosition(snakes[0].GetBreathPos());
	snakes[1].SetBreathPos({ 10,30 });
	breathTwo.setPosition(snakes[1].GetBreathPos());

}

void Game::StartGame() //Start Game
{

	sf::RenderWindow window(sf::VideoMode(600, 800), "C++ Snake ICA : "); //Create a new window on the screen
	srand(time(nullptr));
	sf::Clock clock;
	clock.restart();

	//Spawn Collectables and put them in Collectables array
	for (z = 0; z < 5; z++)
	{
		collectables[z].Spawn();
		collectables[z].SetNotActive(); //Collectables are 'NotActive' by default

	}
	
	// Main loop that continues until we call window.close()
	while (window.isOpen())
	{
		// Handle any pending SFML events
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			default:
				break;
			}
		}

		//Snake Movement
		if (onePlayer) //For One Player Game
		{
			snakes[0].SnakeOneDirection();
		}
		else if (twoPlayer) //For Two Player Game
		{
			//Player One movement controls are different to Player Two movement controls
			snakes[0].SnakeOneDirection();
			snakes[1].SnakeTwoDirection();
		}
		else if (playerAI) //For AI Game
		{
			snakes[0].SnakeOneDirection();
			if (hasTarget) //If AI Snake has a Collectable to go for
			{
				snakes[1].SnakeAIMovement(targetPos); //AI Snake Movement
			}
		}

		//Update Snake position
		for (i = 0; i < 2; i++)
		{
			snakes[i].Update();
		}

		//Snake on Snake Collisions
		Snake snake;
		if (!onePlayer) //One test if more than one Snake
		{
			for (i = 0; i < 2; i++)
			{
				for (j = 0; j < 2; j++)
				{
					if (i != j) //Snake won't test against itself 
					{

						if (snakes[i].CheckOtherSnakeCollision(snakes[j])) //Checks every Snake against every other Snake
						{
							snakes[i].SetNotAlive(); //If Snake collided with another Snake it will die
						}

					}
				}
			}
		}

		//Check self collisions
		for (i = 0; i < 2; i++)
		{
			if (snakes[i].CheckSelfCollision()) //Each Snake tests against own tail
			{
				snakes[i].SetNotAlive();
			}
		}
		
		//Water Drop
		waterLevel.WaterDrop();		
		
		//Collectable going above water level
		for (z = 0; z < 5; z++)
		{
			if (collectables[z].GetPosition().y < waterLevel.GetPosition().y) //If Collectable goes above water level
			{
				collectables[z].SetNotActive(); 
				while (collectables[z].GetPosition().y < waterLevel.GetPosition().y)
				{
					collectables[z].Spawn(); //Give Collectable new position below water level
				}
			}
		}
		
		window.clear();

		//Check for Food, Wall and Water Collisions
		Collisions();

		//Render Water Level
		waterLevel.Render(window);

		//Render Snakes
		if (onePlayer) //For One Player Game
		{
			snakes[0].Render(window);
		}
		else if (twoPlayer || playerAI) //For Two Player Game or AI Game
		{
			for (Snake& s : snakes) //Loop through all Snakes
			{
				s.Render(window);
			}
		}

		//Snake Breathing 
		for (Snake& s : snakes)
		{
			s.LoseBreath(); //Each Snake will lose breath each update
			if (s.GetBreath() <= 0) //If Snake has 0 or less breath
			{
				s.SetNotAlive();
			}
		}

		if (onePlayer) //For One Player Game
		{
			//Set Breath fill colour and size
			breathOne.setFillColor(sf::Color::White);
			breathSize.x = snakes[0].GetBreath();
			breathOne.setSize(breathSize);
			
		}
		else if (twoPlayer || playerAI) //For Two Player Game or AI Game
		{
			//Set Breath fill colour
			breathOne.setFillColor(sf::Color::White);
			breathTwo.setFillColor(sf::Color::White);

			//Set Breath Size
			breathSize.x = snakes[0].GetBreath();
			breathOne.setSize(breathSize);
			breathSize.x = snakes[1].GetBreath();
			breathTwo.setSize(breathSize);
		}

		if (onePlayer) //For One Player Game
		{
			if (snakes[0].GetAlive()) //Will only draw remaining Breath if Snake is alive
			{
				window.draw(breathOne);
			}
		}
		else if (twoPlayer || playerAI)//For Two Player Game or AI Game
		{
			if (snakes[0].GetAlive()) //Will only draw remaining Breath if Snake is alive
			{
				window.draw(breathOne);
			}
			if (snakes[1].GetAlive()) //Will only draw remaining Breath if Snake is alive
			{
				window.draw(breathTwo);
			}
		}
		
		//Render Collectables
		for (z = 0; z < 5; z++) 
		{
			if (rand() % 50 == 0) //Each Collectable has a chance of becoming 'Active'
			{
				collectables[z].SetActive();
			}
				
			collectables[z].Render(window); //Collectables will only be rendered if they are active
		}

		//Find closest collectable for AI snake
		if (playerAI)
		{
			
			for (z = 0; z < 5; z++) //For Each Collectable
			{

				//Work out the distance of Collectable to AI Snake
				totalDistance = (collectables[z].GetPosition().x + collectables[z].GetPosition().y) - (snakes[1].GetPosition().x + snakes[1].GetPosition().y);
				if (totalDistance < 0)
				{
					totalDistance = totalDistance * -1;
				}

				//Work out closest Collectable
				if (minDistance > totalDistance && collectables[z].GetActive())
				{
					minDistance = totalDistance;
					closestCollect = collectables[z];
				}
			}
			
		}

		if (closestCollect.GetActive()) //If closest Collectable is active
		{
			hasTarget = true;
			targetPos = closestCollect.GetPosition(); //Set AI Snake target position
		}

		//Check Win/Lose
		if (onePlayer) //If One Player Game
		{
			score1 = to_string(snakes[0].GetSnakeSize() - 1);
			text.setPosition(320, 10);
			text.setCharacterSize(10);
			text.setString("Player One Score: " + score1);
			window.draw(text);

			if (!snakes[0].GetAlive()) //If Died
			{

				//Set Score Display positons and values
				window.clear();
				text.setPosition(20, 20);
				text.setCharacterSize(40);
				text.setString("Player One Score: " + score1);
				window.draw(text);
				window.display();

				ifstream scoreFile;
				scoreFile.open("HighScore.txt");
				scoreFile >> highScore; //Get High Score from file

				if (snakes[0].GetSnakeSize() - 1 > highScore) //Update High Score if needed
				{

					ofstream scoreFile("HighScore.txt", ofstream::trunc);
					scoreFile << snakes[0].GetSnakeSize() - 1;
					scoreFile.close();

				}

				clock.restart();
				while (clock.getElapsedTime().asMilliseconds() < 10000);
				window.close();

				snakes[0].ResetSnake();
				Run(); //Re Load Game
				
			}

		}
		else if (twoPlayer || playerAI) //If Two Player Game/Player VS CPU
		{

			//Set Score Display positons and values
			score1 = to_string(snakes[0].GetSnakeSize() - 1);
			score2 = to_string(snakes[1].GetSnakeSize() - 1);

			score1 = to_string(snakes[0].GetSnakeSize() - 1);
			text.setPosition(320, 10);
			text.setCharacterSize(10);
			text.setString("Player One Score: " + score1);

			score2 = to_string(snakes[1].GetSnakeSize() - 1);
			textTwo.setPosition(320, 30);
			textTwo.setCharacterSize(10);

			if (twoPlayer) //For Two Player Game
			{
				textTwo.setString("Player Two Score: " + score2);
			}
			else if (playerAI) //For AI Game
			{
				textTwo.setString("CPU Score: " + score2);
			}

			window.draw(text);
			window.draw(textTwo);

			if (snakes[0].GetAlive() && !snakes[1].GetAlive())
			{
				//Player Two Died First
				playerOneDied = false;
				playerTwoDied = true;
			}
			if (!snakes[0].GetAlive() && snakes[1].GetAlive())
			{
				//Player One Died First
				playerOneDied = true;
				playerTwoDied = false;
			}

			if (!snakes[0].GetAlive() && !snakes[1].GetAlive()) //If Both Players Died
			{

				//Set Score Display positons and values
				window.clear();
				text.setPosition(20, 20);
				text.setCharacterSize(40);
				text.setString("Player One Score: " + score1);
			
				textTwo.setPosition(20, 80);
				textTwo.setCharacterSize(40);
				if (twoPlayer) //If Two Player Game
				{
					textTwo.setString("Player Two Score: " + score2);
				}
				else if (playerAI) //If AI Game
				{
					textTwo.setString("CPU Score: " + score2);
				}

				//Work out the winning score
				if (snakes[0].GetSnakeSize() - 1 > snakes[1].GetSnakeSize() - 1)
				{
					winScore = snakes[0].GetSnakeSize() - 1;
					winText.setString("Player One Wins!");
				}
				else if (snakes[1].GetSnakeSize() - 1 > snakes[0].GetSnakeSize() - 1)
				{
					winScore = snakes[1].GetSnakeSize() - 1;
					if (twoPlayer) //If Two Player Game
					{
						winText.setString("Player Two Wins!");
					}
					else if (playerAI) //If AI Game
					{
						winText.setString("CPU Wins!");
					}
					
				}
				else if (snakes[0].GetSnakeSize() - 1 == snakes[1].GetSnakeSize() - 1) //If both players have same score
				{
					winScore = snakes[0].GetSnakeSize() - 1;
					if (playerOneDied) //If Player One died first
					{
						if (twoPlayer)  //If Two Player Game
						{
							winText.setString("Player Two Wins!");
						}
						else if (playerAI) //If AI Game
						{
							winText.setString("CPU Wins!");
						}
					}
					else if (playerTwoDied) //If Player Two/AI died first
					{
						winText.setString("Player One Wins!");
					}

				}

				winText.setFont(font);
				winText.setFillColor(sf::Color::White);
				winText.setStyle(sf::Text::Bold);
				winText.setPosition(20, 300);
				winText.setCharacterSize(40);

				ifstream scoreFile;
				scoreFile.open("HighScore.txt");
				scoreFile >> highScore; //Get High Score from file

				if (winScore > highScore) //Update High Score if needed
				{

					ofstream scoreFile("HighScore.txt", ofstream::trunc);
					scoreFile << snakes[0].GetSnakeSize() - 1;
					scoreFile.close();

				}

				window.draw(text);
				window.draw(textTwo);
				window.draw(winText);
				window.display();

				clock.restart();
				while (clock.getElapsedTime().asMilliseconds() < 10000);
				window.close();

				for (Snake s : snakes)
				{
					s.ResetSnake();
				}
				Run(); //Re Load Game

			}

		}

		window.display();

		//Loop until time passed
		while (clock.getElapsedTime().asMilliseconds() < 100);
		clock.restart();		
	}

}

void Game::Collisions() //Test different Collisions for Snake
{
	for (Snake& s : snakes)
	{

		//Collectable Collsiions
		for (z = 0; z < 5; z++) //For Each Collectable in array
		{
			if (s.GetPosition() == collectables[z].GetPosition()) //If Snake 'Head' position equals Collectable position
			{
				s.Grow(collectables[z].GetGrowAmount()); //Grow Snake

				collectables[z].SetNotActive(); //Stop displaying Collectable 
				collectables[z].Spawn(); //Spawn new Collectable 

				if (collectables[z].GetPosition() == closestCollect.GetPosition()) //If Collectable eaten is AI Snakes target
				{
					hasTarget = false;
				}
				
			}
		}

		//Wall Collisions
		if (s.GetPosition().x < 0 || s.GetPosition().x > 590) //If Snake hits side walls
		{
			s.SetNotAlive(); //Kill Snake
		}
		else if (s.GetPosition().y > 790) //If Snake hits floor
		{
			s.SetNotAlive(); //Kill Snake
		}

		//Water Collisions
		if (s.GetPosition().y < waterLevel.GetPosition().y) //If Snake goes above water level
		{
			s.ResetBreath(); //Snake Breath reset
			s.Sink(); //Sink Snake
		}

	}

}

Game::~Game()
{
}

	

