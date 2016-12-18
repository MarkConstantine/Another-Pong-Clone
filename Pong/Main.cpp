#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "Constants.h"
#include "Paddle.h"
#include "Ball.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Another Pong Clone");
	window.setFramerateLimit(60);
	
	Paddle leftPaddle(sf::Vector2f(WINDOW_WIDTH - (WINDOW_WIDTH - 25), (WINDOW_HEIGHT / 2) - 30)); // Player Paddle
	Paddle rightPaddle(sf::Vector2f(WINDOW_WIDTH - 30, (WINDOW_HEIGHT / 2) - 30)); // AI Paddle
	Ball ball(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), 10);
	
	sf::Clock clock;
	
	// Sound to be played when ball hits paddle
	sf::SoundBuffer boopBuffer;
	boopBuffer.loadFromFile("boop.wav");
	sf::Sound boop;
	boop.setBuffer(boopBuffer);
	boop.setVolume(10.f);

	// Sound to be played when ball goes offscreen to the left
	sf::SoundBuffer loseBuffer;
	loseBuffer.loadFromFile("lose.wav");
	sf::Sound lose;
	lose.setBuffer(loseBuffer);
	lose.setVolume(50.f);

	// Sound to be played when ball goes offscreen to the right
	sf::SoundBuffer winBuffer;
	winBuffer.loadFromFile("win.wav");
	sf::Sound win;
	win.setBuffer(winBuffer);
	win.setVolume(50.f);

	sf::Font font;
	if (!font.loadFromFile("rusq.ttf"))
	{
		// error...
	}

	// Score for the left paddle
	unsigned int leftScore = 0;
	sf::Text leftScoreText(std::to_string(leftScore), font, 30);
	leftScoreText.setPosition(sf::Vector2f(WINDOW_WIDTH / 4, 15));
	
	// Score for the right paddle
	unsigned int rightScore = 0;
	sf::Text rightScoreText(std::to_string(rightScore), font, 30);
	rightScoreText.setPosition(sf::Vector2f(WINDOW_WIDTH * 3 / 4, 15));

	sf::Text introText("Press the Spacebar to Start!", font, 30);
	introText.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - 200, WINDOW_HEIGHT / 3));
	
	bool isPlaying = false;

	while (window.isOpen()) 
	{
		float dt = clock.restart().asSeconds();

		// Event Handling
		sf::Event event;
		while (window.pollEvent(event)) 
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Start Game
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			isPlaying = true;
		
		// Game Start
		if (isPlaying)
		{
			// Left Paddle User Input
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
				leftPaddle.moveUp(dt);
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				leftPaddle.moveDown(dt);

			// AI Movements
			if (ball.getDirection().x > 0.f)
			{
				if (ball.getPosition().y + (ball.getSize() / 2.f) >= rightPaddle.getPosition().y + (rightPaddle.getSize().y / 2.f))
					rightPaddle.moveDown(dt);
				if (ball.getPosition().y + (ball.getSize() / 2.f) <= rightPaddle.getPosition().y + (rightPaddle.getSize().y / 2.f))
					rightPaddle.moveUp(dt);
			}

			// Left Paddle Collision
			if ((ball.getPosition().x <= leftPaddle.getPosition().x + leftPaddle.getSize().x) &&
				(ball.getPosition().y <= leftPaddle.getPosition().y + leftPaddle.getSize().y) &&
				(ball.getPosition().y + ball.getSize() >= leftPaddle.getPosition().y))
			{	
				ball.hit(leftPaddle);
				boop.play();
			}

			// Right Paddle Collision
			if ((ball.getPosition().x + ball.getSize() >= rightPaddle.getPosition().x) &&
				(ball.getPosition().y <= rightPaddle.getPosition().y + rightPaddle.getSize().y) &&
				(ball.getPosition().y + ball.getSize() >= rightPaddle.getPosition().y))
			{	
				ball.hit(rightPaddle);
				boop.play();
			}

			// Moves ball
			ball.update(dt);
		
			// Right Side Wins (Ball goes offscreen left)
			if (ball.getPosition().x < 0.f)
			{
				rightScore++;
				lose.play();
				leftPaddle.reset(sf::Vector2f(WINDOW_WIDTH - (WINDOW_WIDTH - 25), (WINDOW_HEIGHT / 2) - 30));
				rightPaddle.reset(sf::Vector2f(WINDOW_WIDTH - 30, (WINDOW_HEIGHT / 2) - 30));
				ball.reset();
				isPlaying = false;
			}

			// Left Side Wins (Ball goes offscreen right)
			if (ball.getPosition().x + ball.getSize() > WINDOW_WIDTH)
			{
				leftScore++;
				win.play();
				leftPaddle.reset(sf::Vector2f(WINDOW_WIDTH - (WINDOW_WIDTH - 25), (WINDOW_HEIGHT / 2) - 30));
				rightPaddle.reset(sf::Vector2f(WINDOW_WIDTH - 30, (WINDOW_HEIGHT / 2) - 30));
				ball.reset();
				isPlaying = false;
			}

			// Updates score text
			leftScoreText.setString(std::to_string(leftScore));
			rightScoreText.setString(std::to_string(rightScore));
			
			leftPaddle.setVelocity(0.f);
			rightPaddle.setVelocity(0.f);
		}

		window.clear();
		if (!isPlaying)
			window.draw(introText);
		window.draw(leftScoreText);
		window.draw(rightScoreText);
		window.draw(leftPaddle);
		window.draw(rightPaddle);
		window.draw(ball);
		window.display();
	}
	
	return EXIT_SUCCESS;
}