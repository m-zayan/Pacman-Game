#pragma once
#include<SFML/Graphics.hpp>
#include<fstream>
#include<vector>
#ifndef  HighScore_H

#define HighScore_H

class Score
{
public:

	void Read()
	{
		readFile.open("Resources/HighScore/HighScore.txt");
		if (readFile.is_open())
		{
			while (!readFile.eof())
			{
				readFile >> toVector;
				newS.push_back(toVector);
			}
		}
		readFile.close();
	}
	void Out()
	{
		std::ofstream writeFile("Resources/HighScore/HighScore.txt");
		if (writeFile.is_open())
		{
			
		}
	}

private:
	std::ifstream readFile;
	std::vector<int>newS;
	int toVector;
};

void HighScore();



#endif // ! HighScore_H



