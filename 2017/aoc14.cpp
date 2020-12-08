#include <string>
#include <algorithm>
#include <vector>
#include <array>
#include <numeric>
#include <cstdint>
#include <bitset>
#include <iostream>
#include <sstream>
#include <iterator>
#include <iomanip>

using namespace std;

template<int Size = 256,int Count=64>
array<uint8_t,Size> sparse_hash(string key)
{	
	array<uint8_t,Size> sparse;
	iota(begin(sparse),end(sparse),0);
	
	int skip = 0, pos = 0;
	key += "\x11\x1f\x49\x2f\x17";
	for(int i = 0; i < Count; i++)
	{
		for(uint8_t c : key)
		{
			for(int i = pos, j = pos+c-1; i < j; i++, j--)
			{
				swap(sparse[i%Size], sparse[j%Size]);
			}
			pos = (pos + c + skip++) % Size;
		}
	}
	return sparse;
	
}

string knot_hash(string key)
{
	
	array<uint8_t,256> sparse = sparse_hash(move(key));
	
	ostringstream ss;
	ss << setfill('0');
	for(auto it = begin(sparse); it != end(sparse); advance(it,16))
	{
		ss << setw(2) << hex << accumulate(it, next(it,16), 0,bit_xor<uint8_t>());
	}
	
	return ss.str();
}

template<int Width, int Height=Width>
size_t getCoord(size_t x, size_t y)
{
	return x + y*Width;
}

const array<string, 16> hexToBin = {
	"\x00\x00\x00\x00"s,"\x00\x00\x00\x01"s,"\x00\x00\x01\x00"s,"\x00\x00\x01\x01"s,
	"\x00\x01\x00\x00"s,"\x00\x01\x00\x01"s,"\x00\x01\x01\x00"s,"\x00\x01\x01\x01"s,
	"\x01\x00\x00\x00"s,"\x01\x00\x00\x01"s,"\x01\x00\x01\x00"s,"\x01\x00\x01\x01"s,
	"\x01\x01\x00\x00"s,"\x01\x01\x00\x01"s,"\x01\x01\x01\x00"s,"\x01\x01\x01\x01"s,
};

template<int Width, int Height=Width>
int removeRegion(vector<bool>& grid, size_t x, size_t y)
{
	int count = 1;
	grid[getCoord<Width>(x,y)] = false;
	
	if((x+1) < Width && y < Height && grid[getCoord<Width>(x+1, y)])
		count += removeRegion<Width,Height>(grid, x+1, y);
		
	if(x < Width && (y+1) < Height && grid[getCoord<Width>(x, y+1)])
		count += removeRegion<Width,Height>(grid, x, y+1);
	
	if((x-1) < Width && y < Height && grid[getCoord<Width>(x-1, y)])
		count += removeRegion<Width,Height>(grid, x-1, y);
		
	if(x < Width && (y-1) < Height && grid[getCoord<Width>(x, y-1)])
		count += removeRegion<Width,Height>(grid, x, y-1);
	
	return count;
}

int main()
{
	string key = "hxtvlmkl";
	
	vector<bool> grid(128*128);
	
	auto it = begin(grid);
	
	ostringstream ss;
	for(int i = 0; i < 128; i++)
	{
		ss << key << '-' << i;
		auto hash = knot_hash(ss.str());
		ss.clear();ss.str("");
		for(uint8_t c : hash)
		{
			c -= '0';
			if(c > 9)
			{
				c -= 7;
				if(c > 15)
					c -= 32;
			}
			ss << hexToBin[c];
		}
		string s = ss.str();
		ss.clear();ss.str("");
		
		copy(begin(s),end(s),it);
		advance(it,128);
	};
	
	for(int i = 0; i < grid.size(); i++)
	{
		cerr << grid[i];
		if(i % 128 == 127)
			cerr << endl;
	}
	
	int count = 0;
	for(auto it = find(begin(grid),end(grid),true); it != end(grid); it = find(next(it,1),end(grid),true))
	{
		int idx = distance(begin(grid),it);
		int x = idx % 128, y = idx / 128;
		//cout << x << " , " << y << endl;
		cerr << count << ": " << removeRegion<128>(grid,x,y) << endl;
		count++;
	}
	
	cout << count << endl;
	
}