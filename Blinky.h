#pragma once

#include<SFML/Graphics.hpp>
#include"Animation.h"
#include<sstream>
#include"Map.h"
#ifndef Blinky_H

#define Blinky_H

class Blinky
{
public:
	sf::Sprite s_Blinky;
	enum Dir{UP,DOWN,LEFT,RIGHT};
	bool able[4] = { false,false, false, false };
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
		animations[int(AnimationIndex::leftDirection)] = Animation(128, 0, 32, 32, 2, 0.4f, path);
		animations[int(AnimationIndex::rightDirection)] = Animation(192, 0, 32, 32, 2, 0.4f, path);
		
	}
	void Draw(sf::RenderWindow& window) const
	{
		window.draw(s_Blinky);


	}
	void Update(float deltaTime)
	{

		animations[int(currentAnimation)].Update(deltaTime);
		animations[int(currentAnimation)].ApplyToSprite(s_Blinky);
		int row = (s_Blinky.getPosition().y + 43) / 32;
		int col = (s_Blinky.getPosition().x + 43) / 32;
		if (map.wall[row][col + 1]!=1 && able[LEFT]==false)
		{
			able[RIGHT] = true;
			currentAnimation = AnimationIndex::rightDirection;
			s_Blinky.move(2, 0);
        }
		else if(map.wall[row][col + 1] == 1)
		{
			able[RIGHT] = false;
		}
		if (map.wall[row][col - 1] != 1 && able[RIGHT]==false)
		{
			able[LEFT] = true;
			currentAnimation = AnimationIndex::leftDirection;
			s_Blinky.move(-2, 0);
		}
		else if(map.wall[row][col - 1] == 1)
		{
			able[LEFT] = false;
		}

	}
private:
	
	Animation animations[int(AnimationIndex::Count)];
	AnimationIndex currentAnimation = AnimationIndex::downStanding;
	std::string path = "Resources/Graphics/Ghost.png";
	Map map;
};



#endif