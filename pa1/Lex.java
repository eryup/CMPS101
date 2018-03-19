// Lex.java
// Eric Yup
// eyup@ucsc.edu
// pa1 
// arranges input text in alphabetical order 

import java.io.*;
import java.util.Scanner;


public class Lex{
	public static void main(String[] args) throws IOException{
	      // checks that there are two arguments
	      if (args.length != 2){
	          System.out.println("Usage: Lex <input file> <output file>");
		  System.exit(1);
	      }
	      int nline = 0;
	      Scanner in = null;
	      Scanner in2 = null;
	      PrintWriter writer = null;
			try{
			in = new Scanner(new File(args[0]));
			in2 = new Scanner(new File(args[0]));
			writer = new PrintWriter(args[1]);
			}catch(Exception e){
				System.out.println(e);
				System.exit(1);
			}
			while(in.hasNextLine()){
				nline++;
				in.nextLine();
			}
			in.close();
			String[] token = new String[nline];
			for(int i = 0; i < token.length; i++){
				token[i] = in2.nextLine();
			}
			in2.close();
			List L = new List();
			L.append(0);
			for(int i = 1; i<token.length; i++){
				L.moveFront();
				while(L.index()>=0){
					if(token[i].compareTo(token[L.get()]) < 0){
						L.insertBefore(i);
						break;
					}
					L.moveNext();
				}
				if(L.index() < 0){L.append(i);}
			}
			L.moveFront();
			for(int i = 0; i < nline; i++){
				writer.println(token[L.get()]);
				L.moveNext();
			}
			writer.close();
	}
}