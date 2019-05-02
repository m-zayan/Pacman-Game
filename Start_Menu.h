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

		background.loadFromFile("Resources/Graphics/Pacman Menu.png");
		background.setSmooth(true);
		sprit.setTexture(background);
		//sprit.setScale(1.2f, 1.2f);
		sprit.setPosition(-220, 0);
		
	}
	void set_Button(sf::RenderWindow& window)
	{
		font.loadFromFile("Resources/Font/Button_Font.ttf");
		play.setFillColor(sf::Color::White);
		play.setPosition(320,480);
		play.setString("Play");
		play.setCharacterSize(60);
		play.setFont(font);
		////////////////////////////////////////////// Play Button//////////////////////////////////////                             
		highscore.setFillColor(sf::Color::White);
		highscore.setPosition(160, 560);
		highscore.setString("Leaderboard");
		highscore.setCharacterSize(60);
		highscore.setFont(font);
		/////////////////////////////////////////////High Score Button///////////////////////////////////
		//store.setFillColor(sf::Color::White);
		//store.setPosition(370, 450);
		//store.setString("Store");
		//store.setCharacterSize(120);
		//store.setFont(font);
		///////////////////////////////////////////Store Button///////////////////////////////////////////
	}
	void Play_Button(sf::RenderWindow& window)
	{
		mouse_pos = sf::Mouse::getPosition(window);
		if (mouse_pos.x >= 320 && mouse_pos.x <= 560 && mouse_pos.y >= 480 && mouse_pos.y <= 540)
		{ 
			
			play.setFillColor(sf::Color::Red);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sgame.Menu_Selection_Sound.play();
				sgame.Play_Sound(3);
				if (window.isOpen())
				{

					window.setVisible(false);
				}
				Game();
			}
			window.setVisible(true);
		}
		else
		{
			play.setFillColor(sf::Color::White);
		}
	}
	void HighScore_Button(sf::RenderWindow& window)
	{
		mouse_pos = sf::Mouse::getPosition(window);
		if (mouse_pos.x >= 160 && mouse_pos.x <= 820 && mouse_pos.y >= 560 && mouse_pos.y <= 620)
		{
			highscore.setFillColor(sf::Color::Red);
		
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sgame.Menu_Selection_Sound.play();
				sgame.Play_Sound(3);
				if (window.isOpen())
				{

					window.setVisible(false);
				}
				HighScore();
			}
			window.setVisible(true);
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
	//	window.draw(store);
	}
private:
	sf::Font font;
	sf::Text play;
	sf::Text highscore;
	//sf::Text store;
	sf::Texture background;
	sf::Sprite sprit;
	sf::Mouse mouse;
	sf::Event event;
	sf::Vector2i mouse_pos;
	GameS sgame;
	};


void StarMenu();









#endif // !Start_Menu_H

