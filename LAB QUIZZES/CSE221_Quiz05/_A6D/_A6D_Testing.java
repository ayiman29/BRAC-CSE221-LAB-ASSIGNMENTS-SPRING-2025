import java.util.*;
import java.io.*;

// Compile and run: javac _A6D_Testing.java && java _A6D_Testing
public class _A6D_Testing {
    public static class Pair<K, V> {
        public K key;
        public V value;

        public Pair(K key, V value) {
            this.key = key;
            this.value = value;
        }

        public String toString() {
            return "(" + key + ", " + value + ")";
        }
    }
    public static ArrayList<Integer> solve(Integer N, int R, ArrayList<Pair<Integer, Integer>> edges) {
        ArrayList<Integer> res = new ArrayList<>();
        for (int i = 0; i <= N; i++) {
            res.add(0);
        }
        // Place your code here

        return res;
    }

    public static void main(String args[]) throws Exception {
        // stdin
        // 4 1
        // 3 1
        // 4 1
        // 1 2
        // 
        // BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
        // String[] tempA = fin.readLine().split(" ");
        // int N = Integer.parseInt(tempA[0]);
        // int R = Integer.parseInt(tempA[1]);
        //
        // ArrayList<Pair<Integer, Integer>> edges = new ArrayList<>();
        //   
        // for(int i = 0; i < N - 1; i++){
        //     tempA = fin.readLine().split(" ");
        //     int u = Integer.parseInt(tempA[0]);
        //     int v = Integer.parseInt(tempA[1]);
        //     edges.add(new Pair<>(u, v));
        // }
        // fin.close();


        // // hardcoded input
        int N = 4, R = 1;
        ArrayList<Pair<Integer, Integer>> edges = new ArrayList<>();
        edges.add(new Pair<>(3, 1));
        edges.add(new Pair<>(4, 1));
        edges.add(new Pair<>(1, 2)); 
        

        long start = System.nanoTime();
        ArrayList<Integer> res = solve(N, R, edges);
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
