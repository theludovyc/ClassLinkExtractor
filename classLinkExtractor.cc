// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
using namespace std;

ifstream *myFile;

unordered_set<string> mySet;

int main() {
	myFile = new ifstream();

	string line;

	myFile->open("gdscript.cpp");

	mySet.insert("gdscript.cpp");

	if (myFile->is_open()){
		while( getline(*myFile,line) ){
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

		myFile->close();
	}

	else cout << "Unable to open file"; 

	delete(myFile);

	return 0;
}