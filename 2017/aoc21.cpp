#include <iostream>
#include <vector>
#include <array>
#include <unordered_map>
#include <algorithm>
#include <numeric>

using namespace std;

size_t hash_pattern(const vector<bool>& arr) // accepts sz = 9 or 4
{
	if(arr.size() == 4) return accumulate(begin(arr), end(arr), 50);
	
	int corners = arr[0] + arr[2] + arr[6] + arr[8];
	int sides = arr[1] + arr[3] + arr[5] + arr[7];
	int center = arr[4];
	
	return corners + sides * 5 + center * 25;
	
}

struct fractal
{
	vector<vector<bool>> grid;	
};

void iter(fractal& f)
{
	
}

int main()
{
	unordered_map<size_t, string> patterns;
	int n = 0;
	while(!cin.eof())
	{
		string a;
		cin >> a;
		cin.ignore();
		
		vector<bool> test(a.size());
		transform(begin(a),end(a),begin(test), [](auto c) {return c == '#';});
		
		patterns[hash_pattern(test)] = move(a);
		++n;
		
	}
	
	cout << patterns.size() << ',' << n << endl;
	
}