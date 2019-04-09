#pragma once
#include<SFML/Graphics.hpp>
#ifndef Map_H


#define Map_H


class Map
{
public:
	void load()
	{
		texture.loadFromFile("Resources/Graphics/map.png");
		map.setTexture(texture);

	}
	void draw(sf::RenderWindow& window)
	{
		window.draw(map);
	}
private:
	sf::Texture texture;
	sf::Sprite map;

};







#endif 
