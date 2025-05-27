import java.io.*;
import java.util.*;

// Compile and run: javac _A1E_Testing.java && java _A1E_Testing
class _A1E_Solution {
    public static ArrayList<Integer> solve(ArrayList<Integer> arr) {
        // Change the given code
        for (int i = 0; i < arr.size(); ++i)
            for (int j = 0; j < arr.size() - i - 1; ++j)
                if (arr.get(j) > arr.get(j + 1))
                    Collections.swap(arr, j, j + 1);
        return arr;
    }
}
public class _A1E_Testing {
    Random rng = new Random();
    public static int N = 0;
    public static ArrayList<Integer> arr = new ArrayList<>(), res = new ArrayList<>();

    public static void main(String args[]) throws Exception {
        // stdin
        // 5
        // 3 2 1 4 5
        BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
        N = Integer.parseInt(fin.readLine().replace("\\s", ""));
        for (String temp : fin.readLine().split(" "))
        arr.add(Integer.parseInt(temp));

        long start = System.nanoTime();
        res = _A1E_Solution.solve(new ArrayList<>(arr));
        long finish = System.nanoTime();
        long elapsed = finish - start;

        // // stdout
        // System.out.println(arr.toString());

        System.out.printf("Execution time for the targeted one test is %.9fs\n", elapsed * 1e-9);
        System.exit(0);
 
        // // file input
        // BufferedReader fin = new BufferedReader(new
        // FileReader("TimeLimitExceeded.txt"));
        // BufferedReader fin = new BufferedReader(new FileReader("CustomTest.txt"));
        // BufferedReader fin = new BufferedReader(new FileReader("WrongAnswer.txt"));
        // for (int i = 1; i <= 3; ++i)
        //     fin.readLine();
        // fin.skip(7);
        // for (String temp : fin.readLine().replace("]", "").split(", "))
        //     arr.add(Integer.parseInt(temp));
        // fin.close();

        // // hardcoded input
        // arr = new ArrayList<>(Arrays.asList(3, 2, 1, 4, 5));

        
        // // file output
        // BufferedWriter fout = new BufferedWriter(new FileWriter("OutputOfYourCode.txt"));
        // fout.write(arr.toString());
        // fout.close();

 
    }
}