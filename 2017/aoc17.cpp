#include <list>
#include <iostream>
#include <iterator>
#include <chrono>

using namespace std;
using namespace std::chrono;

template <typename iter_t, typename T = typename std::iterator_traits<iter_t>::value_type>
struct circular_iterator_t : public iterator<forward_iterator_tag,T>
{	

	//using T = typename std::iterator_traits<iter_t>::value_type;
	using this_t = circular_iterator_t<iter_t,T>;

	iter_t first, last, pos;
	
	circular_iterator_t() = default;
	
	circular_iterator_t(iter_t f, iter_t l, iter_t p) : first(f), last(l), pos(p)
	{
	}
	
	bool operator!=(this_t& other)
	{
		return pos != other.pos;
	}
	
	bool operator==(this_t& other)
	{
		return pos == other.pos;
	}
	
	T& operator*()
	{
		return *pos;
	}
	
	T& operator->()
	{
		return pos.operator->();
	}
	
	this_t& operator++()
	{
		if(++pos == last)
			pos = first;
		return *this;
	}
	
	this_t operator++(int)
    {
        this_t tmp(*this); // copy
        operator++(); // pre-increment
        return tmp;   // return old value
    }
	
	this_t& operator=(iter_t p)
	{
		pos = p;
	}
	
};

template <typename iter_t>
struct std::iterator_traits<circular_iterator_t<iter_t>> : std::iterator_traits<iter_t>
{
	using iterator_category = forward_iterator_tag;
};

template<typename iter_t>
auto circular_iterator(iter_t f, iter_t l, iter_t p)
{
	return circular_iterator_t<iter_t>(f,l,p);
}

template<typename iter_t>
auto circular_iterator(iter_t f, iter_t l)
{
	return circular_iterator_t<iter_t>(f,l,f);
}

struct timer
{
	high_resolution_clock::time_point start = high_resolution_clock::now();
	
	~timer()
	{
		cout << "Took " << duration_cast<microseconds>(high_resolution_clock::now()-start).count() << " microseconds." << endl;
	}
	
};

int main()
{
	{
		timer t;
		list<int> buffer;
		buffer.push_back(0);
		
		auto it = circular_iterator(begin(buffer), end(buffer));
		
		for(int i = 1; i < 2018; i++)
		{
			advance(it,335);
			
			it = buffer.insert(next(it.pos),i);
			
		}
		
		cout << *next(it) << endl;
	}
	
	{
		timer t;
	
		int lastVal = -1, pos = 0;
		for(int i = 1; i < 50000000; i++)
		{
			pos = 1+(pos+335)%i;
			if(pos == 1)
				lastVal = i;
		}
		
		cout << lastVal << endl;
	}	
	
}