#include<SFML/Graphics.hpp>
#include"Game.h"
#include"HighScore.h"
void GameOver()
{
	sf::RenderWindow window(sf::VideoMode(1375, 851), "Pacman");
	window.setPosition(sf::Vector2i(280,100));
	GameS gameover;
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
		gameover.GameOver(window);
		window.display();
	}

}