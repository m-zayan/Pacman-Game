#include<SFML/Graphics.hpp>
#include<iostream>
#include<Windows.h>
#include "Tile.h"

using namespace sf;
//-------------------------------------------------------------------//


int main() {

	RenderWindow window(VideoMode(896, 992), "Pacman");
	window.setPosition(sf::Vector2i(480, 0));
	enum MOVE { UP, DOWN, LEFT, RIGHT };
	bool move[4];
	bool walking=false;
	for (int i = 0; i < 4; ++i) //initialize the all move booleans to false
		move[i] = false;
	int collision = 0;
	window.setKeyRepeatEnabled(false);
	window.setVerticalSyncEnabled(true);
	CircleShape pacman(20);
	pacman.setFillColor(Color::Yellow);


	Texture texture;
	texture.loadFromFile("resized_map.png");
	Sprite s_map(texture);


	int row, column;
	//-------------------------------------------------------------------//

	Tile tiles[31][28]; //[y][x] y first then x
	int tilesRepresent[31][28] =
	{
	  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	  {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
	  {1, 8, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 8, 1},
	  {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
	  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	  {1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1},
	  {1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1},
	  {1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
	  {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 6, 1, 1, 6, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
	  {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 6, 1, 1, 6, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
	  {1, 1, 1, 1, 1, 1, 0, 1, 1, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 1, 1, 0, 1, 1, 1, 1, 1, 1},
	  {1, 1, 1, 1, 1, 1, 0, 1, 1, 6, 1, 1, 1, 1, 1, 1, 1, 1, 6, 1, 1, 0, 1, 1, 1, 1, 1, 1},
	  {1, 1, 1, 1, 1, 1, 0, 1, 1, 6, 1, 1, 1, 1, 1, 1, 1, 1, 6, 1, 1, 0, 1, 1, 1, 1, 1, 1},
	  {1, 1, 1, 1, 1, 1, 0, 6, 6, 6, 1, 1, 1, 1, 1, 1, 1, 1, 6, 6, 6, 0, 1, 1, 1, 1, 1, 1},
	  {1, 1, 1, 1, 1, 1, 0, 1, 1, 6, 1, 1, 1, 1, 1, 1, 1, 1, 6, 1, 1, 0, 1, 1, 1, 1, 1, 1},
	  {1, 1, 1, 1, 1, 1, 0, 1, 1, 6, 1, 1, 1, 1, 1, 1, 1, 1, 6, 1, 1, 0, 1, 1, 1, 1, 1, 1},
	  {1, 1, 1, 1, 1, 1, 0, 1, 1, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 1, 1, 0, 1, 1, 1, 1, 1, 1},
	  {1, 1, 1, 1, 1, 1, 0, 1, 1, 6, 1, 1, 1, 1, 1, 1, 1, 1, 6, 1, 1, 0, 1, 1, 1, 1, 1, 1},
	  {1, 1, 1, 1, 1, 1, 0, 1, 1, 6, 1, 1, 1, 1, 1, 1, 1, 1, 6, 1, 1, 0, 1, 1, 1, 1, 1, 1},
	  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	  {1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
	  {1, 8, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 8, 1},
	  {1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1},
	  {1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1},
	  {1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1},
	  {1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
	  {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
	  {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
	  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};

	for (int i = 0; i < 28; i++)
	{
		for (int j = 0; j < 31; j++)
		{
			tiles[j][i] = Tile(32 * i + 12, 32 * j + 12);
			switch (tilesRepresent[j][i])
			{
			case 1: // 1 is wall
				tiles[j][i].wall = true;
				break;
			case 0: // 2 is a dot
				tiles[j][i].dot = true;
				break;
			case 8: // 8 is a big_dot
				tiles[j][i].big_dot = true;
				break;
			case 6: // 6 is blank space
				tiles[j][i].eaten = true;
				break;
			case 5: // pacaman's starting position
				row = j;
				column = i;
				break;
			}
		}
	}


	//-------------------------------------------------------------------//

		// start game loop.
	while (window.isOpen())
	{
		//-------------------------------------------------------------------//

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (Keyboard::isKeyPressed(Keyboard::Escape))
				window.close();


		}
		//-------------------------------------------------------------------//



		switch (event.key.code)
		{
		case Keyboard::Up:
			if (walking == false)
			{
				if (row > 0 && tilesRepresent[row - 1][column] != 1)
				{
					row -= 1;
					//move[UP] = true;
					walking = true;
				}
				else
				{
					collision = 1;
				}
			}
			break;
		case Keyboard::Down:
			if (walking == false)
			{
				if (row < 31 && tilesRepresent[row + 1][column] != 1)
				{
					row += 1;
					//move[DOWN] = true;
					walking = true;
				}
				else
				{
					collision = 2;
				}
			}
			break;
		case Keyboard::Right:
			if (walking == false)
			{
				if (column < 28 && tilesRepresent[row][column + 1] != 1)
				{
					column += 1;
					//move[RIGHT] = true;
					walking = true;
				}
				else
				{
					collision = 3;
				}
			}
			break;
		case Keyboard::Left:
			if (walking == false)
			{
				if (column > 0 && tilesRepresent[row][column - 1] != 1)
				{
					column -= 1;
					//move[LEFT] = true;
					walking = true;
				}
				else
				{
					collision = 4;
				}
			}
			break;
		}

		//--------------------------------------------------------------------//
		std::cout << tiles[row][column].pos.x - 13<<" "<< tiles[row][column].pos.y - 12 << std::endl;
		window.clear();
		window.draw(s_map); pacman.setPosition((tiles[row][column].pos.x-13), (tiles[row][column].pos.y-12));
		if (walking == true)
		{
			Sleep(150);
			walking = false;
		}
		else  //Move if there is collision
		{
			if (collision == 1)
			{
				
			}
		}
		for (int i = 0; i < 28; i++)
		{
			for (int j = 0; j < 31; j++)
			{
				tiles[j][i].show(window);
			}
		}

		window.draw(pacman);
		window.display();
		//--------------------------------------------------------------------//end gameloop

	}


	return EXIT_SUCCESS;
}