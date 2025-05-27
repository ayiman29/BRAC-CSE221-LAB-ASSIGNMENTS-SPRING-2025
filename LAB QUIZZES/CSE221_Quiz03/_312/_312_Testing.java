import java.util.*;
import java.io.*;

// Compile and run: javac _312_Solution.java _312_Testing.java && java _312_Testing
public class _312_Testing {
    public static int N = 0;
    public static ArrayList<Integer> preOrder = new ArrayList<>(), postOrder = new ArrayList<>(), result;

    public static ArrayList<Integer> solve(ArrayList<Integer> preOrder, ArrayList<Integer> postOrder) {
        int N = preOrder.size();
        ArrayList<Integer> result = new ArrayList<>();
        // Place your code here
        return result;
    }

    public static void main(String args[]) throws Exception {
        // // file input
        // // BufferedReader fin = new BufferedReader(new
        // // FileReader("TimeLimitExceeded.txt"));
        // // BufferedReader fin = new BufferedReader(new FileReader("CustomTest.txt"));
        // BufferedReader fin = new BufferedReader(new FileReader("WrongAnswer.txt"));
        // for (int i = 1; i <= 3; ++i)
        // fin.readLine();
        // fin.skip(12);
        // for (String temp : fin.readLine().replace("]", "").split(", "))
        // preOrder.add(Integer.parseInt(temp));
        // fin.skip(13);
        // for (String temp : fin.readLine().replace("]", "").split(", "))
        // postOrder.add(Integer.parseInt(temp));
        // fin.close();

        // stdin
        // 5
        // 3 9 20 15 7
        // 9 15 7 20 3
        BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
        String[] tempA = fin.readLine().split(" ");
        N = Integer.parseInt(tempA[0]);
        for (String temp : fin.readLine().split(" "))
            preOrder.add(Integer.parseInt(temp));
        for (String temp : fin.readLine().split(" "))
            postOrder.add(Integer.parseInt(temp));
        fin.close();

        // // hardcoded input
        // preOrder = new ArrayList<>(Arrays.asList(3, 9, 20, 15, 7));
        // postOrder = new ArrayList<>(Arrays.asList(9, 15, 7, 20, 3));

        long start = System.nanoTime();
        result = solve(new ArrayList<>(preOrder), new ArrayList<>(preOrder));
        long finish = System.nanoTime();
        long elapsed = finish - start;

        // // file output
        // BufferedWriter fout = new BufferedWriter(new
        // FileWriter("OutputOfYourCode.txt"));
        // fout.write(result.toString());
        // fout.close();

        // stdout
        System.out.println(result);

        System.out.printf("Execution time for the targeted one test is %.9fs\n", elapsed * 1e-9);
        System.exit(0);
    }
}
