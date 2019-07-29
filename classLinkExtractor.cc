// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
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

unordered_set<CheckPath, CheckPath_Hasher, CheckPath_Comparator> mySet;

void exploreFile(const string fileName){
	string line;

	myFile->open(fileName);

	if (myFile->is_open()){
		mySet.insert(CheckPath(fileName, true));

		while( getline(*myFile,line) ){
			if (line.find("#include")!=string::npos){
				auto pos = line.find_first_not_of("\"< ", 8);
				auto lgth = line.find_last_not_of("\"> ") - pos;
				line = line.substr(pos, lgth+1);
				mySet.insert(CheckPath(line, false));
			}
		}

		for(auto obj:mySet){
			cout << obj.path << endl;
		}

		myFile->close();
	}

	else cout << "Unable to open file"; 
}

int main() {
	myFile = new ifstream();

	exploreFile("gdscript.cpp");

	delete(myFile);

	return 0;
}