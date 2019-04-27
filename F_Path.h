#pragma once
//#Mohamed Zayan (:
#include<SFML/Graphics.hpp>
#include<queue>
#include<fstream>
#include <vector>
#include<utility>
#include"Blinky.h"
#include"Player.h"

#ifndef F_Path_H


#define F_Path_H

void bfs(int x, int y, int Ghost_x, int Ghost_y, int Pacman_x, int Pacman_y, char map[31][28]);
void FindPath(Player& Pacman, Blinky& blinky);

#endif // !Path_H
