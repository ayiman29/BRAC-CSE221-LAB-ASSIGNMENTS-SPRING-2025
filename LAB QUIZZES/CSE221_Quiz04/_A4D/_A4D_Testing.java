import java.util.*;
import java.io.*;

// Compile and run: javac _A4D_Testing.java && java _A4D_Testing
public class _A4D_Testing {

    public static boolean solve(Integer N, ArrayList<_A4D_Solution.Pair<Integer, Integer>> edges) {
        boolean res = true;
        // Place your code here
        
        return res;
    }

    public static void main(String args[]) throws Exception {
        // stdin
        // 3 2
        // 0 1
        // 1 2
        // int N, M;
        // cin >> N >> M;
        // BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
        // String[] tempA = fin.readLine().split(" ");
        // int N = Integer.parseInt(tempA[0]);
        // int M = Integer.parseInt(tempA[1]);
        
        // ArrayList<_A4D_Solution.Pair<Integer, Integer>> edges = new ArrayList<>();
            
        // for(int i = 0; i < M; i++){
        //     tempA = fin.readLine().split(" ");
        //     int u = Integer.parseInt(tempA[0]);
        //     int v = Integer.parseInt(tempA[1]);
        //     edges.add(_A4D_Solution.Pair<Integer, Integer>(u, v));
        // }
        // fin.close();


        // // hardcoded input
        int N = 5;
        ArrayList<_A4D_Solution.Pair<Integer, Integer>> edges = new ArrayList<>();
        edges.add(new _A4D_Solution.Pair<Integer, Integer>(0, 1));
        edges.add(new _A4D_Solution.Pair<Integer, Integer>(0, 2));
        edges.add(new _A4D_Solution.Pair<Integer, Integer>(0, 3));
        edges.add(new _A4D_Solution.Pair<Integer, Integer>(2, 3));
        edges.add(new _A4D_Solution.Pair<Integer, Integer>(2, 4));
        edges.add(new _A4D_Solution.Pair<Integer, Integer>(3, 4));
        

        long start = System.nanoTime();
        boolean res = solve(N, edges);
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
