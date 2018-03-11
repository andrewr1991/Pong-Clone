/*
* Simple Pong clone
* Athuor: Andrew Ridout
*/

#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include "time.h"
#include "stdlib.h"
#include "sstream"

using namespace sf;
using namespace std;

int main()
{
	// Window variables
	Vector2f windowDimensions;
	windowDimensions.x = 900;
	windowDimensions.y = 650;

	VideoMode vm(windowDimensions.x, windowDimensions.y);

	RenderWindow window(vm, "Pong");

	const float paddleMovement = 200;

	// Player variables
	Vector2f playerDimensions;
	playerDimensions.x = 5;
	playerDimensions.y = 100;

	RectangleShape player(playerDimensions);
	const int playerXPosition = 15;
	float playerYPosition = windowDimensions.y / 2 - (player.getSize().y / 2);

	// Computer variables
	Vector2f computerDimensions;
	computerDimensions.x = 5;
	computerDimensions.y = 100;

	RectangleShape computer(computerDimensions);
	const int computerXPosition = windowDimensions.x - (playerXPosition + computerDimensions.x);
	float computerYPosition = windowDimensions.y / 2 - (computerDimensions.y / 2);

	// Ball variables
	const int ballRadius = 8;
	const int ballPoints = 30;
	const float ballMovement = 250;
	CircleShape ball(ballRadius, ballPoints);
	ball.setOrigin(ballRadius, ballRadius);
	float ballXPosition = windowDimensions.x / 2;
	float ballYPosition = windowDimensions.y / 2;

	// Ball direction enums
	enum class BallXDirection { LEFT, RIGHT };
	BallXDirection ballXDirection;
	enum class BallYDirection { UP, DOWN };
	BallYDirection ballYDirection;

	// Score objects and variables
	int playerScore = 0;
	int computerScore = 0;

	Font scoreFont;
	if (!scoreFont.loadFromFile("fonts/arial.ttf"))
	{
		printf("Error loading font");
	}

	Text playerScoreText;
	Text computerScoreText;

	playerScoreText.setFont(scoreFont);
	computerScoreText.setFont(scoreFont);

	playerScoreText.setString("Score: 0");
	computerScoreText.setString("Score: 0");

	playerScoreText.setCharacterSize(15);
	computerScoreText.setCharacterSize(15);

	playerScoreText.setFillColor(Color::White);
	computerScoreText.setFillColor(Color::White);

	playerScoreText.setPosition(100, 15);
	computerScoreText.setPosition(800, 15);

	FloatRect playerScoreRect = playerScoreText.getLocalBounds();
	FloatRect computerScoreRect = computerScoreText.getLocalBounds();

	playerScoreText.setOrigin(playerScoreRect.left +
		playerScoreRect.width / 2.0f,
		playerScoreRect.top +
		playerScoreRect.height / 2.0f);

	computerScoreText.setOrigin(computerScoreRect.left +
		computerScoreRect.width / 2.0f,
		computerScoreRect.top +
		computerScoreRect.height / 2.0f);

	// Clock object to take care of the frame rate
	Clock clock;

	// Enum class to keep track of the current game state
	enum class GameState { PLAYING, PAUSED };
	GameState gameState = GameState::PAUSED;

	// Randomize the initial direction of the ball
	srand(time(NULL));
	int randNum = rand() % 2 + 1;

	if (randNum == 1)
	{
		ballXDirection = BallXDirection::LEFT;
	}
	else
	{
		ballXDirection = BallXDirection::RIGHT;
	}

	randNum = rand() % 2 + 1;

	if (randNum == 1)
	{
		ballYDirection = BallYDirection::UP;
	}
	else
	{
		ballYDirection = BallYDirection::DOWN;
	}

	// Initial game positions
	const int initialPlayerXPosition = 15;
	float initialPlayerYPosition = windowDimensions.y / 2 - (player.getSize().y / 2);

	const int initialComputerXPosition = windowDimensions.x - (playerXPosition + computerDimensions.x);
	float initialComputerYPosition = windowDimensions.y / 2 - (computerDimensions.y / 2);

	float initialBallXPosition = windowDimensions.x / 2;
	float initialBallYPosition = windowDimensions.y / 2;

	// Game loop
	while (window.isOpen())
	{
		Time dt = clock.restart();

		/*
		************
		Handle input
		************
		*/

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		if (gameState == GameState::PAUSED)
		{
			playerYPosition = initialPlayerYPosition;
			computerYPosition = initialComputerYPosition;
			ballXPosition = initialBallXPosition;
			ballYPosition = initialBallYPosition;

			player.setPosition(playerXPosition, playerYPosition);
			computer.setPosition(computerXPosition, computerYPosition);
			ball.setPosition(ballXPosition, ballYPosition);
		}

		if (Keyboard::isKeyPressed(Keyboard::Return) && gameState == GameState::PAUSED)
		{
			gameState = GameState::PLAYING;
			printf("testing 1");
		}

		if (gameState == GameState::PLAYING)
		{
			if (Keyboard::isKeyPressed(Keyboard::Up) && player.getPosition().y >= 0)
			{
				playerYPosition -= (paddleMovement * dt.asSeconds());
			}

			if ((Keyboard::isKeyPressed(Keyboard::Down)) && (player.getPosition().y <= (windowDimensions.y - playerDimensions.y)))
			{
				playerYPosition += (paddleMovement * dt.asSeconds());
			}

			/*
			****************
			UPDATE THE FRAME
			****************
			*/

			player.setPosition(playerXPosition, playerYPosition);
			computer.setPosition(computerXPosition, computerYPosition);
			ball.setPosition(ballXPosition, ballYPosition);

			if (gameState == GameState::PLAYING)
			{
				if (ballXDirection == BallXDirection::LEFT)
				{
					ballXPosition -= (ballMovement * dt.asSeconds());
				}

				else if (ballXDirection == BallXDirection::RIGHT)
				{
					ballXPosition += (ballMovement * dt.asSeconds());
				}

				if (ballYDirection == BallYDirection::DOWN)
				{
					ballYPosition += (ballMovement * dt.asSeconds());
				}

				else if (ballYDirection == BallYDirection::UP)
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

				else if (ball.getPosition().y >= player.getPosition().y &&
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

				else if (ball.getPosition().y >= computer.getPosition().y &&
					ball.getPosition().y <= (computer.getPosition().y + computerDimensions.y) &&
					(ball.getPosition().x + ballRadius) >= computer.getPosition().x &&
					ballYDirection == BallYDirection::UP)
				{
					ballXDirection = BallXDirection::LEFT;
				}

				// Hitting top or bottom of screen
				if ((ball.getPosition().y - ballRadius) <= 0)
				{
					ballYDirection = BallYDirection::DOWN;
				}

				else if ((ball.getPosition().y + ballRadius) >= windowDimensions.y)
				{
					ballYDirection = BallYDirection::UP;
				}

				// Player AI
				if ((ball.getPosition().y - (computer.getPosition().y + (computerDimensions.y / 2)) < 0) && computer.getPosition().y >= 0)
				{
					computerYPosition -= (paddleMovement * dt.asSeconds());
				}

				else if ((ball.getPosition().y - (computer.getPosition().y + (computerDimensions.y / 2)) > 0) && (computer.getPosition().y <= (windowDimensions.y - computerDimensions.y)))
				{
					computerYPosition += (paddleMovement * dt.asSeconds());
				}

				// Scoring a point
				if ((ball.getPosition().x - ballRadius) <= playerXPosition)
				{
					computerScore++;
					gameState = GameState::PAUSED;
				}

				else if ((ball.getPosition().x + ballRadius) >= (computerXPosition + computerDimensions.x))
				{
					playerScore++;
					gameState = GameState::PAUSED;
				}
			}
		}

		stringstream playerStream;
		playerStream << "Score = " << playerScore;
		playerScoreText.setString(playerStream.str());

		stringstream computerStream;
		computerStream << "Score = " << computerScore;
		computerScoreText.setString(computerStream.str());

		/*
		**************
		Draw the scene
		**************
		*/

		window.clear();
		window.draw(player);
		window.draw(computer);
		window.draw(ball);
		window.draw(playerScoreText);
		window.draw(computerScoreText);
		window.display();
	}
    return 0;
}

