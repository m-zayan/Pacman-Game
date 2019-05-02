#pragma once
#include<SFML/Graphics.hpp>
#include<sstream>
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
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
		text.setPosition(100, 930);
		text.setString(Sscore.str());	
	
	}
	void Display_Score(sf::RenderWindow& window)
	{
		text.setPosition(100, 930);
		window.draw(text);
	}
	void Display_Re(sf::RenderWindow& window)
	{
		text.setPosition(500, 0);
		window.draw(text);
	}
	

private:

	sf::Font font;
};

void HighScore();



#endif // ! HighScore_H



