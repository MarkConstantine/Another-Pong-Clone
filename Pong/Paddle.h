#pragma once

#include <SFML/Graphics.hpp>

class Paddle : public sf::Drawable, public sf::Transformable
{
	static const float SPEED;
	static const sf::Vector2f SIZE;
public:
	Paddle(sf::Vector2f position);
	void moveUp(const float DT);
	void moveDown(const float DT);
	void reset(sf::Vector2f position);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	sf::Vector2f getSize() const { return SIZE; }
	float getVelocity() const { return velocity; }
	void setVelocity(float value) { velocity = value; }
private:
	float velocity;
};