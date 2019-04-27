#pragma once
#include<SFML/Graphics.hpp>
#include"Player.h"
#include"HighScore.h"
#include<fstream>
#include<string>
#ifndef Map_H


#define Map_H

class Map
{
public:
	sf::CircleShape Actor;
	bool wall[31][28] = {};
	bool not_eaten_dots[31][28] = {};

	Map()
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

		iFile.open("Resources/Map/Map.txt");
		for (int row = 0; row < 31; row++)
		{
			for (int col = 0; col < 28; col++)
			{
				iFile >> map[row][col];
			}
		}

		iFile.close();

		for (int row = 0; row < 31; row++)
		{
			for (int col = 0; col < 28; col++)
			{
				if (map[row][col] == 'W')
				{
					wall[row][col] = true;

				}
				else if (map[row][col] == 'd' || map[row][col] == 'n' || map[row][col] == 's')  // n Pacman node //s Ghost Nodes
				{
					not_eaten_dots[row][col] = true;
				}
			}
		}
	}
	void Draw(sf::RenderWindow& window,Score& Sscore)
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
					

					if (not_eaten_dots[row][col] == true)
					{
						window.draw(PacDots);
						if (Actor.getGlobalBounds().intersects(PacDots.getGlobalBounds()))
						{
							not_eaten_dots[row][col] = false;
								Sscore.score += 10;
                               Sscore.Sscore.str("");
	                      Sscore.Sscore << "Score : " << Sscore.score;
	                      Sscore.text.setString(Sscore.Sscore.str());
						}
					}
				}
				else if (map[row][col] == 'D') //Super dots.
				{
					superDots.setPosition((col * 30.0f) + 15, (row * 30.0f) + 15);
					window.draw(superDots);
				}

			}
		}
	}
	bool win(Score& Sscore)
	{
		int win = 1;

			for (int row = 0; row < 31; row++)
			{
				for (int col = 0; col < 28; col++)
				{
					if (not_eaten_dots[row][col] == true)
					{
						win = 0;
					}
				}
			}	
	    if (win == 1)
		{
			return true;
		}
		else
		{
			return false;
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
