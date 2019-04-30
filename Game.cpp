#include <SFML/Graphics.hpp>
#include<Windows.h>
#include"Animation.h"
#include"HighScore.h"
#include"Player.h"
#include"Map.h"
#include"Blinky.h" //Red  Ghost
#include"Pinky.h"  //Pink Ghost
#include"Inky.h"   //Blue Ghost
#include"Clyde.h" //Orange Ghost
sf::Event event;
int key = 0;
void Game()
{
	bool gamePause = true;
	sf::RenderWindow window(sf::VideoMode(840, 980), "Pacman");
	window.setPosition(sf::Vector2i(480, 0));
	Score Sscore;
	Blinky blinky({ 420.0f,330.0f });
	Pinky pinky({ 375.0f,420.0f });
	Inky inky({ 405.0f,420.0f });
	Clyde clyde({ 435.0f,420 });
	window.setVerticalSyncEnabled(true);
	window.setKeyRepeatEnabled(false);
	Player Pacman({ 390.0f,690.0f });
	Map map;
	map.Actor.setRadius(15);
	//blinky.FindPath(Pacman, blinky);
	sf::Clock clock;
	sf::Time time;
	float dt = 1/60;
	while (window.isOpen())
	{

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.key.code == sf::Keyboard::Escape)
				window.close();

		}
		int col = (int)Pacman.x / 30;  //x
		int row = (int)Pacman.y / 30; //y



		//handel input;
		sf::Vector2f direction = { 0.0f,0.0f };
		if (event.key.code == sf::Keyboard::Up && map.wall[row - 1][col] != 1)
		{

			direction.y -= 1.0f;
			Pacman.keymove(1);
			key = 1;
		}
		else if (event.key.code == sf::Keyboard::Down && map.wall[row + 1][col] != 1)
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
		else if (event.key.code == sf::Keyboard::Left && map.wall[row][col - 1] != 1)
		{
			direction.x -= 1.0f;
			Pacman.keymove(3);
			key = 3;
		}
		else if (key == 1 && map.wall[row - 1][col] != 1)
		{
			direction.y -= 1.0f;
			Pacman.keymove(key);
		}
		else if (key == 2 && map.wall[row + 1][col] != 1)
		{
			direction.y += 1.0f;
			Pacman.keymove(key);
		}
		else if (key == 3 && map.wall[row][col - 1] != 1)
		{
			direction.x -= 1.0f;
			Pacman.keymove(key);
		}
		else if (key == 4 && map.wall[row][col + 1] != 1)
		{
			direction.x += 1.0f;
			Pacman.keymove(key);
		}
		Pacman.SetDirection(direction);

		//Gpos= blinky.FindPath(Pacman, blinky.s_Blinky);
		//std::cout << Gpos.x << " " << Gpos.y << std::endl;
		//blinky.s_Blinky.setPosition((Gpos.x * 30), Gpos.y * 30);
		//Sleep(100);
		//update model


		Pacman.Update(1.0f / 30.0f);
		blinky.Update(1,Pacman,blinky.s_Blinky);  //Update red Animtion
		pinky.Update(1.0f / 30.0f);   //Update pink Animtion
		inky.Update(1.0f / 30.0f);   //Update Blue Animtion
		clyde.Update(1.0f / 30.0f);  //Update orange Animtion
		map.Actor.setPosition(Pacman.x, Pacman.y); //Follow Pacman 

		window.clear();
		map.Draw(window, Sscore);
		Pacman.Draw(window);
		blinky.Draw(window);  //Draw red
		pinky.Draw(window);   //Draw pink
		inky.Draw(window);    //Draw Blue
		clyde.Draw(window);   // Draw orange
		Sscore.Display_Score(window);
		if (Sscore.score >= 2400)
		{
			if (map.win(Sscore) == true)
			{
				break;
			}
		}
		if (map.Actor.getGlobalBounds().intersects(blinky.s_Blinky.getGlobalBounds())) //life
		{
			window.draw(map.Actor);
			window.display();
			//Sleep(800);
			//Pacman.x = 390.0f;
			//Pacman.y = 690.0f;
		}

		// window.draw(map.Actor);
		window.display();

	}



}