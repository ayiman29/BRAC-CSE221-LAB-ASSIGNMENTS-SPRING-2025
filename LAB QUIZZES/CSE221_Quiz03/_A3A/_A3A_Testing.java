import java.util.*;
import java.io.*;

// Compile and run: javac _A3A_Testing.java && java _A3A_Testing
public class _A3A_Testing {
    public static int N = 0;
    public static ArrayList<Integer> A = new ArrayList<>();
    public static Long res = 0L;

    public static Long solve(ArrayList<Integer> A) {
        int N = A.size();
        Long res = 0L;
        // Place your code here
        return res;
    }

    public static void main(String args[]) throws Exception {
        // // file input
        // // BufferedReader fin = new BufferedReader(new
        // // FileReader("TimeLimitExceeded.txt"));
        // // BufferedReader fin = new BufferedReader(new FileReader("CustomTest.txt"));
        // BufferedReader fin = new BufferedReader(new FileReader("WrongAnswer.txt"));
        // for (int i = 1; i <= 3; ++i)
        // fin.readLine();
        // fin.skip(5);
        // for (String temp : fin.readLine().replace("]", "").split(", "))
        // A.add(Integer.parseInt(temp));
        // fin.close();

        // stdin
        // 5
        // 1 2 5 4 3
        BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
        String[] tempA = fin.readLine().split(" ");
        N = Integer.parseInt(tempA[0]);
        for (String temp : fin.readLine().split(" "))
            A.add(Integer.parseInt(temp));
        fin.close();

        // // hardcoded input
        // N = 5;
        // A = new ArrayList<>(Arrays.asList(1, 2, 5, 4, 3));

        long start = System.nanoTime();
        res = solve(new ArrayList<>(A));
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
