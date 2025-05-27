import java.util.*;
import java.io.*;

// Compile and run: javac _A7E_Testing.java && java _A7E_Testing
public class _A7E_Testing {
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
    public static Long solve(int N, int M, ArrayList<Integer> Us, ArrayList<Integer> Vs, ArrayList<Integer> Ws) {
        Long res = -1L;
        // Place your code here
        return res;
    }

    public static void main(String args[]) throws Exception {
        // stdin
        // 4 3
        // 1 4 3
        // 3 4 4
        // 2 3 5
        // 
        // BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
        // String[] tempA = fin.readLine().split(" ");
        // int N = Integer.parseInt(tempA[0]);
        // int M = Integer.parseInt(tempA[1]);
        //
        // ArrayList<Integer> Us = new ArrayList<>();
        // ArrayList<Integer> Vs = new ArrayList<>();
        // ArrayList<Integer> Ws = new ArrayList<>();
        // for(int i = 0; i < M; i++){
        //     tempA = fin.readLine().split(" ");
        //     int u = Integer.parseInt(tempA[0]);
        //     int v = Integer.parseInt(tempA[1]);
        //     int w = Integer.parseInt(tempA[2]);
        //     Us.add(u);
        //     Vs.add(v);
        //     Ws.add(w);
        // }
        // fin.close();


        // // hardcoded input
        int N = 4, M = 3;
        ArrayList<Integer> Us = new ArrayList<>(Arrays.asList(1, 3, 2));
        ArrayList<Integer> Vs = new ArrayList<>(Arrays.asList(4, 4, 3));
        ArrayList<Integer> Ws = new ArrayList<>(Arrays.asList(3, 4, 5));

        long start = System.nanoTime();
        Long res = solve(N, M, Us, Vs, Ws);
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
