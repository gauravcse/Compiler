/*
 * created By : Gaurav Mitra
 * 
 * This Class is used to efficiently save the production rules of the grammar.
 * Each production is saved in an arraylist.
 * 
 * */

import java.util.ArrayList;

public class Production {
	
	//nonT : Instance variable for storing the left hand side of the production.
	//productions : The right hand side of the productions
	
	public String nonT;
	ArrayList<String> productions = new ArrayList<>();
	
	//Constructor
	
	Production(String line)throws NullPointerException{
		int index = getIndex(line,"->");
		nonT = line.substring(0,index).trim();
		String rest = line.substring(index + 2,line.length()).trim();
		//System.out.println(rest);
		String[] prod = rest.split("\\|");
		//System.out.println(prod.length);
		for(int i = 0; i < prod.length;i++) {
			try {
				//System.out.println(prod[i].trim());
				productions.add(prod[i].trim());
				//System.out.println("Here");
			}
			catch (Exception e) {
				continue;
			}
		}
	}
	
	// Overloaded Constructor
	
	public Production() {
		
	}
	
	//Index of pattern
	
	private int getIndex(String string,String pattern) {
		return string.indexOf(pattern);
	}
	
	// Print all the productions of the grammar
	
	public void printProductions() {
		String buffer = new String(nonT + " -> ");
		for(String prod : productions) {
			buffer += prod + " | ";
		}
		System.out.println(buffer);
	}
}
