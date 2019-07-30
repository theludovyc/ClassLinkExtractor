#include <iostream>
#include <fstream>
#include <string>
#include <forward_list>
#include <stack>
#include <unordered_set>
using namespace std;

forward_list<string> myList;

stack<string> myStack;

ifstream *myFileIn;
ofstream *myFileOut;

unordered_set<string> mySet;

void exploreFile(){
	string line;

	if( mySet.find( myStack.top() ) == mySet.end() ){
		mySet.insert(myStack.top());

		(*myFileOut) << myStack.top() << endl;

		for(auto s:myList){
			myFileIn->open(s+myStack.top());

			if (myFileIn->is_open()){
				while( getline(*myFileIn, line) ){
					if (line.find("#include")!=string::npos){
						auto pos = line.find_first_not_of("\"< ", 8);
						auto lgth = line.find_last_not_of("\"> ") - pos;
						line = line.substr(pos, lgth+1);

						(*myFileOut) << line << endl;

						if ( mySet.find( line ) == mySet.end() ){
							myStack.push(line);
						}
					}
				}

				myFileIn->close();
				break;
			}else{
				(*myFileOut) << "Unable to open file : " << s+myStack.top() << endl;
			}
		}

		(*myFileOut) << endl;
	}

	myStack.pop();
}

int main(int n, char* params[]) {
	if(n<2){
		cout << "no input file" << endl;
		return -1;
	}

	myStack.push(params[1]);
	myFileIn = new ifstream();

	if(n<3){
		cout << "no output file" <<endl;
		return -1;
	}

	myFileOut = new ofstream(params[2]);

	myList.push_front("./");

	for(int i=3; i<n; i++){
		myList.push_front(params[i]);
	}

	myList.reverse();

	while(!myStack.empty()){
		exploreFile();
	}

	myFileOut->close();

	delete(myFileIn);
	delete(myFileOut);

	for(auto obj:mySet){
		cout << obj << endl;
	}

	return 0;
}