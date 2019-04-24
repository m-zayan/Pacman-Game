#pragma once

#include<SFML/Graphics.hpp>
#include"Animation.h"
#include<sstream>
#ifndef Inky_H

#define Inky_H

class Inky
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
	Inky(const sf::Vector2f& position)
	{
		s_Inky.setTextureRect({ 0,64,32,32 });
		s_Inky.setPosition(position);
		animations[int(AnimationIndex::downStanding)] = Animation(64, 64, 32, 32, 1, 10.4f, path);
		animations[int(AnimationIndex::upDirection)] = Animation(0, 64, 32, 32, 2, 0.4f, path);
		animations[int(AnimationIndex::downDirection)] = Animation(64, 64, 32, 32, 2, 0.4f, path);
		animations[int(AnimationIndex::leftDirection)] = Animation(96, 64, 32, 32, 2, 0.4f, path);
		animations[int(AnimationIndex::rightDirection)] = Animation(128, 64, 32, 32, 2, 0.4f, path);

	}
	void Draw(sf::RenderWindow& window) const
	{
		window.draw(s_Inky);


	}
	void Update(float deltaTime)
	{

		animations[int(currentAnimation)].Update(deltaTime);
		animations[int(currentAnimation)].ApplyToSprite(s_Inky);
	}
private:
	sf::Sprite s_Inky;
	Animation animations[int(AnimationIndex::Count)];
	AnimationIndex currentAnimation = AnimationIndex::downStanding;
	std::string path = "Resources/Graphics/Ghost.png";
};



#endif