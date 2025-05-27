import java.io.*;
import java.util.*;

// Compile and run: javac _A1F_Testing.java && java _A1F_Testing

class _A1F_Solution {
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

    public static Pair<Integer, ArrayList<Pair<Integer, Integer>>> solve(ArrayList<Integer> sIDs,
            ArrayList<Integer> sMarks) {
        int N = sIDs.size(), cnt = 0;
        ArrayList<Pair<Integer, Integer>> arr = new ArrayList<>();
        // Place your code here
        return new Pair<>(cnt, arr);
    }
}

public class _A1F_Testing {
    Random rng = new Random();
    public static int N = 0;
    public static ArrayList<Integer> sIDs = new ArrayList<>(), sMarks = new ArrayList<>();
    public static _A1F_Solution.Pair<Integer, ArrayList<_A1F_Solution.Pair<Integer, Integer>>> res;

    public static void main(String args[]) throws Exception {
        // // stdin
        // // 7
        // // 7 4 9 3 2 5 1
        // // 40 50 50 20 10 10 10
        BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
        N = Integer.parseInt(fin.readLine().replace("\\s", ""));
        for (String temp : fin.readLine().split(" "))
        sIDs.add(Integer.parseInt(temp));
        for (String temp : fin.readLine().split(" "))
        sMarks.add(Integer.parseInt(temp));


        long start = System.nanoTime();
        res = _A1F_Solution.solve(new ArrayList<>(sIDs), new ArrayList<>(sMarks));
        long finish = System.nanoTime();
        long elapsed = finish - start;


        // // stdout
        // System.out.println(sIDs.toString());

        System.out.printf("Execution time for the targeted one test is %.9fs\n", elapsed * 1e-9);
        System.exit(0);

        // // file input
        // BufferedReader fin = new BufferedReader(new
        // FileReader("TimeLimitExceeded.txt"));
        // BufferedReader fin = new BufferedReader(new FileReader("CustomTest.txt"));
        // BufferedReader fin = new BufferedReader(new FileReader("WrongAnswer.txt"));
        // for (int i = 1; i <= 3; ++i)
        //     fin.readLine();
        // fin.skip(8);
        // for (String temp : fin.readLine().replace("]", "").split(", "))
        //     sIDs.add(Integer.parseInt(temp));
        // fin.skip(10);
        // for (String temp : fin.readLine().replace("]", "").split(", "))
        //     sIDs.add(Integer.parseInt(temp));
        // fin.close();

        // // hardcoded input
        // sIDs = new ArrayList<>(Arrays.asList(7, 4, 9, 3, 2, 5, 1));
        // sMarks = new ArrayList<>(Arrays.asList(40, 50, 50, 20, 10, 10, 10));

        
        // // file output
        // BufferedWriter fout = new BufferedWriter(new FileWriter("OutputOfYourCode.txt"));
        // fout.write(sIDs.toString());
        // fout.close();
    }
}