#include <iostream>
#include <vector>
#include <unordered_map>
#include <tuple>
#include <stdexcept>
#include <queue>

using namespace std;

unordered_map<string,int> operations = {// <opcode,nargs>
	{"set",0},
	{"sub",1},
	{"mul",2},
	{"jnz",3},
	{"mod",4}
};

string ops[] = {
	"set",
	"sub",
	"mul",
	"jnz",
	"mod"
};

struct executer
{
	vector<tuple<int,string,string>> instructions; // <opcode,X,Y>
	vector<tuple<int,string,string>>::iterator pc = instructions.begin();
	
	unordered_map<char,long long> registers;
	
	int mulCount = 0;
	
	long long getVal(string& s)
	{
		try
		{
			return stoi(s);
		}
		catch(const invalid_argument& e)
		{
			return registers[s.front()];
		}
		
	}
	
	bool run()
	{
		for(; pc >= instructions.begin() && pc < instructions.end(); advance(pc,1))
		{
			//cout << '[' << distance(begin(instructions),pc) << "] " << ops[get<0>(*pc)] << ' ' << get<1>(*pc) << ' ' << get<2>(*pc) << endl;
			switch(get<0>(*pc))
			{
				case 0:
					registers[get<1>(*pc).front()] = getVal(get<2>(*pc));
					break;
				case 1:
					registers[get<1>(*pc).front()] -= getVal(get<2>(*pc));
					break;
				case 2:
					registers[get<1>(*pc).front()] *= getVal(get<2>(*pc));
					break;
				case 3:
					if(getVal(get<1>(*pc)) != 0)
					{
						int skip = getVal(get<2>(*pc));
						advance(pc,skip-1);
					}
					break;
				case 4:
					registers[get<1>(*pc).front()] %= getVal(get<2>(*pc));
					break;
				
				default:
					cerr << "Unknown op " << get<0>(*pc) << endl;
					exit(0);
					break;
			}
			
		}	
		
	}
	
	friend istream& operator>>(istream& ss, executer& obj)
	{
		while(!ss.eof())
		{
			string op;
			ss >> op;
			int id = operations.at(op);
			
			string X,Y;
			ss >> X >> Y;
			ss.ignore();
			
			obj.instructions.push_back(make_tuple(id,X,Y));
		}
		
		obj.pc = begin(obj.instructions);
		//cerr << "done " << obj.instructions.size() << endl;
		return ss;
	}
	
};

int main()
{
	executer ex1;
	cin >> ex1;
	
	ex1.registers['a'] = 1;
	
	ex1.run();
	
	cout << ex1.registers['h'] << endl;
	
}
