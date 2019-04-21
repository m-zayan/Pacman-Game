#include <SFML/Graphics.hpp>
#include"Animation.h"
#include"Player.h"
#include"Map.h"
sf::Event event;

void Game()
{
	sf::RenderWindow window(sf::VideoMode(840, 980), "Pacman");
	window.setPosition(sf::Vector2i(480, 0));
	window.setVerticalSyncEnabled(true);
	window.setKeyRepeatEnabled(false);
	Player Pacman({ 405.0f,720.0f });
	Map map;
	map.Setup();
    map.Read_Map();
	map.Wall();	
	while (window.isOpen())
	{
		
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.key.code == sf::Keyboard::Escape)
				window.close();

		}
		int col = Pacman.x / 30;  //x
		int row = Pacman.y / 30; //y

		//handel input;
		sf::Vector2f direction = { 0.0f,0.0f };
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && map.wall[row - 1][col] != 1)
		{

			direction.y -= 1.0f;
			Pacman.keymove(1);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && map.wall[row+1][col] != 1)
		{
			direction.y += 1.0f;
			Pacman.keymove(2);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && map.wall[row][col + 1] != 1)
		{
			direction.x += 1.0f;
			Pacman.keymove(4);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && map.wall[row][col-1]!=1)
		{
			direction.x -= 1.0f;
			Pacman.keymove(3);
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