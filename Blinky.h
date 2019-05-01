#pragma once

#include<SFML/Graphics.hpp>
#include"Animation.h"
#include<sstream>
#include"Map.h"
#include<queue>
#include<fstream>
#include <vector>
#include<utility>
#ifndef Blinky_H

#define Blinky_H

class Blinky
{
public:

	Blinky() = default;
	sf::Sprite s_Blinky;
	enum MOVE { UP, DOWN, LEFT, RIGHT }; //enums instead of remember numbers
	bool move[4] = { false,false, false, false }; //deciding if You move up/down/left/right
	bool walking = false;
	float nextspot; //the next tilespot of the map
	float x = 420;
	float y = 330;
	float movespeed = 3;
	char map[31][28];	

	struct point
	{
		int x, y;
	}
	parent[31][28];
	bool visit[31][28]; //For Visited Nodes.

	void bfs(int x, int y, int Ghost_row, int Ghost_col, int Pacman_row, int Pacman_col, char map[31][28])
	{
		std::vector< std::pair<int, int> > visited;
		std::queue< std::pair<int, int> > BFS;
		std::pair<int, int> v;
		std::pair<int, int> p;
		BFS.push(std::make_pair(Ghost_row, Ghost_col));
		while (BFS.empty() == false)
		{
			v = BFS.front();
			if (v.first == Pacman_row && v.second == Pacman_col)//the point at which BFS has to be terminated Ghost find Pacman
			{
				visit[v.first][v.second] = true;
				visited.push_back(v);
				BFS.pop();
				return;
			}
			if (visit[v.first][v.second] == true)//if a queue has visited vertex.pop it out.
			{
				BFS.pop();
				continue;
			}
			visit[v.first][v.second] = true;
			visited.push_back(v);
			//now check for neighbours
			if (map[v.first - 1][v.second] != 'W' /*&& map[v.first-1][v.second]!='g'*/&&v.first >= 1 && visit[v.first - 1][v.second] == false)
			{
				parent[v.first - 1][v.second].x = v.first;
				parent[v.first - 1][v.second].y = v.second;
				BFS.push(std::make_pair(v.first - 1, v.second));
			}
			if (map[v.first][v.second - 1] != 'W' /*&& map[v.first-1][v.second]!='g'*/&&v.second >= 1 && visit[v.first][v.second - 1] == false)
			{
				parent[v.first][v.second - 1].x = v.first;
				parent[v.first][v.second - 1].y = v.second;
				BFS.push(std::make_pair(v.first, v.second - 1));
			}
			if (map[v.first][v.second + 1] != 'W'/*&& map[v.first-1][v.second]!='g'*/&&v.second + 1 <= y - 1 && visit[v.first][v.second + 1] == false)
			{
				parent[v.first][v.second + 1].x = v.first;
				parent[v.first][v.second + 1].y = v.second;
				BFS.push(std::make_pair(v.first, v.second + 1));
			}
			if (map[v.first + 1][v.second] != 'W' /*&& map[v.first-1][v.second]!='g'*/ && v.first + 1 <= x - 1 && visit[v.first + 1][v.second] == false)
			{
				parent[v.first + 1][v.second].x = v.first;
				parent[v.first + 1][v.second].y = v.second;
				BFS.push(std::make_pair(v.first + 1, v.second));
			}
		}
	}

	sf::Vector2f FindPath(sf::Vector2f Pacman, sf::Sprite& s_Blinky)

	{

		std::ifstream iFile("Resources/Map/map.txt");

		for (int row = 0; row < 31; row++)
		{
			for (int col = 0; col < 28; col++)
			{
				iFile >> map[row][col];
			}
		}

		iFile.close();


		int x = 31, y = 28, Ghost_row = int(s_Blinky.getPosition().y / 30)
			, Ghost_col = int((s_Blinky.getPosition().x ) / 30),
			Pacman_row = (int)Pacman.y / 30, Pacman_col = (int)Pacman.x / 30;

		//cin >> Ghost_row >> Ghost_col;//Ghost coordinates
		//cin >> Pacman_row >> Pacman_col;//Pacman coordinates


		for (int i = 0; i < x; i++)
		{
			for (int j = 0; j < y; j++)
			{
				visit[i][j] = false;
				parent[i][j].x = -1;
				parent[i][j].y = -1;
			}
		}
		bfs(x, y, Ghost_row, Ghost_col, Pacman_row, Pacman_col, map);//perform BFS starting from Ghost_row,Ghost_col
		//int count;//number of vertices explored during BFS are all visited nodes
	   // count=visited.size();
	   // cout<<count<<endl;
	  //  for(int i=0; i<visited.size(); i++)
		   // cout<<visited[i].first<<" "<<visited[i].second<<endl;
	   // int d=0;
		std::vector<std::pair<int, int> >path;//stores the reverse path ie from the destination to source
		std::pair <int, int> v;
		v = std::make_pair(Pacman_row, Pacman_col);
		while (parent[v.first][v.second].x != -1 && parent[v.first][v.second].y != -1)
		{
			std::pair <int, int> u;
			u = std::make_pair(parent[v.first][v.second].x, parent[v.first][v.second].y);
			path.push_back(u);
			// d++;
			v = u;
		}
		//cout<<d<<endl;
		int cnt = path.size() - 1;

		//for (int i = cnt; i > 0; i--)
		//{
			//std::cout << path[i].second << " " << path[i].first << std::endl;
		//}
		sf::Vector2f dir = {0,0};
		//std::cout<<path[cnt].second- path[cnt-1].second <<" " << path[cnt-1].first-path[cnt].first<<std::endl;
		if (cnt > 0)
		{
			dir.x = (float)path[cnt-1].second- path[cnt].second;
			dir.y = (float)path[cnt-1].first- path[cnt].first;
		}
			return dir;
		

	}
	enum class AnimationIndex
	{
		downStanding,
		upDirection,
		downDirection,
		rightDirection,
		leftDirection,
		frightened,
		back,
		Count
	};
	Blinky(const sf::Vector2f& position)
	{
		s_Blinky.setTextureRect({ 0,0,32,32 });
		s_Blinky.setPosition(position);
		animations[int(AnimationIndex::downStanding)] = Animation(64, 0, 32, 32, 1, 10.4f, path);
		animations[int(AnimationIndex::upDirection)] = Animation(0, 0, 32, 32, 2, 0.4f, path);
		animations[int(AnimationIndex::downDirection)] = Animation(64, 0, 32, 32, 2, 0.4f, path);
		animations[int(AnimationIndex::leftDirection)] = Animation(128, 0, 32, 32, 2, 0.4f, path);
		animations[int(AnimationIndex::rightDirection)] = Animation(192, 0, 32, 32, 2, 0.4f, path);
		animations[int(AnimationIndex::frightened)] = Animation(0, 128,32, 32, 2, 0.4f, path);
		animations[int(AnimationIndex::back)] = Animation(0, 128, 32, 32, 3, 0.4f, path);

	}
	void Draw(sf::RenderWindow& window) const
	{
		window.draw(s_Blinky);


	}
	void dirmove(sf::Vector2f dir)
	{
		if (dir.y == -1)  //Up =1 , DOWN =2 ,Left=3 ,Right=4.
		{
			if (walking == false)
			{

				nextspot = y - 30;

				move[UP] = true;
				walking = true;

			}
		}

		if (dir.y == 1)
		{
			if (walking == false)
			{
				nextspot = y + 30;
				move[DOWN] = true;
				walking = true;
			}
		}

		if (dir.x == -1)
		{
			if (walking == false)
			{
				nextspot = x - 30;
				move[LEFT] = true;
				walking = true;
			}
		}

		if (dir.x == 1)
		{
			if (walking == false)
			{
				nextspot = x + 30;
				move[RIGHT] = true;
				walking = true;
			}

		}
	}
	void moving()
	{
		if (walking == true)
		{
			if (move[UP] == true)
			{
				y -= movespeed;


				if (y <= nextspot)
				{
					y = nextspot;
					walking = false;
					move[UP] = false;
				}
			}

			if (move[DOWN] == true)
			{
				y += movespeed;
				if (y >= nextspot)
				{
					y = nextspot;
					walking = false;
					move[DOWN] = false;
				}
			}
			if (move[LEFT] == true)
			{
				x -= movespeed;
				if (x <= nextspot)
				{
					x = nextspot;
					walking = false;
					move[LEFT] = false;
				}
			}
			if (move[RIGHT] == true)
			{
				x += movespeed;
				if (x >= nextspot)
				{
					x = nextspot;
					walking = false;
					move[RIGHT] = false;
				}
			}
		}
	}
	void Update(float deltaTime , sf::Vector2f Pacman,sf::Sprite& blinky)
	{
		prevP = Gpos;
		animations[int(currentAnimation)].Update(deltaTime);
		animations[int(currentAnimation)].ApplyToSprite(s_Blinky);
		Gpos = FindPath(Pacman, blinky);
		if (Gpos.x > 0 && node.superDot_eaten==false)
		{
			currentAnimation = AnimationIndex::rightDirection;
		}
		else if(Gpos.x<0 && node.superDot_eaten == false)
		{
			currentAnimation = AnimationIndex::leftDirection;
		}
		else if (Gpos.y < 0 && node.superDot_eaten == false)
		{
			currentAnimation = AnimationIndex::upDirection;
		}
		else if (Gpos.y > 0 && node.superDot_eaten == false)
		{
			currentAnimation = AnimationIndex::downDirection;
		}

		int Grow = int(y / 30);
		int Gcol = int(x / 30);
	
		//These conditions prevent ghosts Backtracking.
		if (Gpos.x==0 && prevP.y != 0 && node.wall[Grow - 1][Gcol] != 1 && node.wall[Grow + 1][Gcol] != 1 && Gpos.y == (prevP.y*-1)) 
		{
			Gpos.y *= -1;
			if (currentAnimation == AnimationIndex::upDirection)
			{
				currentAnimation = AnimationIndex::downDirection;
			}
			else
			{
				currentAnimation = AnimationIndex::upDirection;
			}
			
		}
		if (Gpos.y == 0 && prevP.x != 0 && node.wall[Grow][Gcol - 1] != 1 && node.wall[Grow ][Gcol+ 1] != 1 && Gpos.x == (prevP.x*-1))
		{
			Gpos.x *= -1;
			if (currentAnimation == AnimationIndex::rightDirection)
			{
				currentAnimation = AnimationIndex::leftDirection;
			}
			else
			{
				currentAnimation = AnimationIndex::rightDirection;
			}
		}
		dirmove(Gpos);
		moving();
		blinky.setPosition(x, y);

	}
	void Update2(float deltaTime)
	{
		s_Blinky.setPosition(405, 330);
		currentAnimation = AnimationIndex::downDirection;
		animations[int(currentAnimation)].Update(deltaTime);
		animations[int(currentAnimation)].ApplyToSprite(s_Blinky);
	
	}
	void Frightened_Mode(bool superDot_eaten  , sf::Time time)
	{
		if (superDot_eaten == true && time.asSeconds()<8)
		{
			currentAnimation = AnimationIndex::frightened;
		}
		else
		{
			currentAnimation = AnimationIndex::back;
		}
	}
private:
	
	Animation animations[int(AnimationIndex::Count)];
	AnimationIndex currentAnimation = AnimationIndex::downStanding;
	std::string path = "Resources/Graphics/Ghost.png";
	sf::Vector2f Gpos;
	sf::Vector2f prevP = {};
	Map node;

};



#endif