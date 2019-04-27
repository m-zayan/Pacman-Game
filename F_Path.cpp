#include<SFML/Graphics.hpp>
#include<queue>
#include<fstream>
#include <vector>
#include<utility>
#include"Blinky.h"
#include"Player.h"


struct point
{
	int x, y;
}parent[31][28];;
char map[31][28];
std::vector< std::pair<int, int> > visited;
std::queue<std::pair<int, int> > BFS;
bool visit[31][28];
void bfs(int x, int y, int Ghost_x, int Ghost_y, int Pacman_x, int Pacman_y, char map[31][28])
{
	std::pair<int, int> v;
	std::pair<int, int> p;
	BFS.push(std::make_pair(Ghost_x, Ghost_y));
	while (BFS.empty() == false)
	{
		v = BFS.front();
		if (v.first == Pacman_x && v.second == Pacman_y)//the point at which BFS has to be terminated Ghost find Pacman
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
		if (map[v.first - 1][v.second] != 'W'&&v.first >= 1 && visit[v.first - 1][v.second] == false)
		{
			parent[v.first - 1][v.second].x = v.first;
			parent[v.first - 1][v.second].y = v.second;
			BFS.push(std::make_pair(v.first - 1, v.second));
		}
		if (map[v.first][v.second - 1] != 'W'&&v.second >= 1 && visit[v.first][v.second - 1] == false)
		{
			parent[v.first][v.second - 1].x = v.first;
			parent[v.first][v.second - 1].y = v.second;
			BFS.push(std::make_pair(v.first, v.second - 1));
		}
		if (map[v.first][v.second + 1] != 'W'&&v.second + 1 <= y - 1 && visit[v.first][v.second + 1] == false)
		{
			parent[v.first][v.second + 1].x = v.first;
			parent[v.first][v.second + 1].y = v.second;
			BFS.push(std::make_pair(v.first, v.second + 1));
		}
		if (map[v.first + 1][v.second] != 'W'&&v.first + 1 <= x - 1 && visit[v.first + 1][v.second] == false)
		{
			parent[v.first + 1][v.second].x = v.first;
			parent[v.first + 1][v.second].y = v.second;
			BFS.push(std::make_pair(v.first + 1, v.second));
		}
	}
}
void FindPath(Player& Pacman,Blinky& blinky)
{
	int x = 31, y = 28, Ghost_x = (blinky.s_Blinky.getPosition().x + 54) / 30,
		Ghost_y = (blinky.s_Blinky.getPosition().y + 54) / 30,
		Pacman_x = Pacman.x / 30, Pacman_y = Pacman.y / 30;
	std::ifstream iFile("map.txt");

	for (int row = 0; row < 31; row++)
	{
		for (int col = 0; col < 28; col++)
		{
			iFile >> map[row][col];
		}
	}

	iFile.close();

	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			visit[i][j] = false;
			parent[i][j].x = -1;
			parent[i][j].y = -1;
		}
	}
	bfs(x, y, Ghost_x, Ghost_y, Pacman_x, Pacman_y, map);//perform BFS starting from Ghost_x,Ghost_y
	int count;//number of vertices explored during BFS are all visited nodes
	count = visited.size();
	//std::cout << count << std::endl;
	//for (int i = 0; i < visited.size(); i++)
		//std::cout << visited[i].first << " " << visited[i].second << std::endl;
	int d = 0;
	std::vector< std::pair<int, int> >path;//stores the reverse path ie from the destination to source
	std::pair <int, int> v;
	v = std::make_pair(Pacman_x, Pacman_y);
	while (parent[v.first][v.second].x != -1 && parent[v.first][v.second].y != -1)
	{
		std::pair <int, int> u;
		u = std::make_pair(parent[v.first][v.second].x, parent[v.first][v.second].y);
		path.push_back(u);
		d++;
		v = u;
	}
	//std::cout << d << std::endl;
	for (int i = path.size() - 1; i >= 0; i--)
		std::cout << path[i].first << " " << path[i].second << std::endl;
	std::cout << Pacman_x << " " << Pacman_y << std::endl;

}
