#include <SFML/Graphics.hpp>
#include"Animation.h"
#include"Player.h"
#include"Map.h"
sf::Event event;
int key = 0;
void Game()
{
	sf::RenderWindow window(sf::VideoMode(840, 980), "Pacman");
	window.setPosition(sf::Vector2i(480, 0));
	
	window.setVerticalSyncEnabled(true);
	window.setKeyRepeatEnabled(false);
	Player Pacman({ 390.0f,690.0f });
	Map map;
	map.Actor.setRadius(15);
	//map.Actor.setFillColor(sf::Color::Blue);
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
		//std::cout << DotX << " " << DotY <<" "<<col<<" "<<row<< std::endl;
		//handel input;
		sf::Vector2f direction = { 0.0f,0.0f };
		if (event.key.code==sf::Keyboard::Up && map.wall[row - 1][col] != 1)
		{

			direction.y -= 1.0f;
			Pacman.keymove(1);
			key = 1;
		}
		else if (event.key.code == sf::Keyboard::Down && map.wall[row+1][col] != 1)
		{
			direction.y += 1.0f;
			Pacman.keymove(2);
			key = 2;
		}
		else if (event.key.code == sf::Keyboard::Right && map.wall[row][col + 1] != 1)
		{
			direction.x += 1.0f;
			Pacman.keymove(4);
			key = 4;
		}
		else if (event.key.code == sf::Keyboard::Left && map.wall[row][col-1]!=1)
		{
			direction.x -= 1.0f;
			Pacman.keymove(3);
			key = 3;
		}
		else if(key == 1 && map.wall[row - 1][col] != 1)
		{
			Pacman.keymove(key);
		}
		else if (key == 2 && map.wall[row +1][col] != 1)
		{
			Pacman.keymove(key);
		}
		else if (key == 3 && map.wall[row][col-1] != 1)
		{
			Pacman.keymove(key);
		}
		else if (key == 4 && map.wall[row][col + 1] != 1)
		{
			Pacman.keymove(key);
		}
		Pacman.SetDirection(direction);

		//update model
		
		Pacman.Update(1.0f / 30.0f);
		map.Actor.setPosition(Pacman.x, Pacman.y); //Follow Pacman 
		
		window.clear();
		map.Draw(window);
		Pacman.Draw(window);
       // window.draw(map.Actor);
		window.display();

	}


	
}