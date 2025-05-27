import java.util.*;
import java.io.*;

// Compile and run: javac _A6C_Testing.java && java _A6C_Testing
public class _A6C_Testing {
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
    public static Integer solve(Integer N, Integer X1, Integer Y1, Integer X2, Integer Y2) {
        Integer res = 0;
        // Place your code here
        return res;
    }

    public static void main(String args[]) throws Exception {
        // stdin
        // 4
        // 1 1
        // 3 4
        // 
        // BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
        // String[] tempA = fin.readLine().split(" ");
        // int N = Integer.parseInt(tempA[0]);
        // tempA = fin.readLine().split(" ");
        // int X1 = Integer.parseInt(tempA[0]);
        // int Y1 = Integer.parseInt(tempA[1]);
        // tempA = fin.readLine().split(" ");
        // int X2 = Integer.parseInt(tempA[0]);
        // int Y2 = Integer.parseInt(tempA[1]);


        // // hardcoded input
        int N = 4;
        int X1 = 1, Y1 = 1;
        int X2 = 3, Y2 = 4;
        

        long start = System.nanoTime();
        Integer res = solve(N, X1, Y1, X2, Y2);
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
