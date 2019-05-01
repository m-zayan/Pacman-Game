#pragma once

#include<SFML/Graphics.hpp>
#include"Animation.h"
#include<sstream>
#ifndef Pinky_H

#define Pinky_H

class Pinky :public Blinky
{
public:
	sf::Sprite s_Pinky;

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
		animations[int(AnimationIndex::leftDirection)] = Animation(128, 32, 32, 32, 2, 0.4f, path);
		animations[int(AnimationIndex::rightDirection)] = Animation(192, 32, 32, 32, 2, 0.4f, path);
		x = 390;
		y = 420;
		movespeed = 2;
	}
	void Draw(sf::RenderWindow& window) const
	{
		window.draw(s_Pinky);


	}
	void Update(float deltaTime, sf::Vector2f Pacman, sf::Sprite& Pinky)
	{
		prevP = Gpos;
		animations[int(currentAnimation)].Update(deltaTime);
		animations[int(currentAnimation)].ApplyToSprite(s_Pinky);
		Gpos = FindPath(Pacman, Pinky);
		if (Gpos.x > 0)
		{
			currentAnimation = AnimationIndex::rightDirection;
		}
		else if (Gpos.x < 0)
		{
			currentAnimation = AnimationIndex::leftDirection;
		}
		else if (Gpos.y < 0)
		{
			currentAnimation = AnimationIndex::upDirection;
		}
		else if (Gpos.y > 0)
		{
			currentAnimation = AnimationIndex::downDirection;
		}
		int Grow = int(y / 30);
		int Gcol = int(x / 30);
		//These conditions prevent ghosts Backtracking.
		if (Gpos.x == 0 && prevP.y != 0 && node.wall[Grow - 1][Gcol] != 1 && node.wall[Grow + 1][Gcol] != 1 && Gpos.y == (prevP.y*-1))
		{
			Gpos.y *= -1;
			if (currentAnimation == AnimationIndex::upDirection)
			{
				currentAnimation = AnimationIndex::downDirection;
			}
			else
			{
				currentAnimation = AnimationIndex::upDirection;
			}

		}
		if (Gpos.y == 0 && prevP.x != 0 && node.wall[Grow][Gcol - 1] != 1 && node.wall[Grow][Gcol + 1] != 1 && Gpos.x == (prevP.x*-1))
		{
			Gpos.x *= -1;
			if (currentAnimation == AnimationIndex::rightDirection)
			{
				currentAnimation = AnimationIndex::leftDirection;
			}
			else
			{
				currentAnimation = AnimationIndex::rightDirection;
			}
		}
		dirmove(Gpos);
		moving();
		Pinky.setPosition(x, y);
	}
	void Update3(float deltaTime)
	{
		s_Pinky.setPosition(375, 420);
		currentAnimation = AnimationIndex::upDirection;
		animations[int(currentAnimation)].Update(deltaTime);
		animations[int(currentAnimation)].ApplyToSprite(s_Pinky);

	}
private:
	
	Animation animations[int(AnimationIndex::Count)];
	AnimationIndex currentAnimation = AnimationIndex::downStanding;
	std::string path = "Resources/Graphics/Ghost.png";
	sf::Vector2f Gpos;
	sf::Vector2f prevP = {};
	Map node;
};



#endif