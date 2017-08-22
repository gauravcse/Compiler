/*
 * created By : Gaurav Mitra
 * 
 * This Class is used to remove the left recursion from the Grammar 
 * given as an input.
 * A new left recursion removed grammar is saved in a file.
 * 
 * */


import java.io.IOException;

public class LeftRecursion {
	
	//g : Saves the grammar
	
	public Grammar g;

	//Constructor
	
	public LeftRecursion(Grammar g) {
		this.g = g;
	}
	
	// Function to remove left recursion
	
	public void removeLL() {
		int nonTlen = g.nonTerminals.size();
		Grammar newgrammar = new Grammar();
		for(int i = 0; i < nonTlen; i++) {
			Grammar temp = new Grammar();
			Production p = g.grammar.get(i);
			for(int j = 0; j < i; j++) {
				p = removeIndirect(p,g.grammar.get(j));
				temp.add(p);
			}
			String prettyprinter = p.nonT + " -> ";
			for(String prod :  p.productions)
				prettyprinter += prod + " | ";
			System.out.println(prettyprinter);
			newgrammar.update(removeDirect(temp));
		}
	}
	
	// Helper function  to remove direct left recursion 
	
	public Grammar removeDirect(Grammar gram) {
		Grammar temp = new Grammar();
		for(int i = 0; i < gram.grammar.size(); i++) {
			Production p = gram.grammar.get(i);
			for(int j = 0; j < p.productions.size(); j++) {
				if(p.productions.get(j).startsWith(p.nonT)) {
					System.out.print("Direct Visited");
					for(int k = 0; k < p.productions.size(); k++) {
						if(!p.productions.get(k).startsWith(p.nonT)) {
							Production p1 = new Production();
							p1.nonT = p.nonT + "'";
							p1.productions.add(p.productions.get(k) + p.productions.get(j).substring(p.nonT.length(),p.productions.get(k).length()));
						}
					}
				}
			}
			temp.add(p);
		}
		return temp;
	}
	
	// Helper function  to remove indirect left recursion
	
	public Production removeIndirect(Production ai,Production aj) {
		Production newp = new Production();
		newp.nonT = ai.nonT;
		for(String aiprod : ai.productions) {
			if(aiprod.startsWith(aj.nonT)) {
				for(int i = 0; i < aj.productions.size(); i++) {
					String addP = aj.productions.get(i);
					String s = addP + aiprod.substring(aj.nonT.length(),aiprod.length());
					newp.productions.add(s);
				}
			}
			else {
				newp.productions.add(aiprod);
			}
		}
		return newp;
	}
	
	//Main function to test correctness
	
	public static void main(String [] args) throws NullPointerException, IOException {
		Grammar g1 = new Grammar("prog_gram1.txt");
		LeftRecursion l = new LeftRecursion(g1);
		l.removeLL();
	}
}
