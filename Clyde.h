#pragma once

#include<SFML/Graphics.hpp>
#include"Animation.h"
#include<sstream>
#ifndef Clyde_H

#define Clyde_H

class Clyde
{
public:

	enum class AnimationIndex
	{
		downStanding,
		upDirection,
		downDirection,
		rightDirection,
		leftDirection,
		Count
	};
	Clyde(const sf::Vector2f& position)
	{
		s_Clyde.setTextureRect({ 0,96,32,32 });
		s_Clyde.setPosition(position);
		animations[int(AnimationIndex::downStanding)] = Animation(64, 96, 32, 32, 1, 10.4f, path);
		animations[int(AnimationIndex::upDirection)] = Animation(0, 96, 32, 32, 2, 0.4f, path);
		animations[int(AnimationIndex::downDirection)] = Animation(64, 96, 32, 32, 2, 0.4f, path);
		animations[int(AnimationIndex::leftDirection)] = Animation(96, 96, 32, 32, 2, 0.4f, path);
		animations[int(AnimationIndex::rightDirection)] = Animation(128, 96, 32, 32, 2, 0.4f, path);

	}
	void Draw(sf::RenderWindow& window) const
	{
		window.draw(s_Clyde);


	}
	void Update(float deltaTime)
	{

		animations[int(currentAnimation)].Update(deltaTime);
		animations[int(currentAnimation)].ApplyToSprite(s_Clyde);
	}
private:
	sf::Sprite s_Clyde;
	Animation animations[int(AnimationIndex::Count)];
	AnimationIndex currentAnimation = AnimationIndex::downStanding;
	std::string path = "Resources/Graphics/Ghost.png";
};



#endif