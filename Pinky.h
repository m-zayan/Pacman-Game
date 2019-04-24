#pragma once

#include<SFML/Graphics.hpp>
#include"Animation.h"
#include<sstream>
#ifndef Pinky_H

#define Pinky_H

class Pinky
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
	Pinky(const sf::Vector2f& position)
	{
		s_Pinky.setTextureRect({ 0,32,32,32 });
		s_Pinky.setPosition(position);
		animations[int(AnimationIndex::downStanding)] = Animation(64, 32, 32, 32, 1, 10.4f, path);
		animations[int(AnimationIndex::upDirection)] = Animation(0, 32, 32, 32, 2, 0.4f, path);
		animations[int(AnimationIndex::downDirection)] = Animation(64, 32, 32, 32, 2, 0.4f, path);
		animations[int(AnimationIndex::leftDirection)] = Animation(96, 32, 32, 32, 2, 0.4f, path);
		animations[int(AnimationIndex::rightDirection)] = Animation(128, 32, 32, 32, 2, 0.4f, path);

	}
	void Draw(sf::RenderWindow& window) const
	{
		window.draw(s_Pinky);


	}
	void Update(float deltaTime)
	{

		animations[int(currentAnimation)].Update(deltaTime);
		animations[int(currentAnimation)].ApplyToSprite(s_Pinky);
	}
private:
	sf::Sprite s_Pinky;
	Animation animations[int(AnimationIndex::Count)];
	AnimationIndex currentAnimation = AnimationIndex::downStanding;
	std::string path = "Resources/Graphics/Ghost.png";
};



#endif