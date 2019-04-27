#pragma once
#include<SFML/Graphics.hpp>
#include<sstream>
#include<fstream>
#include<vector>
#ifndef  HighScore_H

#define HighScore_H

class Score
{
public:
	sf::Text text;
	std::ostringstream Sscore;
	int score = 0;
	Score()
	{
		font.loadFromFile("Resources/Font/Number.ttf");
		Sscore << "Score : " << score;
		text.setFont(font);
		text.setFillColor(sf::Color::Red);
		text.setStyle(sf::Text::Bold);
		text.setCharacterSize(30);
		text.setPosition(600, 930);
		text.setString(Sscore.str());
	}
	void Display_Score(sf::RenderWindow& window)
	{
		window.draw(text);
	}
	void Read()
	{
		readFile.open("Resources/HighScore/HighScore.txt");
		if (readFile.is_open())
		{
			while (!readFile.eof())
			{
				readFile >> toVector;
				newS.push_back(toVector);
			}
		}
		readFile.close();
	}
	void Out()
	{
		std::ofstream writeFile("Resources/HighScore/HighScore.txt");
		if (writeFile.is_open())
		{
			
		}
	}

private:
	std::ifstream readFile;
	std::vector<int>newS;
	sf::Font font;
	int toVector;
};

class HighS
{
public:
	HighS()
	{
		
		font.loadFromFile("Resources/Font/high.ttf");
		high.setFillColor(sf::Color::Yellow);
		high.setPosition(120, 20);
		high.setString("High Scores");
		high.setCharacterSize(120);
		high.setFont(font);
		texture.loadFromFile("Resources/Graphics/HighB.jpg");
		sprite.setTexture(texture);
		sprite.setScale(3.2f, 5.7f);
	}
	void Draw(sf::RenderWindow& window)
	{
		window.draw(sprite);
		window.draw(high);
		
	}
private:
	sf::Font font; 
	sf::Text high;
	sf::Texture texture;
	sf::Sprite sprite;
};

void HighScore();



#endif // ! HighScore_H



