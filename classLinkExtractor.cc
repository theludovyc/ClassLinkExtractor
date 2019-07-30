#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <stack>
using namespace std;

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

					if ( mySet.find( line ) == mySet.end() ){
						myStack.push(line);
					}
				}
			}

			myFile->close();
		}else{
			cout << "Unable to open file : " << myStack.top() << endl;
		}
	}

	myStack.pop();
}

int main(int n, char* params[]) {
	myFile = new ifstream();

	if(n<2){
		cout << "no input file" << endl;
		return -1;
	}

	myStack.push(params[1]);

	while(!myStack.empty()){
		exploreFile();
	}

	for(auto obj:mySet){
		cout << obj << endl;
	}

	delete(myFile);

	return 0;
}