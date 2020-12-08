#include <iostream>
#include <vector>
#include <unordered_map>
#include <tuple>
#include <stdexcept>
#include <queue>

using namespace std;

unordered_map<string,pair<int,int>> operations = {// <opcode,nargs>
	{"snd",{0,1}},
	{"set",{1,2}},
	{"add",{2,2}},
	{"mul",{3,2}},
	{"mod",{4,2}},
	{"rcv",{5,1}},
	{"jgz",{6,2}},
};

string ops[] = {
	"snd",
	"set",
	"add",
	"mul",
	"mod",
	"rcv",
	"jgz",
};

struct executer
{
	vector<tuple<int,string,string>> instructions; // <opcode,X,Y>
	vector<tuple<int,string,string>>::iterator pc = instructions.begin();
	
	unordered_map<char,long long> registers;
	
	queue<int> messageQueue;
	
	executer* otherExe;
	
	int sendCount = 0;
	
	int pid;
	
	executer() = default;
	executer(executer& other) : instructions(other.instructions), otherExe(&other), sendCount(0), pc(instructions.begin())
	{
		int pid = registers['p'] = (other.pid = other.registers['p']) + 1;
		other.otherExe = this;
	}
	
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
		
		bool locked = true;
		
		for(; pc != end(instructions); advance(pc,1))
		{
			//cout << '#' << pid <<  '[' << distance(begin(instructions),pc) << "] " << ops[get<0>(*pc)] << ' ' << get<1>(*pc) << ' ' << get<2>(*pc) << endl;
			switch(get<0>(*pc))
			{
				case 0:
					otherExe->messageQueue.push(getVal(get<1>(*pc)));
					sendCount++;
					break;
				case 1:
					registers[get<1>(*pc).front()] = getVal(get<2>(*pc));
					break;
				case 2:
					registers[get<1>(*pc).front()] += getVal(get<2>(*pc));
					break;
				case 3:
					registers[get<1>(*pc).front()] *= getVal(get<2>(*pc));
					break;
				case 4:
					registers[get<1>(*pc).front()] %= getVal(get<2>(*pc));
					break;
				case 5:
					if(messageQueue.empty())
					{
						return !locked;
					}
					registers[get<1>(*pc).front()] = messageQueue.front();
					messageQueue.pop();
					break;
				case 6:
					if(getVal(get<1>(*pc)) > 0)
					{
						int skip = getVal(get<2>(*pc));
						advance(pc,skip-1);
					}
					break;
				
				default:
					cerr << "Unknown op " << get<0>(*pc) << endl;
					exit(0);
					break;
			}

			locked = false;
			
		}	
		
	}
	
	friend istream& operator>>(istream& ss, executer& obj)
	{
		while(!ss.eof())
		{
			string op;
			ss >> op;
			auto p = operations.at(op);
			
			string X,Y;
			ss >> X;
			if(p.second == 2)
				ss >> Y;
			ss.ignore();
			
			obj.instructions.push_back(make_tuple(p.first,X,Y));
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
	
	executer ex2(ex1);
	
	while(ex1.run() || ex2.run());
	
	cout << ex2.sendCount << endl;
	
}
