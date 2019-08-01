#include <iostream>
#include <fstream>
#include <string>
#include <forward_list>
#include <unordered_set>
using namespace std;

forward_list<string> myList;

ifstream *myFileIn;
ofstream *myFileOut;

unordered_set<string> fileToExplore;
unordered_set<string> fileExplored;

void exploreFile(){
	string line;

	string myFile = *fileToExplore.begin();

	if( fileExplored.find(myFile) == fileExplored.end() ){
		fileExplored.insert(myFile);

		(*myFileOut) << myFile << endl;

		for(auto s:myList){
			myFileIn->open(s+myFile);

			if (myFileIn->is_open()){
				while( getline(*myFileIn, line) ){
					if (line.find("#include")!=string::npos){
						auto pos = line.find_first_not_of("\"< ", 8);
						auto lgth = line.find_last_not_of("\"> ") - pos;
						line = line.substr(pos, lgth+1);

						(*myFileOut) << line << endl;

						if ( fileExplored.find(line) == fileExplored.end() ){
							fileToExplore.insert(line);
						}
					}
				}

				myFileIn->close();
				break;
			}else{
				(*myFileOut) << "Unable to open file : " << s+myFile << endl;
			}
		}

		(*myFileOut) << endl;
	}

	fileToExplore.erase(myFile);
}

int main(int n, char* params[]) {
	if(n<2){
		cout << "no input file" << endl;
		return -1;
	}

	fileToExplore.insert(params[1]);

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

	do{
		exploreFile();
	}while(!fileToExplore.empty());

	myFileOut->close();

	delete(myFileIn);
	delete(myFileOut);

	cout << fileExplored.size() << " : files explored" << endl;

	return 0;
}