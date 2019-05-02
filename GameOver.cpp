#include<SFML/Graphics.hpp>
#include"Game.h"
#include"HighScore.h"
#include<sstream>

void GameOver(int s)
{
	sf::RenderWindow window(sf::VideoMode(1375, 851), "Pacman");
	window.setPosition(sf::Vector2i(280,100));
	sf::Font font;
	font.loadFromFile("Resources/Font/Name.ttf");
	GameS gameover;
	Score Sscore;
	sf::String Name;
	sf::Text text(Name, font, 40);
	text.setFillColor(sf::Color(51, 51, 255));
	text.setStyle(sf::Text::Bold);
	text.setCharacterSize(70);
	text.setPosition(280, 0);
	sf::Text text2(Name, font, 40);
	text2.setFillColor(sf::Color(51, 51, 255));
	text2.setStyle(sf::Text::Bold);
	text2.setCharacterSize(70);
	std::string string;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.key.code == sf::Keyboard::Escape)
				window.close();
			switch (event.type)
			{

			case sf::Event::TextEntered:
				if (event.text.unicode >= 32 && event.text.unicode <= 126)
				{
					Name += char(event.text.unicode);
				}
				else if (event.text.unicode == 8 && Name.getSize() > 0)
				{
					Name.erase(Name.getSize() - 1, Name.getSize());
				}
				text.setString(Name);
				break;
			}

		}
		
		text2.setString("Name : ");
		string = (std::string)Name;
		std::ofstream writeFile("Resources/HighScore/Name.txt");
		if (writeFile.is_open())
		{
			writeFile << string<<"\n";
		}
		window.clear();
		gameover.GameOver(window);
		window.draw(text);
		window.draw(text2);
		window.display();
	}

}