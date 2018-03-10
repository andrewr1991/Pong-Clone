/*
* Simple Pong clone
* Athuor: Andrew Ridout
*/

#include "stdafx.h"
#include "SFML/Graphics.hpp"

using namespace sf;

int main()
{
	Vector2f windowDimensions;
	windowDimensions.x = 900;
	windowDimensions.y = 650;

	VideoMode vm(windowDimensions.x, windowDimensions.y);

	RenderWindow window(vm, "Pong");

	const float paddleMovement = 200;

	Vector2f playerDimensions;
	playerDimensions.x = 5;
	playerDimensions.y = 100;

	RectangleShape player(playerDimensions);
	const int playerXPosition = 15;
	float playerYPosition = windowDimensions.y / 2 - (player.getSize().y / 2);

	Vector2f computerDimensions;
	computerDimensions.x = 5;
	computerDimensions.y = 100;

	RectangleShape computer(computerDimensions);
	const int computerXPosition = windowDimensions.x - (playerXPosition + computerDimensions.x);
	float computerYPosition = windowDimensions.y / 2 - (computerDimensions.y / 2);

	const int ballRadius = 8;
	const int ballPoints = 30;
	const float ballMovement = 500;
	CircleShape ball(ballRadius, ballPoints);
	ball.setOrigin(ballRadius, ballRadius);
	float ballXPosition = windowDimensions.x / 2;
	float ballYPosition = windowDimensions.y / 2;

	enum class BallXDirection { LEFT, RIGHT };
	enum class BallYDirection { UP, DOWN };
	BallXDirection ballXDirection = BallXDirection::LEFT;
	BallYDirection ballYDirection = BallYDirection::UP;

	Clock clock;

	while (window.isOpen())
	{
		Time dt = clock.restart();

		/*
		************
		Handle input
		************
		*/
		if (Keyboard::isKeyPressed(Keyboard::Up) && player.getPosition().y >= 0)
		{
			playerYPosition -= (paddleMovement * dt.asSeconds());
		}

		if ((Keyboard::isKeyPressed(Keyboard::Down)) && (player.getPosition().y <= (windowDimensions.y - playerDimensions.y)))
		{
			playerYPosition += (paddleMovement * dt.asSeconds());
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		/*
		****************
		UPDATE THE FRAME
		****************
		*/

		player.setPosition(playerXPosition, playerYPosition);
		computer.setPosition(computerXPosition, computerYPosition);
		ball.setPosition(ballXPosition, ballYPosition);

		if (ballXDirection == BallXDirection::LEFT)
		{
			ballXPosition -= (ballMovement * dt.asSeconds());
		}

		if (ballXDirection == BallXDirection::RIGHT)
		{
			ballXPosition += (ballMovement * dt.asSeconds());
		}

		if (ballYDirection == BallYDirection::DOWN)
		{
			ballYPosition += (ballMovement * dt.asSeconds());
		}

		if (ballYDirection == BallYDirection::UP)
		{
			ballYPosition -= (ballMovement * dt.asSeconds());
		}

		// Hitting player paddle
		if (ball.getPosition().y >= player.getPosition().y && 
			ball.getPosition().y <= (player.getPosition().y + playerDimensions.y) &&
			(ball.getPosition().x - ballRadius) <= (player.getPosition().x + playerDimensions.x) &&
			ballYDirection == BallYDirection::DOWN)
		{
			ballXDirection = BallXDirection::RIGHT;
		}

		if (ball.getPosition().y >= player.getPosition().y &&
			ball.getPosition().y <= (player.getPosition().y + playerDimensions.y) &&
			(ball.getPosition().x - ballRadius) <= (player.getPosition().x + playerDimensions.x) &&
			ballYDirection == BallYDirection::UP)
		{
			ballXDirection = BallXDirection::RIGHT;
		}

		// Hitting computer paddle
		if (ball.getPosition().y >= computer.getPosition().y && 
			ball.getPosition().y <= (computer.getPosition().y + computerDimensions.y) &&
			(ball.getPosition().x + ballRadius) >= computer.getPosition().x &&
			ballYDirection == BallYDirection::DOWN)
		{
			ballXDirection = BallXDirection::LEFT;
		}

		if (ball.getPosition().y >= computer.getPosition().y &&
			ball.getPosition().y <= (computer.getPosition().y + computerDimensions.y) &&
			(ball.getPosition().x + ballRadius) >= computer.getPosition().x &&
			ballYDirection == BallYDirection::UP)
		{
			ballXDirection = BallXDirection::LEFT;
		}

		// Hitting top of screen
		if ((ball.getPosition().y - ballRadius) <= 0)
		{
			ballYDirection = BallYDirection::DOWN;
		}

		if ((ball.getPosition().y - ballRadius) <= 0)
		{
			ballYDirection = BallYDirection::DOWN;
		}

		// Hitting bottom of screen
		if ((ball.getPosition().y + ballRadius) >= windowDimensions.y)
		{
			ballYDirection = BallYDirection::UP;
		}

		if ((ball.getPosition().y + ballRadius) >= windowDimensions.y)
		{
			ballYDirection = BallYDirection::UP;
		}

		// player AI
		if ((ball.getPosition().y - (computer.getPosition().y + (computerDimensions.y / 2)) < 0) && computer.getPosition().y >= 0)
		{
			computerYPosition -= (paddleMovement * dt.asSeconds());
		}

		if ((ball.getPosition().y - (computer.getPosition().y + (computerDimensions.y / 2)) > 0) && (computer.getPosition().y <= (windowDimensions.y - computerDimensions.y)))
		{
			computerYPosition += (paddleMovement * dt.asSeconds());
		}

		/*
		**************
		Draw the scene
		**************
		*/

		window.clear();
		window.draw(player);
		window.draw(computer);
		window.draw(ball);
		window.display();
	}

    return 0;
}

