import java.util.*;
import java.util.function.Consumer;

public class _A6D_Solution {
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
}
