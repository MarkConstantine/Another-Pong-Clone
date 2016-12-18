#pragma once

#include <SFML/Graphics.hpp>
#include "Paddle.h"

class Ball : public sf::Drawable, public sf::Transformable
{
	static const float SPEED;
public:
	Ball(sf::Vector2f position, float size_set);
	void update(const float DT);
	void hit(const Paddle &paddle);
	void reset();
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	sf::Vector2f getDirection() const { return direction; }
	float getSize() const { return size; } 
private:
	float randomDirection() const;
private:
	sf::Vector2f direction;
	float size;
};