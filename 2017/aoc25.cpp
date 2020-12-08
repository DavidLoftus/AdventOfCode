#include <iostream>
#include <unordered_map>
#include <array>
#include <vector>
#include <algorithm>

using namespace std;

/*right 1 left 2
left 0 right 2
right 0 left 3
left 4 left 2
right 5 right 0
right 0 right 4*/
int main()
{
	
	vector<array<int,6>> states = {
		{1,-1,1,0,+1,2},
		{1,+1,0,1,-1,2},
		{1,-1,0,0,+1,3},
		{1,+1,4,1,+1,2},
		{1,-1,5,1,-1,0},
		{1,-1,0,1,-1,4},
	};
	
	unordered_map<int,bool> tape;
	
	int state = 0, cursor = 0;
	for(int i = 0; i < 12261543; i++)
	{
		auto& element = tape[cursor];
		auto& p = states[state];

		
		cursor += p[element*3+1];
		state = p[element*3+2];
		
		element = p[element*3];
	}
	
	cout << count_if(begin(tape),end(tape),[](auto& pair){return pair.second;});
	
}