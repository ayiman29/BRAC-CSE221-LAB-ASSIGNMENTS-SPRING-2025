import java.util.*;
import java.io.*;

// Compile and run: javac _712_Testing.java && java _712_Testing
public class _712_Testing {
    public static int N = 0, A = 0, M = 0, S = 0, K = 0, D = 0;
    public static int res = 0;
    public static ArrayList<ArrayList<Integer>> edges;
    public static ArrayList<Integer> u, v, w;   
    public static int solve(int N, int M, int S, int D, int K, ArrayList<ArrayList<Integer> > edges) {
        int res = 0;
        // Place your code here
        
        return res;
    }

    public static void main(String args[]) throws Exception {
        /*
        stdin
        7 10 3 7 5
        2 3 1
        2 4 1
        4 3 6
        4 1 2
        1 7 2
        4 5 3
        5 7 8
        4 7 1
        5 6 4
        6 7 2
        */

        BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
        String[] nums = fin.readLine().split(" ");
        N = Integer.parseInt(nums[0]);
        M = Integer.parseInt(nums[1]);
        S = Integer.parseInt(nums[2]);
        D = Integer.parseInt(nums[3]);
        K = Integer.parseInt(nums[4]);

        u = new ArrayList<>();
        v = new ArrayList<>();
        w = new ArrayList<>();
        edges = new ArrayList<>();
        for(int i = 0; i < M; i++)
        {
            String[] temp = fin.readline().split(" ");
            u.add(Integer.parseInt(temp[0]));
            v.add(Integer.parseInt(temp[1]));
            w.add(Integer.parseInt(temp[2]));
            ArrayList<Integer> ed = new ArrayList<>(Arrays.asList(u.get(i),v.get(i),w.get(i)));
            edges.add(ed);
        }
        fin.close();

        long start = System.nanoTime();
        int result = solve(N, M, S, D, K, edges);
        long finish = System.nanoTime();
        long elapsed = finish - start;

        // // file output
        // BufferedWriter fout = new BufferedWriter(new
        // FileWriter("OutputOfYourCode.txt"));
        // fout.write(res.toString());
        // fout.close();

        // stdout
        System.out.println(result);
    
        System.out.printf("Execution time for the targeted one test is %.9fs\n", elapsed * 1e-9);
        System.exit(0);
    }
}
