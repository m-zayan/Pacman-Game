#pragma once
#include<SFML/Graphics.hpp>
#include<sstream>
#include"Game.h"
#include"HighScore.h"
#ifndef Start_Menu_H

#define Start_menu_H

class Menu
{


public:

	void Background()
	{

		background.loadFromFile("Resources/Graphics/wallpaper.jpg");
		sprit.setTexture(background);
		sprit.setScale(1.2f, 1.2f);
		background.setSmooth(true);
	}
	void set_Button(sf::RenderWindow& window)
	{
		font.loadFromFile("Resources/Font/Button_Font.ttf");
		play.setFillColor(sf::Color::White);
		play.setPosition(370, 250);
		play.setString("Play");
		play.setCharacterSize(120);
		play.setFont(font);
		////////////////////////////////////////////// Play Button//////////////////////////////////////                             
		highscore.setFillColor(sf::Color::White);
		highscore.setPosition(370, 350);
		highscore.setString("High Scores");
		highscore.setCharacterSize(120);
		highscore.setFont(font);
		/////////////////////////////////////////////High Score Button///////////////////////////////////
		store.setFillColor(sf::Color::White);
		store.setPosition(370, 450);
		store.setString("Store");
		store.setCharacterSize(120);
		store.setFont(font);
		///////////////////////////////////////////Store Button///////////////////////////////////////////
	}
	void Play_Button(sf::RenderWindow& window)
	{
		mouse_pos = sf::Mouse::getPosition(window);
		if (mouse_pos.x >= 370 && mouse_pos.x <= 850 && mouse_pos.y >= 250 && mouse_pos.y <= 370)
		{ 
			
			play.setFillColor(sf::Color::Red);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				window.close();
				Game();
			}
		}
		else
		{
			play.setFillColor(sf::Color::White);
		}
	}
	void HighScore_Button(sf::RenderWindow& window)
	{
		mouse_pos = sf::Mouse::getPosition(window);
		if (mouse_pos.x >= 370 && mouse_pos.x <= 850 && mouse_pos.y >= 350 && mouse_pos.y <= 470)
		{
			highscore.setFillColor(sf::Color::Red);
		
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				HighScore();
			}
		}
		else
		{
			highscore.setFillColor(sf::Color::White);
		}
	}
	void Draw(sf::RenderWindow& window)
	{
		window.draw(sprit);
		window.draw(play);
		window.draw(highscore);
		window.draw(store);
	}
private:
	sf::Font font;
	sf::Text play;
	sf::Text highscore;
	sf::Text store;
	sf::Texture background;
	sf::Sprite sprit;
	sf::Mouse mouse;
	sf::Event event;
	sf::Vector2i mouse_pos;
	};


void StarMenu();









#endif // !Start_Menu_H

