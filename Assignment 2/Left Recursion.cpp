#include<iostream>
#include<fstream>
#include<map>

using namespace std;

map<char,int> nonterminal;
map<char,string> grammar;
bool ERRORFLAG = false;

void printMap() {
	for(map<char,int>::iterator it = nonterminal.begin(); it != nonterminal.end(); it++) {
		cout<<it->first<<"\t"<<it->second<<endl;
	}
}

void getLeft(string s, int current) {
	if(nonterminal.find(s[0]) != nonterminal.end()) {
		ERRORFLAG = true;
		return;
	}
	nonterminal[s[0]] = current;
}

void nonterminalGrammar() {
	fstream input("grammar.txt");
	int current = 1;
	for(string line; getline( input, line ); ) {
    	getLeft(line,current);
    	current++;
	}
	input.close();
	//printMap();
}

void parseLine(string line) {
		
}

void saveGrammar() {
	fstream input("grammar.txt");
	for(string line; getline( input, line ); ) {
    	parseLine(line);
	}
}


int main(void) {
	nonterminalGrammar();
	saveGrammar();
}
