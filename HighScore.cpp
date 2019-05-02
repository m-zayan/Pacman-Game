#include<SFML/Graphics.hpp>
#include "HighScore.h"
#include"Animation.h"

void HighScore()
{
	sf::RenderWindow window(sf::VideoMode(960, 960), "Pacman");
	window.setPosition(sf::Vector2i(480, 0));
	sf::Font font;
	sf::Text high;
	font.loadFromFile("Resources/Font/high.ttf");
	high.setFillColor(sf::Color::Yellow);
	high.setPosition(120, 20);
	high.setString("Game Leader ");
	high.setCharacterSize(120);
	high.setFont(font);
	std::ifstream readFile;
	int Scoref;
	std::ifstream readFile2;
	std::string Name;
	std::ostringstream Nn;
	sf::Font font2;
	sf::Text high2;
	font2.loadFromFile("Resources/Font/Name.ttf");
	high2.setCharacterSize(50);
	high2.setFont(font2);
	high2.setFillColor(sf::Color::Green);
	high2.setPosition(100, 300);
	readFile2.open("Resources/HighScore/Name.txt");



	readFile.open("Resources/HighScore/HighScore.txt");

	if (readFile.is_open())
	{
		while (!readFile.eof())
		{
			readFile >> Scoref;

		}
	}
	readFile.close();
	if (readFile2.is_open())
	{
		while (readFile2 >> Name)
		{
			Nn << "Leader : " << Name << std::endl<< "Score :" << Scoref;
		}
	}
	readFile2.close();

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
		
		high2.setString(Nn.str());
		window.clear();
		window.draw(high2);
		window.draw(high);
		window.display();
	
	
	}

}