#pragma once
#include<SFML/Graphics.hpp>

using namespace sf;

#ifndef Tile_H
#define	Tile_H

//-------------------------------------------------------------------//
class Tile {
public:

	bool wall = false;
	bool dot = false;
	bool big_dot = false;
	bool eaten = false;
	Vector2f pos;

	Tile() {}//default constructor

//-------------------------------------------------------------------//
	Tile(float x, float y)//constructor
	{
		pos = Vector2f(x, y);
	}
	//-------------------------------------------------------------------//
	void show(RenderWindow& window)//for drawnig dots, if a dot exists on this tile and it's not eaten
	{
		if (dot)
		{
			if (!eaten)
			{
				CircleShape dot(3);
				dot.setPosition(pos.x, pos.y);
				dot.setFillColor(Color::Yellow);
				window.draw(dot);
			}
		}
		else if (big_dot)
		{
			if (!eaten)
			{
				CircleShape big_dot(6);
				big_dot.setPosition(pos.x, pos.y);
				big_dot.setFillColor(Color::Yellow);
				window.draw(big_dot);
			}
		}
	}





};
#endif





