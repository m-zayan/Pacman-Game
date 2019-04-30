#pragma once
#include<SFML/Graphics.hpp>
#include"Player.h"
#include "Animation.h"
#include<iostream>
#ifndef Player_H

#define Player_H


class Player
{
public:
	Player() = default;
	sf::Sprite sprite;
	sf::Vector2f velocity = { 0.0f,0.0f };
	enum MOVE { UP, DOWN, LEFT, RIGHT }; //enums instead of remember numbers
	bool move[4] = { false,false, false, false }; //deciding if You move up/down/left/right
	bool walking=false;
	float nextspot; //the next tilespot of the map
	float x = 390;
	float y = 690;
	float movespeed=5;
private:
	enum class AnimationIndex
	{
		upDirection,
		downDirection,
		rightDirection,
		leftDirection,
		upStanding,
		downStanding,
		rightStanding,
		leftStanding,
		Count
	};
public:
	Player(const sf::Vector2f& position)
		:
		position(position)

	{



		sprite.setTextureRect({ 0,0,30,30 });
		animations[int(AnimationIndex::rightDirection)] = Animation(30, 0, 30, 30, 3, 0.4f,pac);
		animations[int(AnimationIndex::leftDirection)] = Animation(30, 30, 30, 30, 3, 0.4f,pac);
		animations[int(AnimationIndex::upDirection)] = Animation(30, 60, 30, 30, 3, 0.4f,pac);
		animations[int(AnimationIndex::downDirection)] = Animation(30, 90, 30, 30, 3, 0.4f,pac);
		animations[int(AnimationIndex::rightStanding)] = Animation(30, 0, 30, 30, 1, 10.8f,pac);
		animations[int(AnimationIndex::leftStanding)] = Animation(30, 30, 30, 30, 1, 10.8f,pac);
		animations[int(AnimationIndex::upStanding)] = Animation(30, 60, 30, 30, 1, 10.8f,pac);
		animations[int(AnimationIndex::downStanding)] = Animation(30, 90, 30, 30, 1, 10.8f,pac);
	}
	void Draw(sf::RenderTarget& rt) const
	{
		rt.draw(sprite);


	}
	void SetDirection(const sf::Vector2f& dir)
	{

		if (dir.x > 0.0f)
		{
			currentAnimation = AnimationIndex::rightDirection;
		}
		else if (dir.x < 0.0f)
		{
			currentAnimation = AnimationIndex::leftDirection;
		}
		else if (dir.y < 0.0f)
		{
			currentAnimation = AnimationIndex::upDirection;
		}
		else if (dir.y > 0.0f)
		{
			currentAnimation = AnimationIndex::downDirection;
		}
		else
		{
			if (velocity.x > 0.0f)
			{
				currentAnimation = AnimationIndex::rightStanding;
			}
			else if (velocity.x < 0.0f)
			{
				currentAnimation = AnimationIndex::leftStanding;
			}
			else if (velocity.y < 0.0f)
			{
				currentAnimation = AnimationIndex::upStanding;
			}
			else if (velocity.y > 0.0f)
			{
				currentAnimation = AnimationIndex::downStanding;
			}
		}
		velocity = dir * speed;
	}

	void keymove(int key)
	{
		if (key==1)  //Up =1 , DOWN =2 ,Left=3 ,Right=4.
		{
			if (walking == false)
			{

				nextspot = y - 30;

				move[UP] = true;
				walking = true;

			}
		}

		if (key==2)
		{
			if (walking == false)
			{
				nextspot = y + 30;
				move[DOWN] = true;
				walking = true;
			}
		}

		if (key ==3)
		{
			if (walking == false)
			{
				nextspot = x - 30;
				move[LEFT] = true;
				walking = true;
			}
		}

		if (key ==4)
		{
			if (walking == false)
			{
				nextspot = x + 30;
				move[RIGHT] = true;
				walking = true;
			}

		}
	}
	void moving()
	{
		if (walking == true)
		{
			if (move[UP] == true)
			{
				y -= movespeed;


				if (y <= nextspot)
				{
					y = nextspot;
					walking = false;
					move[UP] = false;
				}
			}

			if (move[DOWN] == true)
			{
				y += movespeed;
				if (y >= nextspot)
				{
					y = nextspot;
					walking = false;
					move[DOWN] = false;
				}
			}
			if (move[LEFT] == true)
			{
				x -= movespeed;
				if (x <= nextspot)
				{
					x = nextspot;
					walking = false;
					move[LEFT] = false;
				}
			}
			if (move[RIGHT] == true)
			{
				x += movespeed;
				if (x >= nextspot)
				{
					x = nextspot;
					walking = false;
					move[RIGHT] = false;
				}
			}
		}
	}
	void Update(float deltaTime)
	{
		//position += velocity * deltaTime;
		animations[int(currentAnimation)].Update(deltaTime);
		animations[int(currentAnimation)].ApplyToSprite(sprite);
		moving();
		sprite.setPosition(x,y);
		//std::cout << "position X :" << x/30 << " " << "Position Y :" << y/30 <<std:: endl;
	}

private:
	static constexpr float speed = 30.0f;
	sf::Vector2f position;
	
	
	std::string pac = "Resources/Graphics/Pacman.png";
	Animation animations[int(AnimationIndex::Count)];
	AnimationIndex currentAnimation = AnimationIndex::rightStanding;

};


#endif