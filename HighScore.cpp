#include<SFML/Graphics.hpp>
#include "HighScore.h"
#include"Animation.h"

void HighScore()
{
	sf::RenderWindow window(sf::VideoMode(960, 960), "Pacman");
	window.setPosition(sf::Vector2i(480, 0));
	HighS SHigh;
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
		SHigh.Draw(window);
		window.display();
	
	
	}

}