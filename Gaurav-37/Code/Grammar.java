/*
 * created By : Gaurav Mitra
 * 
 * This Class is used to efficiently save the grammar of the language.
 * Also contains the list of the nonTerminals of the grammar.
 * 
 * */

import java.util.ArrayList;
import java.util.HashMap;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

public class Grammar {

	//grammar : Production rules making up the grammar
	//nonTerminals : The list of nonTerminals of the grammar.
	
	ArrayList<Production> grammar = new ArrayList<>();
	ArrayList<String> nonTerminals = new ArrayList<>();
	
	// Constructor
	
	Grammar() {
		
	}
	
	// Overloaded Constructor
	
	Grammar(String filename)throws IOException,NullPointerException {
		File file = new File(filename);
		FileReader fr = new FileReader(file);
		BufferedReader br = new BufferedReader(fr);
		String line = "";
		while(true) {
			line = br.readLine();
			if(line != null) {
				Production p = new Production(line);
				grammar.add(p);
				nonTerminals.add(p.nonT);
			}
			else
				break;
		}
		br.close();
	}
	
	// Add production rule to the grammar. utility function.
	
	public void add(Production p) {
		grammar.add(p);
		nonTerminals.add(p.nonT);
	}
	
	// Print the production rules of the grammar.
	
	public void printGrammar()throws NullPointerException{
		for(Production p : grammar) {
			p.printProductions();
		}	
	}
	
	//Update the production rules of the grammar.
	
	public void update(Grammar g) {
		for(int i = 0; i < g.grammar.size(); i++) {
			this.grammar.add(g.grammar.get(i));
			this.nonTerminals.add(g.grammar.get(i).nonT);
		}
	}
	
	// Store the productions in a map for later use.
	
	public void storeMap(HashMap<String,Production> lookup) {
		for(Production p : grammar) {
			lookup.put(p.nonT, p);
		}
	}
}
