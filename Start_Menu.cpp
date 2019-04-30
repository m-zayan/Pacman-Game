#include <SFML/Graphics.hpp>
#include "Start_Menu.h"


void StarMenu()
{
	sf::RenderWindow window(sf::VideoMode(840, 960), "Pacman");
	window.setPosition(sf::Vector2i(480, 0));
	window.setKeyRepeatEnabled(false);
	window.setVerticalSyncEnabled(true);
	Menu main;

	main.set_Button(window);
	main.Background();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.key.code == sf::Keyboard::Escape)
				window.close();

		}
	
		main.Play_Button(window);
		main.HighScore_Button(window);
		window.clear();
		main.Draw(window);
		window.display();

	}


}

