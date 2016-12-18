#include "Ball.h"
#include "Constants.h"

const float Ball::SPEED = 445.f;

Ball::Ball(sf::Vector2f position, float size_set) 
{
	direction = sf::Vector2f(randomDirection(), 0.f);
	size = size_set;
	setPosition(position);
}

void Ball::update(const float DT)
{
	// Horizontal Collision
	if (getPosition().y <= 0.f)
		direction.y = -direction.y;
	if (getPosition().y >= WINDOW_HEIGHT - size)
		direction.y = -direction.y;

	move(direction * SPEED * DT);
}

void Ball::hit(const Paddle &paddle)
{
	direction.x = -direction.x;

	if (paddle.getVelocity() > 0)
		direction.y = 1.f;
	if (paddle.getVelocity() < 0)
		direction.y = -1.f;
	
}

void Ball::reset()
{
	setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	direction = sf::Vector2f(randomDirection(), 0.f);
}

void Ball::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	sf::RectangleShape ball(sf::Vector2f(size, size));

	ball.setPosition(getPosition());

	target.draw(ball);
}

float Ball::randomDirection() const
{
	int choices = rand() % 2;
	// Left
	if (choices == 0)
		return -1.f;
	// Right
	return 1.f;
}