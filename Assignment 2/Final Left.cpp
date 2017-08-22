#include<iostream>
#include<fstream>
#include<vector>

using namespace std;
vector<vector<string> > grammar(26);

void directLeftRemove(int superI) {
	for(int i = 0; i < superI; i++) {
		vector<string> withleft;
		vector<string> withoutleft;
		for(int j = 0; j < grammar[i].size(); j++) {
			if(grammar[i][j][0] == (char)(i + 65))
				withleft.push_back(grammar[i][j]);
			else
				withoutleft.push_back(grammar[i][j]);	
		}
		for(int k = 0; k < withoutleft.size() && withleft.size() != 0; k++) {
			withoutleft[k] += (char)(90- i);
			//cout<<withoutleft[k]<<endl;
		}
		for(int k = 0; k < withleft.size(); k++) {
			withleft[k] = withleft[k].substr(1,withleft[k].size() - 1) + (char)(90- i);
			//cout<<withleft[k]<<endl;
		}
		if(withleft.size() != 0) {
			grammar[i].clear();
			for(int k = 0; k < withoutleft.size(); k++) {
				grammar[i].push_back(withoutleft[k]);
			}
			for(int k = 0; k < withleft.size(); k++) {
				grammar[25 - i].push_back(withleft[k]);
			}
		}
	}
}

void totalLeftRecursion() {
	for(int i = 0; i < 13; i++) {
		for(int j = 0; j < i; j++) {
			for(int k = 0; k < grammar[i].size(); k++) {
				if(grammar[i][k][0] == (char)(j + 65)) {
					for(int r = 0; r < grammar[j].size(); r++) {
						grammar[i].push_back(grammar[j][r] + grammar[i][k].substr(1,grammar[i][k].size() - 1));					
					}			
					grammar[i].erase(grammar[i].begin());
				}
			}
		}
		directLeftRemove(i + 1);
	}
}

void parseRHS(char lhs,string rhs) {
	int l = rhs.size();
	string each = "";
	for(int i = 0; i < l; i++) {
		if(rhs[i] == '|') {
			grammar[lhs - 65].push_back(each);
			//cout<<each<<endl;
			each = "";
		}
		else {
			each += rhs[i];
		}
	}
	grammar[lhs - 65].push_back(each);
}

void parseLine(string line) {
	char first = line[0];
	line = line.substr(3,line.size() - 3);
	parseRHS(first,line);
}

void printMap() {
	for(int i = 0; i < 26; i++) {
		for(int j = 0; j < grammar[i].size(); j++) {
			cout<<i<<"\t"<<grammar[i][j]<<"\t";
		}
		cout<<endl;
	}
}

void parseGrammar() {
	fstream input("grammar.txt");
	for(string line; getline( input, line ); ) {
    	parseLine(line);
	}
	//printMap();
	//directLeftRemove();
	totalLeftRecursion();
	printMap();
}

void printGrammar() {
	ofstream output("output.txt");
	for (int i = 0; i < 26; ++i) {
		string write = "";
		if(grammar[i].size() > 0) {
			for (int j = 0; j < grammar[i].size(); ++j) {
				write += grammar[i][j] + "|";
			}
		}
		if(write.size() > 0) {
			cout<<write<<endl;
			output<<write<<endl;
		}
	}
	output.close();
}

int main(void) {
	parseGrammar();
	printGrammar();
}
