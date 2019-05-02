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
#include"Game.h"
#include"GameOver.h"
sf::Event event;
int key =0;
	int lives = 3;
	int leve = 1;
void Game()
{
	bool gamePause = true;
	enum Sound { START, Eating, Death };
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
	map.superDot_eaten = false;
	map.Actor.setRadius(15);
	GameS sgame;
	sf::Clock clock;
	sf::Clock frClock;
	sf::Time time;
	sf::Time frTime;
	//pinky
	sf::Vector2f pinky_to_pac;
	sgame.Play_Sound(START);
	//inky 
	sf::Vector2f inky_to_pac;
	sf::Vector2f node1;
	sf::Vector2f node2;
	bool Geaten = false;
	bool Geaten1 = false;
	bool Geaten2 = false;
	bool Geaten3 = false;
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
		if (time.asSeconds() > 0.5)
		{
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
		}
		Pacman.SetDirection(direction);

		
		Pacman.Update(1.0f / 30.0f);
		if (map.superDot_eaten == true && frTime.asSeconds()<15)
		{
			frTime = frClock.getElapsedTime();
			blinky.Frightened_Mode(1,frTime, Geaten);
			inky.Frightened_Mode(1, frTime, Geaten2);
			clyde.Frightened_Mode(1, frTime, Geaten3);
			pinky.Frightened_Mode(1, frTime,Geaten1);
			blinky.movespeed = 1;
			 inky.movespeed = 1;
			 clyde.movespeed = 1;
			 pinky.movespeed = 1;
			
		}
	    if(frTime.asSeconds()>15 && map.superDot_eaten ==true )
		{
			frClock.restart();
			frTime = frClock.restart();
			map.superDot_eaten = false;
			 Geaten = false;
			 Geaten1 = false;
			 Geaten2 = false;
			 Geaten3 = false;
			 blinky.movespeed = 3;
			 inky.movespeed = 2;
			 clyde.movespeed = 1.5;
			 pinky.movespeed = 2;
		}
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

		if (time.asSeconds() >= 4 && Geaten == false) //Chase Mode
		{
			blinky.Update(1, blinky_to_pac, blinky.s_Blinky);  //Update red Animtion
			
		}
		else if (Geaten == true) //eaten blinky
		{
		blinky.Update(1, {420.0f,330.0f }, blinky.s_Blinky);
		}

		else
		{
			blinky.Update2(0.5f,blinky.s_Blinky);

		}
		if (time.asSeconds() >= 5 && Geaten1 == false) //Chase Mode
		{
			pinky.Update(1, pinky_to_pac, pinky.s_Pinky);   //Update pink Animtion
		}
		else if (Geaten1 == true) //eaten pinky
		{
			pinky.Update(1, { 390.0f,420.0f }, pinky.s_Pinky); //
		}
		else
		{
			pinky.Update3(0.5f,pinky.s_Pinky);
		}
		if (time.asSeconds() >= 8 && Geaten2== false) //Chase Mode
		{
			inky.Update(1, inky_to_pac, inky.s_Inky);   //Update Blue Animtion
		}
		else if (Geaten2 == true) //eaten inky
		{
			inky.Update(1, { 420.0f,420.0f }, inky.s_Inky);
		}
		else
		{
			inky.Update4(0.5f,inky.s_Inky);
		}
		if (time.asSeconds() >= 10 && Geaten3 == false) //Chase Mode
		{
			clyde.Update(1,blinky_to_pac,clyde.s_Clyde);  //Update orange Animtion
		}
		else if (Geaten3 == true) //eaten clyde
		{
			clyde.Update(1, { 450.0f,420 }, clyde.s_Clyde);
		}
		else
		{
			clyde.Update5(0.5f, clyde.s_Clyde);
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
		sgame.Draw(window);
		if (Sscore.score >= 2800)
		{
			if (map.win(Sscore) == true)
			{
				break; //Level Up.
			}
		}
		if (map.superDot_eaten == false)
		{
			if (map.Actor.getGlobalBounds().intersects(blinky.s_Blinky.getGlobalBounds()) ||
				map.Actor.getGlobalBounds().intersects(inky.s_Inky.getGlobalBounds()) ||
				map.Actor.getGlobalBounds().intersects(pinky.s_Pinky.getGlobalBounds()) ||
				map.Actor.getGlobalBounds().intersects(clyde.s_Clyde.getGlobalBounds())) //life
			{
				Pacman.Die(1 / 30, Pacman.sprite);
				clock.restart();
				time = clock.restart();
				sgame.die[lives - 1] = true;
				lives--;
				sgame.Play_Sound(Death);
			}
		}
		else if (map.superDot_eaten==true)
		{
			if (map.Actor.getGlobalBounds().intersects(blinky.s_Blinky.getGlobalBounds()) )
			{
				Geaten = true;
				Sscore.score += 100;
				Sscore.Sscore.str("");
				Sscore.Sscore << "Score : " << Sscore.score;
				Sscore.text.setString(Sscore.Sscore.str());
				blinky.movespeed = 5;

			}
			if (map.Actor.getGlobalBounds().intersects(pinky.s_Pinky.getGlobalBounds()))
			{
				Geaten1 = true;
				Sscore.score += 50;
				Sscore.Sscore.str("");
				Sscore.Sscore << "Score : " << Sscore.score;
				Sscore.text.setString(Sscore.Sscore.str());
				pinky.movespeed = 5;
			}
			if (map.Actor.getGlobalBounds().intersects(inky.s_Inky.getGlobalBounds()))
			{
				Geaten2 = true;
				Sscore.score += 50;
				Sscore.Sscore.str("");
				Sscore.Sscore << "Score : " << Sscore.score;
				Sscore.text.setString(Sscore.Sscore.str());
				inky.movespeed = 5;
			}
			if (map.Actor.getGlobalBounds().intersects(clyde.s_Clyde.getGlobalBounds()))
			{
				Geaten3 = true;
				Sscore.score += 50;
				Sscore.Sscore.str("");
				Sscore.Sscore << "Score : " << Sscore.score;
				Sscore.text.setString(Sscore.Sscore.str());
				clyde.movespeed = 5;

			}
		}
		if (lives == 0)
		{
			window.setVisible(false);
			window.setActive(false);
			leve = 1;
			break;

		}

		// window.draw(map.Actor);
		window.display();

	}
	if (lives == 0)
	{
		lives = 3;
		leve = 1;
		std::ifstream readFile;
		int PrevS;
		int new_score = 0;
		readFile.open("Resources/HighScore/HighScore.txt");

		if (readFile.is_open())
		{
			while (!readFile.eof())
			{
				readFile >> PrevS;

			}
		}
		if (PrevS < Sscore.score)
		{
			new_score = 1;
			std::ofstream writeFile("Resources/HighScore/HighScore.txt");
			if (writeFile.is_open())
			{
				writeFile << Sscore.score;
			}
		}
		if(new_score==0)
		GameOver(0);
		else
		{
			GameOver(1);
		}
	}
	else if (event.type!=sf::Event::Closed)
	{
		leve++;
		Game();
	}
}