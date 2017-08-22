#include<iostream>
#include<fstream>
#include<map>
#include<list>
using namespace std;
map<string,list<string> > grammar;

void directLeftRemove(string lhs,list<string> &production) {
	char left = lhs[0];
	cout<<lhs;
	list<string> withleft;
	list<string> withoutleft;
	for(list<string>::iterator it = production.begin(); it != production.end(); it++) {
		cout<<(*it)[0]<<endl;
		if(left == (*it)[0])
			withleft.push_back((*it));
		else
			withoutleft.push_back((*it));
	}
	for(list<string>::iterator it = withleft.begin(); it != withleft.end(); it++) {
	//	cout<<(*it)<<endl;
	}
	for(list<string>::iterator it = withoutleft.begin(); it != withoutleft.end(); it++) {
		//cout<<(*it)<<endl;
	}
}

void parseRHS(string lhs,string rhs,int lineno) {
	int l = rhs.size();
	string each = "";
	for(int i = 0; i < l; i++) {
		
		if(rhs[i] == '|') {
			if(grammar.find(lhs) == grammar.end()) {
				grammar[lhs];
			}
			grammar[lhs].push_back(each);
			//cout<<each<<endl;
			each = "";
		}
		else {
			each += rhs[i];
		}
	}
	grammar[lhs].push_back(each);
}

void parseLine(string line,int number) {
	int nonter_pos = line.find("->");
	string first = line.substr(0,nonter_pos - 1);
	line = line.substr(nonter_pos + 2,line.size() - nonter_pos - 2);
	parseRHS(first,line,number);
}

void printMap() {
	for(map<string,list<string> >::iterator it = grammar.begin(); it != grammar.end(); it++ ) {
		cout<<it->first<<endl;
		directLeftRemove(it->first,it->second);
		//for(list<string>::iterator iter = (it->second).begin(); iter != (it->second).end(); iter++)
			//cout<<*(iter)<<endl;
			
	}
}

void parseGrammar() {
	fstream input("grammar.txt");
	int count = 0;
	for(string line; getline( input, line ); ) {
		count++;
    	parseLine(line,count);
	}
	printMap();
}

int main(void) {
	parseGrammar();
	
}
