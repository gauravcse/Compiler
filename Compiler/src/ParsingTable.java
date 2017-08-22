/*
 * created By : Gaurav Mitra
 * 
 * This Class is used to compute the LL(1) parsing table for the grammar 
 * 
 * */

import java.io.IOException;
import java.util.HashMap;
import java.util.Iterator;


public class ParsingTable {
	
	// ptable : Stores the parsing table as Map<Non Terminal,Map<Terrminal, Production>>
	// gram : The grammar
	// f : First follow object uses the computed value of first follow of the grammar
	
	HashMap<String,HashMap<String,String>> ptable = new HashMap<>();
	HashMap<String,Production> gram;
	FirstFollow f;
	
	// Constructor
	
	public ParsingTable() throws NullPointerException, IOException {
		 f = new FirstFollow();
		 f.computeAll();
		 gram = f.lookup;
	}
	
	// Computes the parsing table for the grammar
	
	public void compute() {
		 for(String nonT : f.nonTer) {
			 HashMap<String, String> cell = new HashMap<>();
			 for(int i = 0; i < gram.get(nonT).productions.size(); i++) {
				 String p1 = gram.get(nonT).productions.get(i);
				 //System.out.println(nonT + "->" + p1);
				 int p1size = p1.length();
				 Iterator<String> iter = f.terminal.iterator();
				 boolean isTer = false;
				 while(iter.hasNext()) {
					 String cur_T = iter.next();
					 int cur_T_size = cur_T.length();
					 if(p1size >=  cur_T_size) {
						 String start = p1.substring(0,cur_T_size);
						 if(start.equals(cur_T)) {
							 cell.put(cur_T,p1);
							 isTer = true;
						 }
					 }
				 }
				 if(!isTer) {
					 iter = f.nonTer.iterator();
					 while(iter.hasNext()) {
						String cur_nonT = iter.next();
						int cur_nonT_size = cur_nonT.length();
						if(p1size >=  cur_nonT_size) {
							String start = p1.substring(0,cur_nonT_size);
							if(start.equals(cur_nonT)) {
								//System.out.println("Start : " + start);
								
								//System.out.println(f.first.get(start).toString());
								for(String fir : f.first.get(start)) {
									if(!fir.equals("e$")) {
										cell.put(fir, p1);
									}
									else {
										for(String fol : f.follow.get(start))
											cell.put(fol, p1);
									}
								}
							}
						}
					 }
				 }
			 }
		 }
		 System.out.print(ptable.toString());
	}
	
	// Test main
	
	public static void main(String [] args) throws NullPointerException, IOException {
		ParsingTable p = new ParsingTable();
		p.compute();

	}
}
