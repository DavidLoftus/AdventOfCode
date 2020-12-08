#include <iostream>
#include <string>
#include <array>
#include <algorithm>
#include <vector>
#include <cctype>

using namespace std;

int main()
{
	
	array<array<char,201>,201> grid;
	
	auto it = begin(grid);
	
	while(!cin.eof())
	{
		
		string s;
		getline(cin,s);// cin.ignore();
		
		copy(begin(s),end(s),begin(*it++));
		
	}
	
	
	auto first = find(begin(grid[0]),end(grid[0]), '|');
	
	int x = distance(begin(grid[0]),first), y=0;
	
	int dir = 1; // UP,DOWN,LEFT,RIGHT
	
	string markers;
	bool flag = true;
	int count = 0;
	while(flag)
	{
		//cerr << x << ", " << y << endl;
		if(x > 201 || x < 0 || y > 201 || y < 0)
		{
			cout << "OOps" << count << endl << x << "," << y << endl;
			exit(0);
		}
		
		if(isalpha(grid[y][x]))
		{
			markers += grid[y][x];
		}
		
		switch(grid[y][x])
		{
			
		case ' ':
			flag = false;
			break;
			
		case '+':
			if((dir & 2) == 0)
			{
				dir = (grid[y][x+1] == '-') ? 3 : 2;
			}
			else
			{
				dir = (grid[y+1][x] == '|') ? 1 : 0;
			}
			
		default:
			if((dir & 2) == 0)
				y += (dir & 1) * 2 - 1;
			else
				x += (dir & 1) * 2 - 1;
			break;
		}
		
		count++;
		
	}
	
	cout << "Markers: \"" << markers << '"' << endl << "Count: " << count << endl << "X: " << x << ", Y: " << y << " => \'" << grid[y][x] << '\'' << endl;
	
	cout << "Row: \""; 
	//for(auto c : grid[y])
	//	cout << c;
	cout << "\"" << endl;
	
}