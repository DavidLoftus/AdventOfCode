#include <iostream>
#include <algorithm>
#include <array>
#include <numeric>
#include <cstdint>
#include <vector>
#include <memory>

using namespace std;

class itransform
{
public:
	virtual ~itransform()
	{
		
	}
	virtual void apply(string& str) = 0;
};

class transform_move : public itransform
{
	array<uint8_t,16> indices;
	
	
public:

	auto begin()
	{
		return indices.begin();
	}
	
	auto end()
	{
		return indices.end();
	}
	
	uint8_t& operator[](size_t i)
	{
		return indices[i];
	}

	transform_move()
	{
		iota(begin(),end(),0);
	}
	
	void apply(string& str)
	{
		string s(16,'\0');
		for(int i = 0; i < 16; i++)
		{
			s[i] = str[indices[i]];
		}
		str = move(s);
	}
};

class transform_swapi : public itransform
{
	
public:
	int i,j;
	transform_swapi(int x, int y) : i(x),j(y)
	{
	}
	
	void apply(string& str)
	{
		swap(str[i],str[j]);
	}
	
};

class transform_swapc : public itransform
{
	char A,B;
	
	public:
	transform_swapc(char a, char b) : A(a),B(b)
	{
	}
	
	void apply(string& str)
	{
		auto i = find(begin(str),end(str),A), j = find(begin(str),end(str),B);
		swap(*i,*j);
	}
};

template<typename Derived, typename Base, typename Del>
std::unique_ptr<Derived, Del> 
static_unique_ptr_cast( std::unique_ptr<Base, Del>&& p )
{
    auto d = static_cast<Derived *>(p.release());
    return std::unique_ptr<Derived, Del>(d, std::move(p.get_deleter()));
}

int main()
{
	
	vector<int> order(16);
	iota(begin(order),end(order),0);
	
	vector<unique_ptr<itransform>> transforms;
	
	while(!cin.eof())
	{
		char c;
		cin >> c;
		
		switch(c)
		{
		case 's':
		{
			int X;
			cin >> X;
			
			if(!dynamic_cast<transform_move*>(transforms.back().get()))
			{
				auto trmove = new transform_move;
				auto it = rbegin(transforms);
				for(;it != rend(transforms) && dynamic_cast<transform_swapi*>(it->get());advance(it,1))
				{
				}
				for(auto it2 = it.base(); it2 != end(transforms); advance(it2,1))
				{
					auto& swp = dynamic_cast<transform_swapi&>(*it2->get());
					swap((*trmove)[swp.i],(*trmove)[swp.j]);
				}
				
				transforms.erase(it.base(),end(transforms));
				transforms.emplace_back(trmove);
				
			}
			
			auto& back = dynamic_cast<transform_move&>(*transforms.back().get());
			
			rotate(back.begin(),prev(back.end(),X),back.end());
			
			break;
		}	
		case 'x':
		{
			int X,Y;
			(cin >> X).ignore() >> Y;
			
			swap(order[X],order[Y]);
			
			if(!transforms.empty() && dynamic_cast<transform_move*>(transforms.back().get()))
			{
				auto& mv = dynamic_cast<transform_move&>(*transforms.back().get());
				swap(mv[X],mv[Y]);
			}
			else
			{
				transforms.emplace_back(new transform_swapi(X,Y));
			}
			
			break;
		}
		case 'p':
		{
			char A,B;
			(cin >> A).ignore() >> B;
			
			transforms.emplace_back(new transform_swapc(A,B));
			
			break;
		}
		default:
			cerr << "Unknown char " << c << endl;
			return -1;
		}
		cin.ignore();
		
	}
	
	string s = "abcdefghijklmnop", s2 = s;
	
	while(s != s2)
	{
		for(auto& t : transforms)
		{
			t->apply(s);
			t->apply(s2);
		}
		for(auto& t : transforms)
		{
			t->apply(s2);
		}
	}
	
	s = "abcdefghijklmnop";
	int mu = 0;
	while(s != s2)
	{
		for(auto& t : transforms)
		{
			t->apply(s);
			t->apply(s2);
		}
		++mu;
	}
	for(auto& t : transforms)
	{
		t->apply(s2);
	}
	int lam = 1;
	while(s != s2)
	{
		for(auto& t : transforms)
		{
			t->apply(s2);
		}
		++lam;
	}
	

	cout << lam + mu << endl;
	
	s="abcdefghijklmnop";
	
	for(int i = 0; i < ((1000000000 % lam)+mu); i++)
	{
		for(auto& t : transforms)
		{
			t->apply(s);
		}
	}
	
	cout << s << endl;
	
}