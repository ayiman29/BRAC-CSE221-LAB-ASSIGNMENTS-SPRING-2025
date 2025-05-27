import java.util.*;
import java.io.*;

// Compile and run: javac _412_Solution.java _412_Testing.java && java _412_Testing
public class _412_Testing {
    public static int N = 0, M = 0, initX = -1, initY = -1;
    public static ArrayList<_412_Solution.Pair<Integer, Integer>> arr = new ArrayList<>();
    public static int res;
    public static int solve(int N, int initX, int initY, ArrayList<_412_Solution.Pair<Integer,Integer>> arr) {
        int M = arr.size();
        int ans = -1;
        // Place your code here
        
        return ans;
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
        // 4 3
        // 1 3
        // 2 3
        // 1 1
        // 3 4 
        BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
        String[] tempA = fin.readLine().split(" ");
        N = Integer.parseInt(tempA[0]);
        M = Integer.parseInt(tempA[1]);
        String[] tempB = fin.readLine().split(" ");
        initX = Integer.parseInt(tempB[0]);
        initY = Integer.parseInt(tempB[1]);
        for (int i = 0; i<M; i++){
            String[] temp = fin.readLine().split(" ");
            int first = Integer.parseInt(temp[0]);
            int second = Integer.parseInt(temp[1]);
            _412_Solution.Pair<Integer, Integer> pair = new _412_Solution.Pair<>(first, second);
            arr.add(pair);
        }
        fin.close();

        // // hardcoded input
        // list1 = new ArrayList<>(Arrays.asList(1, 2, 2, 3, 4));
        // list2 = new ArrayList<>(Arrays.asList(2, 2, 3, 3, 5, 6));

        long start = System.nanoTime();
        res = solve(N, initX, initY, new ArrayList<>(arr));
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
