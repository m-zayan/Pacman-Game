#pragma once
#include<SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include"Player.h"
#include "Animation.h"

#ifndef Game_H

#define Game_H

class GameS
{
public:
	sf::SoundBuffer SoundBuffer_Menu_Selection;
	sf::Sound Menu_Selection_Sound;
	enum Sound{ START, Eating, Death, MouseClick};
	bool die[3] = {};
	GameS()
	{
		texture.loadFromFile("Resources/Graphics/lives .png");
		texture.setSmooth(true);
		lives.setTexture(texture);
		lives.setScale(1.0f, 0.9f);
		lives.setTextureRect({ 0,0,40,37 });
		texture2.loadFromFile("Resources/Graphics/GameOver.jpg");
		texture2.setSmooth(true);
		gameOver.setTexture(texture2);

		/////////////Sound////////////////////////////////////////////////////
		SoundBuffer_Start.loadFromFile("Resources/Sound/pacman_beginning.wav");
		Start_Sound.setBuffer(SoundBuffer_Start);
		//Start_Sound.setVolume(50.f);
		//Start_Sound.setPlayingOffset(sf::seconds(0.1f));
		Soundbuffer_eating.loadFromFile("Resources/Sound/pacman_chomp.wav");
		Sound_eating.setVolume(50.f);
		Sound_eating.setPlayingOffset(sf::seconds(2.f));
		Sound_eating.setBuffer(Soundbuffer_eating);
		Soundbuffer_death.loadFromFile("Resources/Sound/pacman_death.wav");
		Sound_death.setBuffer(Soundbuffer_death);
		SoundBuffer_MouseClick.loadFromFile("Resources/Sound/mouseclick.wav");
		MouseClick_Sound.setBuffer(SoundBuffer_MouseClick);
		SoundBuffer_Menu_Selection.loadFromFile("Resources/Sound/Menu Selection Click.wav");
		Menu_Selection_Sound.setBuffer(SoundBuffer_Menu_Selection);
	}
	void Draw(sf::RenderWindow& window)
	{
		for (int i = 0; i < 3; i++)
		{

			lives.setPosition(float(600 + (i * 40)), 940.0f);
			if (die[i] == false)
			{
				window.draw(lives);
			}
		}
	}
	void Play_Sound(int state)
	{
		if (state == START)
		{
			Start_Sound.play();
		}
		if (state == Eating)
		{
			Sound_eating.play();
		}
		if (state == Death)
		{
			Sound_death.play();
		}
		if (state == MouseClick)
		{
			MouseClick_Sound.play();
		}
		
	}
	void GameOver(sf::RenderWindow& window)
	{
		window.draw(gameOver);
	}
private:
	sf::Texture texture;
	sf::Sprite lives;
	sf::Texture texture2;
	sf::Sprite gameOver;
	sf::SoundBuffer SoundBuffer_MouseClick;
	sf::Sound MouseClick_Sound;

	sf::SoundBuffer SoundBuffer_Start;
	sf::Sound Start_Sound;
	sf::SoundBuffer Soundbuffer_eating;
	sf::Sound Sound_eating;
	sf::SoundBuffer Soundbuffer_death;
	sf::Sound Sound_death;

};
void Game();

#endif // !Game_H