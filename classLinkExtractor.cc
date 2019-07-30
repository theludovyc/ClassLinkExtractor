// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <stack>
using namespace std;

class CheckPath{
	public:
		string path;
		bool b;

		CheckPath(string s, bool b){
			path=s;
			b=b;
  	}
};

struct CheckPath_Hasher{
  size_t operator()(const CheckPath & obj) const{
    return hash<string>()(obj.path);
  }
};

struct CheckPath_Comparator{
  bool operator()(const CheckPath & obj0, const CheckPath & obj1) const{
    if (obj0.path == obj1.path)
      return true;
    return false;
  }
};

ifstream *myFile;

stack<string> myStack;

unordered_set<string> mySet;

void exploreFile(){
	string line;

	if( mySet.find( myStack.top() ) == mySet.end() ){
		mySet.insert(myStack.top());

		myFile->open(myStack.top());

		if (myFile->is_open()){
			while( getline(*myFile,line) ){
				if (line.find("#include")!=string::npos){
					auto pos = line.find_first_not_of("\"< ", 8);
					auto lgth = line.find_last_not_of("\"> ") - pos;
					line = line.substr(pos, lgth+1);

					myStack.push(line);
				}
			}

			myFile->close();
		}else{
			cout << "Unable to open file : " << myStack.top() << endl;
		}
	}

	myStack.pop();
}

int main() {
	myFile = new ifstream();

	myStack.push("gdscript.cpp");

	while(!myStack.empty()){
		exploreFile();
	}

	for(auto obj:mySet){
		cout << obj << endl;
	}

	delete(myFile);

	return 0;
}