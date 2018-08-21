/**
 * Name: Garland Simpson
 * Cruzid: 
 * Assignment: pa1
 */
import java.io.*;
import java.util.ArrayList;
import java.util.Scanner;
import java.io.File;

public class Lex
{
    public static void main(String[] args) throws IOException
    {
        Scanner in = null;
        PrintWriter out = null;
        String line;
        ArrayList<String> token = new ArrayList<>();
        int n = 0;
        int i = 0;

        if(args.length < 2)
        {
            System.err.println("Usage: FileIO infile outfile");
            System.exit(1);
        }

        in = new Scanner(new File(args[0]));
        out = new PrintWriter(new FileWriter(args[1]));

        List myList = new List();



        while( in.hasNextLine() )
        {
            n++;
            line = in.nextLine();
            token.add(i, line);
            i++;
        }

        myList.append(0);

        for(i = 1; i < n; i++)
        {
            for(myList.moveFront(); myList.index() >= 0; myList.moveNext())
            {
                if (token.get(i).compareTo(token.get(myList.get())) < 0)
                {
                    myList.insertBefore(i);
                    break;
                }
            }

            if (myList.index() == -1)
                myList.append(i);
        }

        for(myList.moveFront(); myList.index() >= 0; myList.moveNext())
        {
            out.println(token.get(myList.get()));
        }

        in.close();
        out.close();
    }
}
