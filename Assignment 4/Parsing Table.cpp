#include<bits/stdc++.h>

map<int,vector<string> > grammar;
set<string> t;
set<string> nont;
map<string, vector<string> > gram;
map<string, string> first;
map<string, string> follow;
map<string, map<string,string> > ptable;
stack<string> 

void readTerminals() {
	ifstream outfile("term.txt");
	string line;
	getline(input,line);
	int l = line.size(), i = 0;
	string each = "";
	while(i < l) {
		if(each[i] != ',') {
			each += line[i];
		}
		else {
			t.insert(each);
			each = "";	
		}
		i++;
	}
}

void readNonTerminals() {
	ifstream outfile("nonterm.txt");
	string line;
	getline(input,line);
	int l = line.size(), i = 0;
	string each = "";
	while(i < l) {
		if(each[i] != ',') {
			each += line[i];
		}
		else {
			t.insert(each);
			each = "";	
		}
		i++;
	}
}

void readGrammar() {
	fstream input("grammar.txt");
	bool top = false;
	for(string line; getline( input, line ); ) {
		string prod = line.substr(line.find("->"), line.size() - line.find("->") - 2);
		string ter = line.substr(0,line.find("->"));
		gram[ter].push_back(prod);
	}
}

void readFirstFollow() {
	fstream input("first_follow.txt");
	for(string line; getline( input, line ); ) {
		int pos = line.find("-");
		string nonT = line.substr(0,pos - 1);
		string rest = line.substr(pos + 3,line.size() - pos - 3);
		string fir = rest.substr(0, rest.size() - rest.find("}"));
		string fol = rest.substr(rest.find("}"),
	}
}

void makeTable() {
	for(map<string,vector<string>::iterator it = gram.begin(); it != gram.end(); it++) {
		string ter = it->first;
		for(int i = 0; i < gram[ter].size(); i++) {
			string eachp = gram[ter][i];
			if(each == "eps ") {
				for(int j = 0; j < follow[f].size(); j++) {
					ptable[ter][follow[f][j]] = eachp;
				}
				continue;
			}
			string f = "";
			int p = 0;
			while(p != " ") {
				f += eachp[p++];
			}
			if(t.find(f)) {
				ptable[ter][f] = eachp;
			}
			else if(nont.find(f)) {
				for(int j = 0; j < first[f].size(); j++) {
					ptable[ter][first[f][j]] = eachp;
				}
			}
		}
	}
}



int main(void) {
	readTerminals();
	readNonTerminals();
	readGrammar();
	readFirstFollow();
	makeTable();
}
