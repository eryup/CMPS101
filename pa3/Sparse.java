
// Sparse.java
// Eric Yup
// eyup@ucsc.edu 
// pa3 
// Reads input file and represents Matrix using a List of data points
import java.io.*;
import java.util.Scanner;

public class Sparse {

	public static void main(String[] args) throws IOException {
		if (args.length != 2) {
			System.out.println("Usage: Sparse inputFileName outputFileName");
			System.exit(1);
		}

		Scanner in = new Scanner(new File(args[0]));
		int n = in.nextInt();// size of matrix
		int a = in.nextInt();
		int b = in.nextInt();
		Matrix A = new Matrix(n);
		Matrix B = new Matrix(n);

		for (int i = 0; i < a; i++) {
			int row = in.nextInt();
			int col = in.nextInt();
			double val = in.nextDouble();
			A.changeEntry(row, col, val);
		}

		for (int i = 0; i < b; i++) {
			int row = in.nextInt();
			int col = in.nextInt();
			double val = in.nextDouble();
			B.changeEntry(row, col, val);
		}
		in.close();// close input file

		PrintWriter out = new PrintWriter(new FileWriter(args[1]));
		out.println("A has " + a + " non-zero entries:\n" + A);
		out.println("B has " + b + " non-zero entries:\n" + B);
		out.println("(1.5)*A = \n" + A.scalarMult(1.5));
		out.println("A+B = \n" + A.add(B));
		out.println("A+A = \n" + A.add(A));
		out.println("B-A = \n" + B.sub(A));
		out.println("A-A = \n" + A.sub(A));
		out.println("Transpose(A) = \n" + A.transpose());
		out.println("A*B = \n" + A.mult(B));
		out.println("B*B = \n" + B.mult(B));
		out.close();

	}// end of Main() program

}// end of class Sparse