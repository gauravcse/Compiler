/*
 * created By : Gaurav Mitra
 * 
 * This Class is used as an intermediate between Parsing Table and Test
 * for pretty printing the Parsing Table and also to provide the 
 * parsing table as an Input for the final test stage
 * 
 * */

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Map.Entry;
import java.util.Set;


public class Compile {
	HashMap<String,HashMap<String,String>> ptable = new HashMap<>();
	HashMap<String,Set<String>> first = new HashMap<String,Set<String>>();
	HashMap<String,Set<String>> follow = new HashMap<String,Set<String>>();
	HashMap<String,Production> gram;
	FirstFollow f;
	
	public Compile() throws NullPointerException, IOException {
		 f = new FirstFollow();
		 f.computeAll();
		 gram = f.lookup;
		 FirstFollowCopy("first_main.txt",first);
		 FirstFollowCopy("first_main.txt",follow);
		 //System.out.print(first.toString());
	}
	
	void FirstFollowCopy(String filename,HashMap<String,Set<String>> var) throws IOException {
		File file = new File(filename);
		FileReader fr = new FileReader(file);
		BufferedReader br = new BufferedReader(fr);
		String line = "";
		while(true) {
			line = br.readLine();
			if(line == null)
				break;
			System.out.println(line);
			String vars[] = line.split("->");
			String vars1[] = vars[1].trim().substring(1,vars[1].length() - 1).split(" ");
			Set<String> set = new HashSet<>();
			set.addAll(Arrays.asList(vars1));
			var.put(vars[0].trim(), set);
		}
		br.close();
	}
	
	
	public void compute() {
		//System.out.println("TABLE : \n\n\n");
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
								
								//System.out.println(first.get(start).toString());
								for(String fir : first.get(start)) {
									if(!fir.equals("e$")) {
										cell.put(fir, p1);
									}
									else {
										for(String fol : follow.get(start))
											cell.put(fol, p1);
									}
								}
							}
						}
					 }
				 }
			 }
			 ptable.put(nonT, cell);
		 }
		// System.out.print(ptable.toString());
	}
	
	// Utility function to pretty Print
	
	void prettyPrint() {
		System.out.println("\t\tPARSING TABLE\t\t");
		System.out.println("\t\t-------------\t\t\n\n");
		Iterator<Entry<String, HashMap<String, String>>> entry = ptable.entrySet().iterator();
		while(entry.hasNext()) {
			Entry<String, HashMap<String, String>> pair = entry.next();
			String keyLevel1 = pair.getKey();
			Iterator<Entry<String, String>> entry1 = pair.getValue().entrySet().iterator();
			while(entry1.hasNext()) {
				Entry<String, String> pair1 = entry1.next();
				String keyLevel2 = pair1.getKey();
				System.out.println("[ " + keyLevel1 + " , " + keyLevel2 + " ] => [ " + keyLevel1 + " -> " + ptable.get(keyLevel1).get(keyLevel2) + " ]");
			}
			
		}
	}
	
	//Test function
	
	public static void main(String [] args) throws NullPointerException, IOException {
		Compile p = new Compile();
		p.compute();
		p.prettyPrint();
	}
}
