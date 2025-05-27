import java.util.*;
import java.io.*;

// Compile and run: javac _311_Solution.java _311_Testing.java && java _311_Testing
public class _311_Testing {
    public static int N = 0, M = 0;
    public static ArrayList<Integer> arr = new ArrayList<>();
    public static int res;
    public static int solve(ArrayList<Integer> arr) {
        int N = arr.size();
        int res = -1;
        // Place your code here
        return res;
    }

    public static void main(String args[]) throws Exception {
        // // file input
        // // BufferedReader fin = new BufferedReader(new
        // // FileReader("TimeLimitExceeded.txt"));
        // // BufferedReader fin = new BufferedReader(new FileReader("CustomTest.txt"));
        // BufferedReader fin = new BufferedReader(new FileReader("WrongAnswer.txt"));
        // for (int i = 1; i <= 4; ++i)
        // fin.readLine();
        // fin.skip(9);
        // for (String temp : fin.readLine().replace("]", "").split(", "))
        // list1.add(Integer.parseInt(temp));
        // fin.skip(9);
        // for (String temp : fin.readLine().replace("]", "").split(", "))
        // list2.add(Integer.parseInt(temp));
        // fin.close();

        // stdin
        // 5 
        // 4 2 1 5 3
        BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
        String[] tempA = fin.readLine().split(" ");
        N = Integer.parseInt(tempA[0]);
        for (String temp : fin.readLine().split(" "))
            arr.add(Integer.parseInt(temp));
        fin.close();

        // // hardcoded input
        // list1 = new ArrayList<>(Arrays.asList(1, 2, 2, 3, 4));
        // list2 = new ArrayList<>(Arrays.asList(2, 2, 3, 3, 5, 6));

        long start = System.nanoTime();
        res = solve(new ArrayList<>(arr));
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
