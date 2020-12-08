#include <iostream>
#include <iomanip>
using namespace std;

class generator
{
private:
	int factor;
	int mult;
	unsigned long long current;
	
public:

	generator(unsigned int first, int f, int m) : factor(f), mult(m), current(first)
	{
		cerr << factor << '_' << current << endl;
	}

	void next()
	{
		do
			current = (current * factor) % 2147483647;
		while(current % mult != 0);
	}
	
	bool operator==(const generator& other) const
	{
		return (current & 65535) == (other.current & 65535);
	}
	
	friend ostream& operator<<(ostream& os, const generator& obj)
	{
		return os << obj.current;
	}
	
};

int main()
{
	int count = 0;
	
	generator A(512,16807,4), B(191,48271,8);
	for(int i = 0; i < 5000000; i++,A.next(),B.next())
	{
		if(A == B)
			count++;
		//cerr << setfill(' ') << setw(10) << A << ' '  << setw(10) << B << endl;
	}
	
	cout << count << endl;
}