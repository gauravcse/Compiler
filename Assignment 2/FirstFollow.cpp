#include<bits/stdc++.h>
using namespace std;

map<char,vector<string> > grammar;
set<char> nonterminals;
map<char,set<char> > first;
map<char,set<char> > follow;

bool checkTerminal(char nonT) {
	for(vector<string>::iterator it = grammar[nonT].begin(); it != grammar[nonT].end(); it++) {
		if((*it)[0] >= 'A' && (*it)[0] <= 'Z')
			return false;
	}
	return true;
}

bool isTerminal(string s) {
	if(s[0] >= 'A' && s[0] <= 'Z') {
		return false;
	}
	return true;
}

bool isTerminalc(char c) {
	if(c >= 'A' && c <= 'Z') {
		return false;
	}
	return true;
}


set<char>& computeFirst(char nonT) {
	if(checkTerminal(nonT)) {
		for(int i = 0; i < grammar[nonT].size(); i++) {
			first[nonT].insert(grammar[nonT][i][0]);
		}
		return first[nonT];
	}
	else {
		//bool isEpsilon = false;
		for(int i = 0; i < grammar[nonT].size(); i++) {
			if(isTerminal(grammar[nonT][i])) {
				first[nonT].insert(grammar[nonT][i][0]);
			}
			else {
				set<char> terminals;
				terminals = computeFirst(grammar[nonT][i][0]);
				for(set<char>::iterator it = terminals.begin(); it != terminals.end(); it++) {
					if((*it) == 'e' && grammar[nonT][i].size() > 1) {
						set<char> termi;
						termi = computeFirst(grammar[nonT][i][1]);
						for(set<char>::iterator iter = termi.begin(); iter != termi.end(); iter++) {
							first[nonT].insert(*iter);	
						}
					}
					else
						first[nonT].insert(*it);
				}
			}
			/*if(isEpsilon) {
				for(vector<string>::iterator it = grammar[nonT].begin(); it != grammar[nonT].end(); it++) {
					set<char> terminals2;
					if((*it).size() > 2)
						terminals2 = computeFirst((*it)[1]);
					for(set<char>::iterator iter = terminals2.begin(); iter != terminals2.end(); iter++) {
						first[nonT].insert(*iter);
					}
				}
			}*/
		}
		return first[nonT];
	}
}

void computeFollow() {
	vector<char> nonterminals;
	for(map<char,vector<string> >::iterator it = grammar.begin(); it != grammar.end(); it++) {
		nonterminals.push_back(it->first);
	}
	for(int i = 0; i < nonterminals.size(); i++) {
		for(int j = 0; j < nonterminals.size(); j++) {
			for(int k = 0; k < grammar[nonterminals[j]].size(); k++) {
				string prod = grammar[nonterminals[j]][k];
				for(int l = 0; l < prod.size(); l++) {
					if(nonterminals[i] == prod[l]) {
						if((l + 1) >= prod.size() && (follow.find(nonterminals[j]) != follow.end())) {
							for(set<char>::iterator it = follow[nonterminals[j]].begin(); it != follow[nonterminals[j]].end(); it++) {
								follow[nonterminals[i]].insert(*it);
							}
						}
						else if(isTerminalc(prod[l + 1])) {
							follow[nonterminals[i]].insert(prod[l + 1]);
						}
						else if(!isTerminalc(prod[l + 1])) {
							for(set<char>::iterator it = first[prod[l + 1]].begin(); it != first[prod[l + 1]].end(); it++) {
								if(*it != 'e')
									follow[nonterminals[i]].insert(*it);
								else {
									if(prod.size() > l + 1)
									for(set<char>::iterator iter = first[prod[l + 2]].begin(); iter != first[prod[l + 2]].end(); iter++) {
										follow[nonterminals[i]].insert(*iter);						
									}
								}
							}
						}
					}
				}
			}
		}
	}
}


void parseLine(string line) {
	nonterminals.insert(line[0]);
	grammar[line[0]].push_back(line.substr(3,line.size() - 3));
}

void parseGrammar() {
	fstream input("grammar2.txt");
	bool top = false;
	for(string line; getline( input, line ); ) {
		if(!top) {
			follow[line[0]].insert('$');
			top = true;
		}
    	parseLine(line);
	}
}

void writeFile() {
	ofstream outfile("firstfollow1.txt");
	string output;
	for(set<char>::iterator it = nonterminals.begin(); it != nonterminals.end(); it++) {
		output = output + (*it) + " ->  {";
		for(set<char>::iterator iter = first[*it].begin(); iter != first[*it].end(); iter++) {
			output = output + " " + (*iter) + " , ";
		}
		output = output + " }  ,  {";
		for(set<char>::iterator iter = follow[*it].begin(); iter != follow[*it].end(); iter++) {
			output = output + " " + (*iter) + " , ";
		}
		output = output + " }";
		outfile<<output<<endl;
		output = "";
	}
}

void computeAll() {
	parseGrammar();
	for(set<char>::iterator it = nonterminals.begin(); it != nonterminals.end(); it++) {
		computeFirst(*it);
	}
	for(set<char>::iterator it = nonterminals.begin(); it != nonterminals.end(); it++) {
		computeFollow();
	}
	writeFile();
}

int main(void) {
	computeAll();
}
