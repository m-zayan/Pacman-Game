#pragma once
#include<SFML/Graphics.hpp>
#include<sstream>
#ifndef Animation_H


#define Animation_H


class Animation
{
public:
	Animation() = default;
	Animation(int x, int y, int width, int height, int nFrames, float holdTime , std::string path_sprite)
		:
		holdTime(holdTime)
	{
		frames.reserve(nFrames);
		texture.loadFromFile(path_sprite);
		texture.setSmooth(true);
		for (int i = 0; i < nFrames; i++)
		{
			frames.emplace_back(sf::Vector2i{ x,y }, sf::Vector2i{ width,height });
			x += width;
		}
	}
	void ApplyToSprite(sf::Sprite& s)const
	{

		s.setTexture(texture);
		s.setTextureRect(frames[iFrame]);
	}
	void Update(float deltaTime)
	{
		time += deltaTime;
		while (time >= holdTime)
		{
			time -= holdTime;
			Advance();
		}
	}
private:
	void Advance()
	{
		if (++iFrame >= int(frames.size()))
		{
			iFrame = 0;
		}
	}
private:
	float holdTime;
	sf::Texture texture;
	std::vector<sf::IntRect>frames;
	int iFrame = 0;
	float time = 0.0f;

};




#endif 
