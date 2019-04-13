#include <SFML/Graphics.hpp>
#include"Animation.h"
#include"Player.h"
#include"Map.h"

void Game()
{
	sf::RenderWindow window(sf::VideoMode(840, 980), "Pacman");
	window.setPosition(sf::Vector2i(480, 0));

	Player Pacman({ 405.0f,690.0f });
	Map map;
	map.Setup();

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

		map.Read_Map();
		//handel input;
		sf::Vector2f direction = { 0.0f,0.0f };
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{

			direction.y -= 1.0f;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			direction.y += 1.0f;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			direction.x += 1.0f;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			direction.x -= 1.0f;
		}
		Pacman.SetDirection(direction);

		//update model

		Pacman.Update(1.0f / 60.0f);

		window.clear();
		map.Draw(window);
		Pacman.Draw(window);

		window.display();

	}


	
}