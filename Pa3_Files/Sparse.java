/**
 * Name: Garland Simpson
 * Cruzid: gfsimpso
 * Assignment: pa3
 */

import java.util.Scanner;
import java.io.File;
import java.io.*;

public class Sparse {

    public static void main(String[] args) throws IOException
    {
        Scanner in = null;
        PrintWriter out = null;

        int n;
        int a;
        int b;

        if(args.length < 2)
        {
            System.err.println("Usage: FileIO infile outfile");
            System.exit(1);
        }

        in = new Scanner(new File(args[0]));
        out = new PrintWriter(new FileWriter(args[1]));

        n = in.nextInt();
        a = in.nextInt();
        b = in.nextInt();

        int i;
        int j;
        double d;

        int idxA = 0;
        int idxB = 0;

        Matrix A = new Matrix(n);
        Matrix B = new Matrix(n);

        while(idxA < a) {

            i = in.nextInt();
            j = in.nextInt();
            d = in.nextDouble();

            A.changeEntry(i,j,d);

            idxA++;
        }
        while(idxB < b) {

            i = in.nextInt();
            j = in.nextInt();
            d = in.nextDouble();

            B.changeEntry(i,j,d);

            idxB++;
        }

        out.println("A has " + A.getNNZ() + " non-zero entries:");
        out.println(A);

        out.println("B has " + B.getNNZ() + " non-zero entries:");
        out.println(B);

        out.println("(1.5)*A =");
        Matrix C = A.scalarMult(1.5);
        out.println(C);

        out.println("A+B =");
        Matrix D = A.add(B);
        out.println(D);

        out.println("A+A =");
        Matrix E = A.add(A);
        out.println(E);

        out.println("B-A =");
        Matrix F = B.sub(A);
        out.println(F);

        out.println("A-A =");
        Matrix G = A.sub(A);
        out.println(G);

        out.println("Transpose(A) =");
        Matrix H = A.transpose();
        out.println(H);

        out.println("A*B =");
        Matrix I = A.mult(B);
        out.println(I);

        out.println("B*B =");
        Matrix J = B.mult(B);
        out.println(J);


        in.close();
        out.close();
    }
}