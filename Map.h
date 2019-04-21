#pragma once
#include<SFML/Graphics.hpp>
#include"Player.h"
#include<fstream>
#include<string>
#ifndef Map_H


#define Map_H

class Map
{
public:

	bool wall[31][28] = {};
	void Setup()
	{
		texture.loadFromFile("Resources/Map/Map.png");
		sprite.setTexture(texture);
		//tiles.setSize(sf::Vector2f(30, 30));
		//tiles.setFillColor(sf::Color::Blue);
		superDots.setRadius(10.0f);
		superDots.setOrigin(10.0f, 10.0f);
		superDots.setFillColor(sf::Color::Yellow);
		PacDots.setFillColor(sf::Color::Yellow);
		PacDots.setRadius(3.75f);
		PacDots.setOrigin(3.75, 3.75f);

	}
	void Read_Map()
	{
		iFile.open("Resources/Map/Map.txt");
		for (int row = 0; row < 31; row++)
		{
			for (int col = 0; col < 28; col++)
			{
				iFile >> map[row][col];
			}
		}

		iFile.close();
	}
	void Wall()
	{
		for (int row = 0; row < 31; row++)
		{
			for (int col = 0; col < 28; col++)
			{
				if (map[row][col] == 'W')
				{
					wall[row][col] = true;

				}
			}
		}
	}

	void Draw(sf::RenderWindow& window)
	{
		window.draw(sprite);
		for (int row = 0; row < 31; row++)
		{
			for (int col = 0; col < 28; col++)
			{
				if (map[row][col] == 'W')
				{
					//tiles.setPosition(col* 30.0f, row* 30.0f);
					//window.draw(tiles);

				}
				else if (map[row][col] == 'd' || map[row][col] == 'n' || map[row][col] == 's')  // n Pacman node //s Ghost Nodes
				{
					PacDots.setPosition((col * 30.0f) + 15, (row * 30.0f) + 15);
					window.draw(PacDots);
				}
				else if (map[row][col] == 'D') //Super dots.
				{
					superDots.setPosition((col * 30.0f) + 15, (row * 30.0f) + 15);
					window.draw(superDots);
				}

			}
		}
	}

private:
	//sf::RectangleShape tiles;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::CircleShape PacDots;
	sf::CircleShape superDots;
	std::ifstream iFile;
	std::ofstream oFile;
	char map[31][28];
	Player Pacman;


};





#endif // !Map_H
