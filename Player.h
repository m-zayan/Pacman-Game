#pragma once
#include<SFML/Graphics.hpp>
#include"Player.h"
#include "Animation.h"


#ifndef Player_H

#define Player_H


class Player
{
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
		animations[int(AnimationIndex::rightDirection)] = Animation(30, 0, 30, 30, 3, 0.4f);
		animations[int(AnimationIndex::leftDirection)] = Animation(30, 30, 30, 30, 3, 0.4f);
		animations[int(AnimationIndex::upDirection)] = Animation(30, 60, 30, 30, 3, 0.4f);
		animations[int(AnimationIndex::downDirection)] = Animation(30, 90, 30, 30, 3, 0.4f);
		animations[int(AnimationIndex::rightStanding)] = Animation(30, 0, 30, 30, 1, 10.8f);
		animations[int(AnimationIndex::leftStanding)] = Animation(30, 30, 30, 30, 1, 10.8f);
		animations[int(AnimationIndex::upStanding)] = Animation(30, 60, 30, 30, 1, 10.8f);
		animations[int(AnimationIndex::downStanding)] = Animation(30, 90, 30, 30, 1, 10.8f);
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
	void Update(float deltaTime)
	{
		position += velocity * deltaTime;
		animations[int(currentAnimation)].Update(deltaTime);
		animations[int(currentAnimation)].ApplyToSprite(sprite);
		sprite.setPosition(position);
	}

private:
	static constexpr float speed = 30.0f;
	sf::Vector2f position;
	sf::Vector2f velocity = { 0.0f,0.0f };
	sf::Sprite sprite;
	Animation animations[int(AnimationIndex::Count)];
	AnimationIndex currentAnimation = AnimationIndex::rightStanding;

};


#endif