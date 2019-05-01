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

	sf::Clock clock;
	sf::Time time;
	//pinky
	sf::Vector2f pinky_to_pac;


	//inky 
	sf::Vector2f inky_to_pac;
	sf::Vector2f node1;
	sf::Vector2f node2;
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


		Pacman.Update(1.0f / 30.0f);
		time = clock.getElapsedTime();
		sf::Vector2f blinky_to_pac = { Pacman.x, Pacman.y };
		//Pinky 4 spaces ahead of Pacman.
		if (key == 4 && Pacman.x + (30 * 4) < 800 && Pacman.walking == true)
		{
			pinky_to_pac = { Pacman.x + (30 * 4), Pacman.y };
		}
		else if (key == 3 && Pacman.x - (30 * 4) > 0 && Pacman.walking == true)
		{
			pinky_to_pac = { Pacman.x - (30 * 4), Pacman.y };
		}
		else if (key == 2 && Pacman.y + (30 * 4) < 910 && Pacman.walking == true)
		{
			pinky_to_pac = { Pacman.x , Pacman.y + (30 * 4) };
		}
		else if (key == 1 && Pacman.y - (30 * 4) > 0 && Pacman.walking == true)
		{
			pinky_to_pac = { Pacman.x , Pacman.y - (30 * 4) };
		}
		else
		{
			pinky_to_pac = { Pacman.x, Pacman.y };
		}
		//inky 
		node1 = blinky.s_Blinky.getPosition();

		if (key == 4 && Pacman.x + (30 * 2) < 800 && Pacman.walking == true)
		{
			node2 = { Pacman.x + (30 * 2), Pacman.y };
		}
		else if (key == 3 && Pacman.x - (30 * 2) > 0 && Pacman.walking == true)
		{
			node2 = { Pacman.x - (30 * 2), Pacman.y };
		}
		else if (key == 2 && Pacman.y + (30 * 2) < 910 && Pacman.walking == true)
		{
			node2 = { Pacman.x , Pacman.y + (30 * 2) };
		}
		else if (key == 1 && Pacman.y - (30 * 2) > 0 && Pacman.walking == true)
		{
			node2 = { Pacman.x , Pacman.y - (30 * 2) };
		}
		if (node1.x + node2.x < 0 && node1.x + node2.x>800 && node1.y + node2.y < 0 && node1.y + node2.y > 910)
		{
			inky_to_pac = { (node1 + node2) };
		}
		else
		{
			inky_to_pac = { Pacman.x, Pacman.y };
		}
		/////////////////////////////////Update Ghosts/////////////////////////////////////////////

		if (time.asSeconds() >= 1)
		{
			blinky.Update(1, blinky_to_pac, blinky.s_Blinky);  //Update red Animtion
		}
		else
		{
			blinky.Update2(1);
		}
		if (time.asSeconds() >= 2)
		{
			pinky.Update(1, pinky_to_pac, pinky.s_Pinky);   //Update pink Animtion
		}
		else
		{
			pinky.Update3(1);
		}
		if (time.asSeconds() >= 5)
		{
			inky.Update(1.0f / 30.0f, inky_to_pac, inky.s_Inky);   //Update Blue Animtion
		}
		else
		{
			inky.Update4(1);
		}
		if (time.asSeconds() >= 7)
		{
			clyde.Update(1,blinky_to_pac,clyde.s_Clyde);  //Update orange Animtion
		}
		else
		{
			clyde.Update5(1);
		}
		///////////////////////////////////////////////////////////////////////////////////////////
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
			//window.draw(map.Actor);
			//window.display();
			//Sleep(800);
			//Pacman.x = 390.0f;
			//Pacman.y = 690.0f;
		}

		// window.draw(map.Actor);
		window.display();

	}



}