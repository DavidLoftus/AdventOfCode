#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <sstream>
#include <numeric>
#include <iomanip>

using namespace std;

vector<vector<int>> nodes;
vector<bool> connected;

void findConnected(int node)
{
	if(connected[node]) return;
	//cerr << node << endl;
	connected[node] = true;
	for_each(begin(nodes[node]),end(nodes[node]),findConnected);
}

int main()
{
	while(!cin.eof())
	{
		int i;
		cin >> i; cin.ignore();
		
		string s;
		getline(cin, s);
		
		istringstream ss(s);
		nodes.emplace_back();
		copy(istream_iterator<int>(ss), istream_iterator<int>(), back_inserter(nodes.back()));
		
		
	}
	connected.resize(nodes.size(),false);
	int count = 0;
	for(auto it = find(begin(connected),end(connected),false); 
		it != end(connected); 
		it = find(next(it),end(connected),false))
	{
		++count;
		findConnected(distance(begin(connected),it));
	}
	cout << count << endl;
	
}