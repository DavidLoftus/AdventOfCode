#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <memory>

using namespace std;

struct test_t
{
	int i;
};

struct pair_hash
{
	template<typename T1, typename T2, class Hash1 = hash<T1>, class Hash2 = hash<T2>>
	size_t operator()(const pair<T1,T2>& p) const
	{
		size_t seed = Hash1()(p.first);
		seed ^= Hash2()(p.second) + 0x9e3779b9 + (seed<<6) + (seed>>2);
		return seed;
	}
};

int main()
{
	
	unordered_map<pair<int,int>,int,pair_hash> grid;
	
	int j = 12;
	while(!cin.eof())
	{
		string s;
		getline(cin,s);
		transform(s.begin(), s.end(),inserter(grid,end(grid)), [j,x = -12](char c) mutable
		{
			cout << x << ',' << j << '=' << c << endl;
			return make_pair(make_pair(x++,j),(c == '#') ? 2 : 0);
		});
		cout << "---------" << endl;
		--j;
	}
	
	int x = 0, y = 0;
	int dirX = 0, dirY = 1;
	
	int count = 0;
	
	for(int i = 0; i < 10000000; i++)
	{
		switch(grid[{x,y}])
		{
		case 0:
			if(dirY == 0)
			{
				dirY = dirX;
				dirX = 0;
			}
			else
			{
				dirX = -dirY;
				dirY = 0;
			}
			break;
		case 1:
			++count;
			break;
			
		case 2:
			if(dirY == 0)
			{
				dirY = -dirX;
				dirX = 0;
			}
			else
			{
				dirX = dirY;
				dirY = 0;
			}
			break;
		case 3:
			dirX = -dirX;
			dirY = -dirY;
			break;
		}
		
		grid[{x,y}] = (grid[{x,y}]+1) % 4;
		
		x += dirX;
		y += dirY;
		//cerr << x << ',' << y << endl;
	}
	
	cout << count << endl;
	
}