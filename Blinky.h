#pragma once

#include<SFML/Graphics.hpp>
#include"Animation.h"
#include<sstream>
#ifndef Blinky_H

#define Blinky_H

class Blinky
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
	Blinky(const sf::Vector2f& position)
	{
		s_Blinky.setTextureRect({ 0,0,32,32 });
		s_Blinky.setPosition(position);
		animations[int(AnimationIndex::downStanding)] = Animation(64, 0, 32, 32, 1, 10.4f,path);
		animations[int(AnimationIndex::upDirection)] = Animation(0, 0, 32, 32, 2, 0.4f, path);
		animations[int(AnimationIndex::downDirection)] = Animation(64, 0, 32, 32, 2, 0.4f, path);
		animations[int(AnimationIndex::leftDirection)] = Animation(96, 0, 32, 32, 2, 0.4f, path);
		animations[int(AnimationIndex::rightDirection)] = Animation(128, 0, 32, 32, 2, 0.4f, path);
		
	}
	void Draw(sf::RenderWindow& window) const
	{
		window.draw(s_Blinky);


	}
	void Update(float deltaTime)
	{

		animations[int(currentAnimation)].Update(deltaTime);
		animations[int(currentAnimation)].ApplyToSprite(s_Blinky);
	}
private:
	sf::Sprite s_Blinky;
	Animation animations[int(AnimationIndex::Count)];
	AnimationIndex currentAnimation = AnimationIndex::downStanding;
	std::string path = "Resources/Graphics/Ghost.png";
};



#endif