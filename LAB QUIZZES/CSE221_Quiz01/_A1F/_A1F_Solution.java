import java.util.*;

public class _A1F_Solution {
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