#include "Snake.h"

void Snake::Render(sf::RenderWindow & window)
{
	if (isAlive) //Only Render Snake if it is Alive
	{
		for (sf::Vector2f position : snakeSegments) //Render each Segment of Snake
		{
			shape.setPosition(position);
			window.draw(shape);
		}
	}
}

Snake::Snake() :
	size(10, 10),
	shape(size)
{
	shape.setFillColor(sf::Color::White);
}

//Each Snake has a Position and Breath, 'IsAlive' is used to check if Snake should be rendered or not and 'BreathYPos' is used to set the Breath display position
Snake::Snake(sf::Vector2f position_, bool IsAlive, int SnakeBreath, int BreathYPos):
	position(position_),
	size(10, 10),
	shape(size)
{
	shape.setFillColor(sf::Color::White);
	shape.setPosition(position);

}

Snake::~Snake()
{
}

void Snake::ResetSnake() //Reset all Snake Values when Game ends
{

	snakeSize = 1;
	snakeSegments.clear();
	direction = EDirection::eNoDirection;

}

void Snake::ResetBreath() //Used when Snake hits top of water level
{
	snakeBreath = 300; //Snake start Breath is 300;
}

void Snake::SetBreathPos(sf::Vector2f Pos)
{
	breathPos = Pos;
}

void Snake::LoseBreath()
{
	snakeBreath -= 2; //Will Lose 2 Breath on every update
}

void Snake::Grow(int collectGrowAmount)
{

	growAmount = collectGrowAmount; //Snake will 'Grow' depending on Collectable growAmount
	//Snake will gain a segment for each 1 'growAmount'

}

void Snake::Spawn() //Will Spawn Snake at a random position at the start of the Game
{
	x = (rand() % 59) *10.0f; //Snake x and y values can only be in multiples of 10 so Snake will be on same 'grid' as Collectables
	y = ((rand() % 64) *10.0f) + 150;
	shape.setPosition({ x, y });

	position = { x, y };
	snakeSegments.push_front(position); //Put first position in SnakeSegments list
}

void Snake::SnakeOneDirection() //Movemt Keys for Player One
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		direction = EDirection::eNorth;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		direction = EDirection::eEast;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		direction = EDirection::eSouth;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		direction = EDirection::eWest;
	}
	
}

void Snake::SnakeTwoDirection() //Movemt Keys for Player Two
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		direction = EDirection::eNorth;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		direction = EDirection::eEast;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		direction = EDirection::eSouth;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		direction = EDirection::eWest;
	}

}

void Snake::SnakeAIMovement(sf::Vector2f CollectPos) //Movement for AI Snake
{
	if (CollectPos.x == 0 && CollectPos.y == 0)
	{
		desiredDirection = EDirection::eNoDirection;
	}

	if (snakeSegments.front().x < CollectPos.x) //If Snake is to Left of Collectable move Right/East
	{
		desiredDirection = EDirection::eEast;
	}
	else if (snakeSegments.front().x > CollectPos.x) //If Snake is to Right of Collectable move Left/West
	{
		desiredDirection = EDirection::eWest;
	}
	else if (snakeSegments.front().x == CollectPos.x) //If Snake is Above/Below Collectable
	{

		if (snakeSegments.front().y < CollectPos.y) //If Snake is Above Collectable move Down/South
		{
			desiredDirection = EDirection::eSouth;
		}
		else if (snakeSegments.front().y > CollectPos.y) //If Snake is Below Collectable move Up/North
		{
			desiredDirection = EDirection::eNorth;
		}
		else if (snakeSegments.front().y == CollectPos.y)
		{
			//Collectable Found
		}

	}

	direction = desiredDirection;

}

void Snake::Update() //Updates all positions of Snakes depending on their direction
{

	switch (direction)
	{
	case EDirection::eNorth:
		position.y -= 10;
		break;
	case EDirection::eEast:
		position.x += 10;
		break;
	case EDirection::eSouth:
		position.y += 10;
		break;
	case EDirection::eWest:
		position.x -= 10;
		break;
	case EDirection::eNoDirection:
		position.x = position.x;
		position.y = position.y;
		break;
	}

	shape.setPosition(position);
	snakeSegments.push_front(position); //Put new position at front of list

	if (growAmount > 0) //If Snake needs to grow, don't 'pop_back' last Segment
	{
		growAmount--;
	}
	else //If Snake doesnt need to grow, get rid of last Segment on update, Snake will then stay the same size whilst moving
	{
		snakeSegments.pop_back();
	}

	snakeSize = snakeSegments.size();

}

void Snake::Sink() //If Snake hits top of water level
{
	if (direction == EDirection::eNorth)
	{
		if (position.x < 300) //If Snake is in left half of window
		{
			direction = EDirection::eEast;
		}
		else if (position.x >= 300) //If Snake is in right half of window
		{
			direction = EDirection::eWest;
		}
	}

	else if (direction == EDirection::eEast || direction == EDirection::eWest)
	{

		position.y += 10; //Move Snake 10 down

	}
}

bool Snake::CheckOtherSnakeCollision(const Snake& other) const //Collisions with other Snakes
{

	for (auto& otherSegment : other.snakeSegments) //Loop through other Snakes Segments
	{
		if (snakeSegments.front() == otherSegment) //Compare Segments positions to first Snakes 'Head' position
		{
			return true;
		}

	}

}

bool Snake::CheckSelfCollision() //Collisions with own tail
{

	for (auto& segment : snakeSegments) //Loops through all Segments of Snake
	{
		sf::Vector2f* a = &segment; //Pointers used so can loop through all Segments without comparing 'Head' to 'Head'
		sf::Vector2f* b = &snakeSegments.front();

		if (a != b) //Dont Compare Head position to Head position
		{
			if (snakeSegments.front() == segment) //If 'Head' position equals Segment position
			{
				return true;
			}
		}
		
	}

}

//The rest of the functions return and alter values

sf::Vector2f Snake::GetBreathPos()
{
	return breathPos;
}

int Snake::GetBreath()
{
	return snakeBreath;
}

sf::Vector2f Snake::GetPosition()
{
	return position;
}

void Snake::SetAlive()
{
	isAlive = true;
}

void Snake::SetNotAlive()
{
	isAlive = false;
}

bool Snake::GetAlive()
{
	return isAlive;
}

int Snake::GetSnakeSize()
{
	return snakeSize;
}
