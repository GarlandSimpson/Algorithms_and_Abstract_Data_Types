/**
 * Name: Garland Simpson
 * Cruzid: gfsimpso
 * Assignment: pa3
 */

public class Matrix {

    private List row[];
    private int length;
    private int nnz;
    // Constructor
    Matrix(int n) { // Makes a new n x n zero Matrix.  pre: n>=1

        if (n < 1) {
            throw new RuntimeException("Error in Matrix(n): n < 1");
        }
        else {
            row = new List[n + 1];

            length = n;
            nnz = 0;

            for(int i = 0; i <= length; i++) {

                this.row[i] = new List();
            }
        }
    }

    private class Entry {

        private int col;
        private double data;

        Entry(int theCol, double theData) {

            col = theCol;
            data = theData;
        }

        public boolean equals(Object x){
            boolean eq = false;
            Entry that;

            if (x instanceof Entry) {
                that = (Entry)x;
                eq = (this.data == that.data && this.col == that.col);
            }
            return eq;
        }

        public String toString() { return "(" + String.valueOf(col) +", " + String.valueOf(data) + ")"; }
    }

    // Access functions
    int getSize() {
        return length;
    } // Returns n, the number of rows and columns of this Matrix

    int getNNZ() {
        return nnz;
    } // Returns the number of non-zero entries in this Matrix

    public boolean equals(Object x) { // overrides Object's equals() method

        boolean eq = false;
        Matrix that;

        if (x instanceof Matrix ) {

            that = (Matrix)x;

            if (this.length == that.length) {

                for(int i = 0; i < this.length; i++) {

                    eq = this.row[i].equals(that.row[i]);
                    if (eq == false) return eq;
                }
            }
        }
        return eq;
    }

    // Manipulation procedures
    void makeZero() { // sets this Matrix to the zero state
        for(int i = 0; i < length; i++) {

            row[i].clear();
        }
        nnz = 0;
    }

    Matrix copy() {// returns a new Matrix having the same entries as this Matrix
        Matrix cpy = new Matrix(length);

        for(int i = 0; i < length; i++) {

            cpy.row[i].moveFront(); // this may not be needed
            for(this.row[i].moveFront(); this.row[i].index() >= 0; this.row[i].moveNext()) {
                cpy.row[i].append(this.row[i].get());
                cpy.row[i].moveNext();
            }
        }
        cpy.nnz = this.nnz;

        return cpy;
    }

    void changeEntry(int i, int j, double x) { // changes ith row, jth column of this Matrix to x

        Entry that = new Entry(j, x);


        if (this.row[i].length() > 0) {
            Entry f = (Entry)this.row[i].front();
            Entry b = (Entry)this.row[i].back();


            if (j < f.col) {
                if (x != 0.0) {
                    this.row[i].prepend(that);
                    nnz++;
                }
            }
            else if (j > b.col) {
                if (x != 0.0) {
                    this.row[i].append(that);
                    nnz++;
                }
            }
            else {

                // was while(this.row[i].index() <= j)
                while(this.row[i].index() <= j && this.row[i].index() > -1) {
                    this.row[i].moveNext();
                }
                // this is new too
                if (this.row[i].index() <= -1)
                    this.row[i].moveBack();

                if (this.row[i].index() != j && x != 0.0) {
                    nnz++;
                    this.row[i].insertBefore(that);
                }
                else {
                    if (x == 0.0) {
                        this.row[i].delete();
                    }
                    else {
                        f = (Entry)this.row[i].get();
                        f.data = x;
                    }

                }
            }
        }
        else if (this.row[i].length() == 0 && x != 0.0) {
            this.row[i].append(that);
            nnz++;
        }
    }

    // pre: 1<=i<=getSize(), 1<=j<=getSize()
    Matrix scalarMult(double x) { // returns a new Matrix that is the scalar product of this Matrix with x
        Matrix sclr = new Matrix(length);
        Entry that;

        for (int i = 1; i <= length; i++) {
            this.row[i].moveFront();

            while(this.row[i].index() >= 0) {
                that = (Entry)this.row[i].get();
                sclr.row[i].append(new Entry(that.col, that.data * x));
                this.row[i].moveNext();
            }
        }
        sclr.nnz = nnz;
        return sclr;
    }

    private List addRow(List P, List Q) {
        List newRow = new List();
        P.moveFront();
        Q.moveFront();
        Entry thatP;
        Entry thatQ;

        if (P.length() > 0 && Q.length() > 0) {

            while(P.index() >= 0 || Q.index() >= 0) {

                if (Q.index() >= 0 && P.index() >= 0) {
                    thatP = (Entry)P.get();
                    thatQ = (Entry) Q.get();

                    if (thatP.col == thatQ.col) {

                        if (thatP.data + thatQ.data != 0.0)
                            newRow.append(new Entry(thatP.col, thatP.data + thatQ.data));

                        Q.moveNext();
                        P.moveNext();
                    }
                    else if (thatP.col < thatQ.col) {
                        newRow.append(thatP);
                        P.moveNext();
                    }
                    else {
                        newRow.append(thatQ);
                        Q.moveNext();
                    }
                }
                else if (P.index() >= 0){
                    thatP = (Entry)P.get();
                    newRow.append(thatP);
                    P.moveNext();
                }
                else if (Q.index() >= 0) {
                    thatQ = (Entry)Q.get();
                    newRow.append(thatQ);
                    Q.moveNext();
                }
            }
        }
        return newRow;
    }

    // pre: getSize()==M.getSize()
    Matrix add(Matrix M) {// returns a new Matrix that is the sum of this Matrix with M

        if (getSize() != M.getSize()) {
            throw new RuntimeException("Error in Matrix: sub(M): getSize != M.getSize() ");
        }
        else {
            Matrix sum = new Matrix(length);
            int n = 0;

            if (this.equals(M)) {
                sum = scalarMult(2.0);
                n = nnz;
            }

            else {
                int r = 1;

                while(r <= length) {

                    if (M.row[r].length() > 0 && this.row[r].length() > 0) {
                        sum.row[r] = addRow(this.row[r], M.row[r]);
                    }
                    else if (this.row[r].length() > 0){
                        sum.row[r] = this.row[r];
                    }
                    else if (M.row[r].length() > 0) {
                        sum.row[r] = M.row[r];
                    }

                    n += sum.row[r].length();
                    r++;
                }
            }
            sum.nnz = n;
            return sum;
        }
    }

    // pre: getSize()==M.getSize()
    Matrix sub(Matrix M) { // returns a new Matrix that is the difference of this Matrix with M

        if (getSize() != M.getSize()) {
            throw new RuntimeException("Error in Matrix: sub(M): getSize != M.getSize() ");
        }
        else {
            Matrix diff;

            if (this.equals(M)) {
                diff = new Matrix(length);
            } else {
                M = M.scalarMult(-1.0);
                diff = add(M);
                diff.nnz = nnz;
            }
            return diff;
        }
    }

    private static double dot(List P, List Q) {
        double prod = 0.0;

        P.moveFront();
        Q.moveFront();
        Entry thatP;
        Entry thatQ;

        while(P.index() >= 0 && Q.index() >= 0) { // was just P.index() >= 0
            thatP = (Entry)P.get();
            thatQ = (Entry)Q.get();
            if (thatP.col < thatQ.col) {
                P.moveNext();
            }
            else if (thatP.col > thatQ.col) {
                Q.moveNext();
            }
            else {
                P.moveNext();
                Q.moveNext();
                prod += thatP.data * thatQ.data;
            }

        }
        return prod;
    }

    Matrix transpose() { // returns a new Matrix that is the transpose of this Matrix

        Matrix tramp = new Matrix(length);
        int i = 1;
        Entry that;

        while (i <= length) {

            this.row[i].moveFront();

            while (row[i].index() >= 0) {

                that = (Entry)row[i].get();
                tramp.changeEntry(that.col, i, that.data);
                row[i].moveNext();
            }
            i++;
        }

        tramp.nnz = nnz;
        return tramp;
    }

    Matrix mult(Matrix M) { // returns a new Matrix that is the product of this Matrix with M
        Matrix prodt = new Matrix(length);
        M = M.transpose();

        int n = 0;
        int i = 1;
        int j = 1;
        double d;


        row[i].moveFront();
        while (i < length) {

            if (j > length) {
                i++;
                j = 1;
            }

            if (this.row[i].length() > 0 && M.row[j].length() > 0) { // was M.row[i].length()

                d = dot(this.row[i], M.row[j]);

                if (d != 0.0) {
                    prodt.row[i].append(new Entry(j, d));
                    n++;
                }
            }
            j++;
            row[i].moveFront();
        }

        prodt.nnz = n;
        return prodt;
    }

    // Other functions
    public String toString() { // overrides Object's toString() method

        StringBuffer sb = new StringBuffer();

        int n = 0;
        int i = 1;

        while(n < nnz) {

            if (this.row[i].length() > 0 ) {
                sb.append(i + ": ");
                sb.append(this.row[i].toString());
                sb.append('\n');
                n += this.row[i].length();
            }
            i++;

        }
        return new String(sb);
    }
}