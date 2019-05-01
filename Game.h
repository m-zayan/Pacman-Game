#pragma once
#include<SFML/Graphics.hpp>
#include"Player.h"
#include "Animation.h"

#ifndef Game_H

#define Game_H

class GameS
{
public:
	bool die[3] = {};
	GameS()
	{
		texture.loadFromFile("Resources/Graphics/lives .png");
		texture.setSmooth(true);
		lives.setTexture(texture);
		lives.setScale(1, 0.9);
		lives.setTextureRect({ 0,0,40,37 });
		texture2.loadFromFile("Resources/Graphics/GameOver.jpg");
		texture2.setSmooth(true);
		gameOver.setTexture(texture2);
	}
	void Draw(sf::RenderWindow& window)
	{
		for (int i = 0; i < 3; i++)
		{
			
			lives.setPosition(600+(i*40),940);
			if (die[i] == false)
			{
				window.draw(lives);
			}
		}
	}
	void GameOver(sf::RenderWindow& window)
	{
		window.draw(gameOver);
	}
private:
	sf::Texture texture;
	sf::Sprite lives;
	sf::Texture texture2;
	sf::Sprite gameOver;
};
void Game();

#endif // !Game_H