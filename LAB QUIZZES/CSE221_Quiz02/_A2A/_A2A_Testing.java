import java.util.*;
import java.io.*;

// Compile and run: javac _A2A_Testing.java && java _A2A_Testing
class _A2A_Solution {
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

    public static Pair<Integer, Integer> solve(Integer N, Integer S, ArrayList<Integer> A) {
        Integer I = 0, J = 0;
        // Place your code here
        return new Pair<>(I, J);
    }
}

public class _A2A_Testing {
    Random rng = new Random();
    public static Integer N = 0, S = 0;
    public static ArrayList<Integer> A = new ArrayList<>();
    public static _A2A_Solution.Pair<Integer, Integer> res;

    public static void main(String args[]) throws Exception {
        // // stdin
        // // 4 10
        // // 1 3 5 7
        BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
        String[] temp2 = fin.readLine().split(" ");
        N = Integer.parseInt(temp2[0]);
        S = Integer.parseInt(temp2[1]);
        for (String temp : fin.readLine().split(" "))
            A.add(Integer.parseInt(temp));

        // // hardcoded input
        // N = 4
        // S = 10
        // A = new ArrayList<Integer>({1, 3, 5, 7});

        long start = System.nanoTime();
        res = _A2A_Solution.solve(N, S, new ArrayList(A));
        long finish = System.nanoTime();
        long elapsed = finish - start;

        // stdout
        System.out.println(res.toString());

        System.out.printf("Execution time for the targeted one test is %.9fs\n", elapsed * 1e-9);
        System.exit(0);

        // // file input
        // BufferedReader fin = new BufferedReader(new
        // FileReader("TimeLimitExceeded.txt"));
        // BufferedReader fin = new BufferedReader(new FileReader("CustomTest.txt"));
        // BufferedReader fin = new BufferedReader(new FileReader("WrongAnswer.txt"));
        // for (int i = 1; i <= 2; ++i)
        // fin.readLine();
        // N = Integer.parseInt(fin.readLine().split(" ")[2]);
        // S = Integer.parseInt(fin.readLine().split(" ")[2]);
        // String[] temp = fin.readLine().split(" ");
        // for(int i = 0; i < N; i++){
        // if(i == 0)
        // A.add(Integer.parseInt(temp[2].substring(1, temp[2].length() - 1)));
        // else
        // A.add(Integer.parseInt(temp[i + 2].substring(0, temp[i + 2].length() - 1)));
        // }
        // fin.close();

        // // file output
        // BufferedWriter fout = new BufferedWriter(new
        // FileWriter("OutputOfYourCode.txt"));
        // fout.write(res.toString());
        // fout.close();
    }
}
