#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <tuple>

using namespace std;

int main()
{
	int severity = 0;
	
	vector<tuple<int,int,bool>> scanners; // <range,pos,direction>
	
	int depth, range;
	string ignore;
	while(cin >> depth >> ignore >> range)
	{
		if(depth >= scanners.size())
		{
			scanners.resize(depth+1, {-1,-1,false});
		}
		scanners[depth] = {range,0,false};
		
		//int pos = range-1-abs((depth%(range*2+2))-(range-1));
		//cerr << depth << ignore << ' ' << range << endl;
		//if(pos == 0)
		//	severity += depth * range;*/
	}
	
	for(int i = 1; i < scanners.size(); ++i)
	{
		for(int j = i; j < scanners.size(); j++)
		{
			if(get<0>(scanners[j]) == -1) continue;
			int& pos = get<1>(scanners[j]);
			bool& dir = get<2>(scanners[j]);
			
			pos += dir ? -1 : 1;
			if(pos == 0 || pos == get<0>(scanners[j])-1)
				dir = !dir;
		}
	}
	
	int delay = 0;
	while(true)
	{
		auto it = find_if(begin(scanners),end(scanners), [](auto& tp)
			{
				return get<1>(tp) == 0;
			});
		if(it == end(scanners))
		{
			break;
		}
		cerr << delay << ": " << distance(begin(scanners),it) << endl;
		
		
		for(int i = 0; i < scanners.size(); i++)
		{
			if(get<0>(scanners[i]) == -1) continue;
			int& pos = get<1>(scanners[i]);
			bool& dir = get<2>(scanners[i]);
			
			pos += dir ? -1 : 1;
			if(pos == 0 || pos == get<0>(scanners[i])-1)
				dir = !dir;
		}
		
		++delay;
	}
	
	
	cout << delay << endl;
}