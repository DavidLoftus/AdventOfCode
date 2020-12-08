#include <iostream>
#include <array>
#include <valarray>
#include <list>
#include <iterator>
#include <algorithm>
#include <functional>
#include <limits>

using namespace std;

struct particle
{
	
	int collision_time = numeric_limits<int>::max(); // max
	
	valarray<double> pos{3}, vel{3}, acc{3};

	/*bool collides_with(const particle& other, int& time) const
	{
		valarray<double> a = (acc - other.acc)/2.0,
			 b = (2.0*vel-acc-2.0*other.vel+other.acc)/2.0,
			 c = pos-vel-other.pos+other.vel;
		
		valarray<double> x = b*b+4.0*a*c;
			
		if((x < 0.0).sum() != 0) // If any are less than 0 return false
			return false;
			
		x = x.apply(sqrt);
		if((x != x.apply(floor)).sum() != 0)
			return false;
		
		valarray<double> t1 = (-b + x)/(2.0*a),
			 t2 = (-b - x)/(2.0*a);
			
		bool b1 = (t1 <= 0.0 || t1 != t1.apply(floor)).sum() == 0,
			 b2 = (t2 <= 0.0 || t2 != t2.apply(floor)).sum() == 0;
		
		if(b1)
		{
			if(b2)
			{
				
			}
		}
		else if(b2)
		{
			
		}
	}*/
	
	void tick()
	{
		vel += acc;
		pos += vel;
	}
	
	int dist() const
	{
		return abs(pos).sum();
	}
	
	int acc_mag() const
	{
		return abs(acc).sum();
	}
	
	friend istream& operator>>(istream& ss, particle& p)
	{
		ss >> p.pos[0] >> p.pos[1] >> p.pos[2];
		ss >> p.vel[0] >> p.vel[1] >> p.vel[2];
		ss >> p.acc[0] >> p.acc[1] >> p.acc[2];
		//ss.ignore();
		
		return ss;
	}
	
	friend bool operator<(const particle& a, const particle& b)
	{
		return a.dist() < b.dist();
	}
	
	friend bool operator==(const particle& a, const particle& b)
	{
		return (a.pos != b.pos).sum() == 0;
	}
	
};

int main()
{
	
	list<particle> particles{istream_iterator<particle>(cin), istream_iterator<particle>()};
	
	//vector<particle> remaining;
	for(int i = 0; i < 1000; i++)
	{
		//cout << i << endl;
		for(auto it = begin(particles); next(it) != end(particles);)
		{
			bool collision = false;
			for(auto it2 = next(it); it2 != end(particles);)
			{
				if(*it == *it2)
				{
					
					cout << distance()
					
					it2 = particles.erase(it2);
					collision = true;
				}
				else
					++it2;
			}
			
			if(collision)
				it = particles.erase(it);
			else
				++it;
			
		}
		for_each(begin(particles),end(particles), mem_fun_ref(&particle::tick));
	}
	cout << count_if(begin(particles),end(particles), [](const particle& p)
	{
		return p.collision_time == numeric_limits<int>::max();
	}) << endl;
	
}