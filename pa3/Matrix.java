// Matrix.java
// Eric Yup
// eyup@ucsc.edu 
// pa3
// doubly linked list ADT
class Matrix {
	private class Entry {
		private int col;
		private double val;

		Entry(int c, double v) {
			col = c;
			val = v;
		}

		public boolean equals(Object x) {
			if (x instanceof Entry) {
				Entry E = (Entry) x;
				if (this.col == E.col && this.val == E.val)
					return true;
			}
			return false;
		}

		public String toString() {
			return ("(" + col + ", " + val + ")");
		}
	}

	private int size;
	private int NNZ;
	private List[] row;

	// Constructor
	Matrix(int n) {
		if (!(n >= 1)) {
			throw new RuntimeException("Error: Matrix() called on invalid Matrix size");
		}
		size = n;
		NNZ = 0;
		row = new List[size + 1];
		for (int i = 0; i < size + 1; i++) {
			row[i] = new List();
		}
	}

	// Makes a new n x n zero Matrix. pre: n>=1
	// Access functions
	int getSize() {
		return size;
	} // Returns n, the number of rows and columns of this Matrix

	int altSize() {
		return size + 1;
	} // formats matrix with first extra row at index 0

	int getNNZ() {
		return NNZ;
	} // Returns the number of non-zero entries in this Matrix

	public boolean equals(Object x) {
		if (x instanceof Matrix) {
			Matrix M = (Matrix) x;
			if (!(M.altSize() == this.altSize()) || (M.getNNZ() != this.getNNZ())) {
				return false;
			}
			for (int i = 0; i < altSize(); i++) {
				if (this.row[i].equals(M.row[i]) == false)
					return false;
			}
			return true;
		} else
			return false;
	}
	// overrides Object's equals() method
	// Manipulation procedures

	void makeZero() {
		for (int i = 0; i < altSize(); i++) {
			row[i].clear();
		}
		this.NNZ = 0;
	}

	// sets this Matrix to the zero state
	Matrix copy() {
		Matrix C = new Matrix(this.getSize());
		for (int i = 0; i < this.altSize(); i++) {
			C.row[i] = row[i].copy();
		}
		C.NNZ = this.NNZ;
		return C;
	}

	// returns a new Matrix having the same entries as this Matrix
	void changeEntry(int i, int j, double x) {
		if (!(1 <= i && i <= this.altSize())) {
			throw new RuntimeException("Error: changeEntry() called on invalid row");
		}
		if (!(1 <= j && j <= this.altSize())) {
			throw new RuntimeException(" Error: changeEntry() called on invalid column");
		}
		Entry E = new Entry(j, x);
		if (x != 0) {
			if (row[i].length() > 0) {
				for (row[i].moveFront(); row[i].index() >= 0; row[i].moveNext()) {
					Entry temp = (Entry) row[i].get();
					if (temp.col == j) {
						row[i].delete();
						NNZ--;
						break;
					}
				}
				boolean flag = false;
				for (row[i].moveFront(); row[i].index() >= 0; row[i].moveNext()) {
					Entry temp = (Entry) row[i].get();
					if (j < temp.col) {
						row[i].insertBefore(E);
						NNZ++;
						flag = true;
						break;
					}
				}
				if (flag == false) {
					row[i].append(E);
					NNZ++;
				}
			} else {
				row[i].append(E);
				NNZ++;
			}
		}
		if (x == 0) {
			if (row[i].length() > 0) {
				for (row[i].moveFront(); row[i].index() >= 0; row[i].moveNext()) {
					Entry temp = (Entry) row[i].get();
					if (temp.col == j && (int) temp.val != 0) {
						row[i].delete();
						NNZ--;
						break;
					}
				}
			}
		}
	}

	// changes ith row, jth column of this Matrix to x
	// pre: 1<=i<=altSize(), 1<=j<=altSize()
	Matrix scalarMult(double x) {
		Entry E;
		Matrix S = new Matrix(this.getSize());
		// S.NNZ = this.NNZ;
		for (int i = 0; i < this.altSize(); i++) {
			for (row[i].moveFront(); row[i].index() >= 0; row[i].moveNext()) {
				E = (Entry) row[i].get();
				S.changeEntry(i, E.col, (E.val) * x);
			}
		}
		return S;
	}

	// returns a new Matrix that is the scalar product of this Matrix with x
	Matrix add(Matrix M) {
		if (!(this.altSize() == M.altSize())) {
			throw new RuntimeException("Matrix Error: add() called on Matrices of different size");
		}
		Matrix A = new Matrix(this.getSize());// Addition matrix to be returned
		if (this.equals(M))
			return this.scalarMult(2);// If the matrices are equal, return 2M

		for (int i = 1; i < altSize(); i++) {
			if (this.row[i].length() > 0 && M.row[i].length() == 0) {
				this.row[i].moveFront();
				while (this.row[i].index() >= 0) {
					Entry temp = (Entry) row[i].get();
					A.changeEntry(i, temp.col, temp.val);
					this.row[i].moveNext();
				}
			}
			if (M.row[i].length() > 0 && this.row[i].length() == 0) {
				M.row[i].moveFront();
				while (M.row[i].index() >= 0) {
					Entry tempM = (Entry) M.row[i].get();
					A.changeEntry(i, tempM.col, tempM.val);
					M.row[i].moveNext();
				}
			}
			if (this.row[i].length() > 0 && M.row[i].length() > 0) {
				this.row[i].moveFront();
				M.row[i].moveFront();
				while (this.row[i].index() >= 0 && M.row[i].index() >= 0) {
					Entry temp = (Entry) row[i].get();
					Entry tempM = (Entry) M.row[i].get();
					if (temp.col == tempM.col) {
						A.changeEntry(i, temp.col, (temp.val + tempM.val));
						this.row[i].moveNext();
						M.row[i].moveNext();
					} else if (temp.col < tempM.col) {
						A.changeEntry(i, temp.col, temp.val);
						this.row[i].moveNext();
					} else if (temp.col > tempM.col) {
						A.changeEntry(i, tempM.col, tempM.val);
						M.row[i].moveNext();
					}
				}
				if (this.row[i].index() >= 0 && M.row[i].index() < 0) {
					while (this.row[i].index() >= 0) {
						Entry temp = (Entry) row[i].get();
						A.changeEntry(i, temp.col, temp.val);
						this.row[i].moveNext();
					}
				}
				if (M.row[i].index() >= 0 && this.row[i].index() < 0) {
					while (M.row[i].index() >= 0) {
						Entry tempM = (Entry) M.row[i].get();
						A.changeEntry(i, tempM.col, tempM.val);
						M.row[i].moveNext();
					}
				}
			} // end of both matrix have row i
		}
		return A;
	}

	// returns a new Matrix that is the sum of this Matrix with M
	// pre: getSize()==M.getSize()
	Matrix sub(Matrix M) {
		if (!(altSize() == M.altSize())) {
			throw new RuntimeException("Matrix Error: add() called on Matrices of different size");
		}
		Matrix negM = M.scalarMult(-1);// Multiply M.matrix by scalar (-1)
		Matrix difference = this.add(negM);
		return difference;
	}

	// returns a new Matrix that is the difference of this Matrix with M
	// pre: getSize()==M.getSize()
	Matrix transpose() {
		Matrix T = new Matrix(this.getSize());
		for (int i = 0; i < this.altSize(); i++) {
			for (row[i].moveFront(); row[i].index() >= 0; row[i].moveNext()) {
				Entry temp = (Entry) row[i].get();
				T.changeEntry(temp.col, i, temp.val);
			}
		}
		return T;
	}

	// returns a new Matrix that is the transpose of this Matrix
	private static double dot(List P, List Q) {
		double dotVal = 0;

		for (P.moveFront(); P.index() >= 0; P.moveNext()) {
			Entry eP = (Entry) P.get();
			for (Q.moveFront(); Q.index() >= 0; Q.moveNext()) {

				Entry eQ = (Entry) Q.get();
				if (eP.col == eQ.col) {
					dotVal = dotVal + (eP.val * eQ.val);
					break;
				}
			}
		}
		return dotVal;
	}

	Matrix mult(Matrix M) {
		if (!(altSize() == M.altSize())) {
			throw new RuntimeException("Matrix Error: mult() called on Matrices of different size");
		}
		Matrix mult = new Matrix(this.getSize());
		Matrix Mtranspose = M.transpose();
		for (int i = 1; i < this.altSize(); i++) {
			for (int j = 1; j < Mtranspose.altSize(); j++) {
				mult.changeEntry(i, j, dot(this.row[i], Mtranspose.row[j]));
			}
		}
		return mult;
	}

	// returns a new Matrix that is the product of this Matrix with M
	// pre: getSize()==M.getSize()
	// Other functions
	public String toString() {
		String s = "";
		for (int i = 0; i < size + 1; i++) {
			if (this.row[i].length() > 0) {// If a non-empty row is found, then
											// print row
				s = s + String.valueOf(i) + ": " + row[i] + "\n";

			}
		}
		return s;
	}
	// overrides Object's toString() method
}