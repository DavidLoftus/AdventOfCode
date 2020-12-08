#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

struct component
{
	int a,b;
	
	bool used = false;
	
	int strength() const
	{
		return a + b;
	}
	
};

istream& operator>>(istream& is, component& obj)
{
	((is >> obj.a).ignore() >> obj.b).ignore();
}

bool operator==(component& obj, int x)
{
	return obj.a == x || obj.b == x;
}

pair<int,int> max_length(vector<component>& components, int type = 0) // returns <length,strength>
{	
	pair<int,int> max = {0,0};
	
	for(auto it = find(begin(components),end(components), type); it != end(components); it = find(next(it),end(components), type))
	{
		if(it->used) continue;
		
		it->used = true;
		
		auto p = max_length(components, (it->a == type) ? it->b : it->a);
		p.second += it->strength();
		p.first += 1;
		
		it->used = false;
		
		if((p.first > max.first) || (p.first == max.first && p.second > max.second))
			max = p;
		
	}
	return max;
	
}

int main()
{
	
	vector<component> components{istream_iterator<component>(cin),istream_iterator<component>()};
	
	cout << max_length(components).second << endl;
	
}