#include<SFML/Graphics.hpp>
#include "HighScore.h"
#include"Animation.h"

void HighScore()
{
	sf::RenderWindow window(sf::VideoMode(960, 960), "Pacman");
	window.setPosition(sf::Vector2i(480, 0));
	sf::Font font; //must be in class
	font.loadFromFile("Resources/Font/high.ttf");
	sf::Text high;
	high.setFillColor(sf::Color::Yellow);
	high.setPosition(120, 20);
	high.setString("High Scores");
	high.setCharacterSize(120);
	high.setFont(font);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.key.code == sf::Keyboard::Escape)
				window.close();
		}
		window.clear();
		window.draw(high);
		window.display();
	
	
	}

}