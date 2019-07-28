// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
using namespace std;

int main() {
	unordered_set<string> mySet;

	string line;
	ifstream myfile("gdscript.cpp");
	mySet.insert("gdscript.cpp");
	if (myfile.is_open()){
		while( getline(myfile,line) ){
			if (line.find("#include")!=string::npos){
				auto pos = line.find_first_not_of("\"< ", 8);
				auto lgth = line.find_last_not_of("\"> ") - pos;
				line = line.substr(pos, lgth+1);
				mySet.insert(line);
			}
		}

		for(auto s:mySet){
			cout << s << endl;
		}

		myfile.close();
	}

	else cout << "Unable to open file"; 

	return 0;
}