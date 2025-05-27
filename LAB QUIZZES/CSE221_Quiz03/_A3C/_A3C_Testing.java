import java.util.*;
import java.io.*;

// Compile and run: javac _A3C_Testing.java && java _A3C_Testing
public class _A3C_Testing {
    public static Long N = 0L, A = 0L;
    public static Long res = 0L;

    public static Long solve(Long A, Long N) {
        Long res = 0L;
        Long MOD = 1000003L;
        // Place your code here

        return res;
    }

    public static void main(String args[]) throws Exception {
        // // file input
        // // BufferedReader fin = new BufferedReader(new
        // // FileReader("TimeLimitExceeded.txt"));
        // // BufferedReader fin = new BufferedReader(new FileReader("CustomTest.txt"));
        // BufferedReader fin = new BufferedReader(new FileReader("WrongAnswer.txt"));
        // for (int i = 1; i <= 2; ++i)
        // fin.readLine();
        // fin.skip(4);
        // A = Long.parseLong(fin.readLine());
        // fin.skip(4);
        // N = Long.parseLong(fin.readLine());
        // fin.close();

        // stdin
        // 100
        // 7
        BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
        String[] tempA = fin.readLine().split(" ");
        A = Long.parseLong(tempA[0]);
        tempA = fin.readLine().split(" ");
        A = Long.parseLong(tempA[0]);
        fin.close();

        // // hardcoded input
        // A = 100;
        // N = 7;

        long start = System.nanoTime();
        res = solve(A, N);
        long finish = System.nanoTime();
        long elapsed = finish - start;

        // // file output
        // BufferedWriter fout = new BufferedWriter(new
        // FileWriter("OutputOfYourCode.txt"));
        // fout.write(res.toString());
        // fout.close();

        // stdout
        System.out.println(res);

        System.out.printf("Execution time for the targeted one test is %.9fs\n", elapsed * 1e-9);
        System.exit(0);
    }
}
