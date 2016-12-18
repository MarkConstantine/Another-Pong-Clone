#include "Paddle.h"
#include "Constants.h"

const float Paddle::SPEED = 400.f;
const sf::Vector2f Paddle::SIZE = sf::Vector2f(5.f, 60.f);

Paddle::Paddle(sf::Vector2f position)
{
	setPosition(position);
	velocity = 0.f;
}

void Paddle::moveUp(const float DT)
{
	velocity = -SPEED * DT;
	if (getPosition().y >= 0.f)
		move(sf::Vector2f(0, velocity));
}

void Paddle::moveDown(const float DT)
{
	velocity = SPEED * DT;
	if (getPosition().y <= WINDOW_HEIGHT - SIZE.y)
		move(sf::Vector2f(0, velocity));
}

void Paddle::reset(sf::Vector2f position)
{
	setPosition(position);
}

void Paddle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RectangleShape paddle(sf::Vector2f(SIZE.x, SIZE.y));
	
	paddle.setPosition(getPosition());
	
	target.draw(paddle);
}