import java.util.*;

public class _412_Solution {
    public static class Pair<K, V> {
        private final K first;
        private final V second;
        
        public Pair(K first, V second) {
            this.first = first;
            this.second = second;
        }
        
        public K getFirst() {
            return first;
        }
        
        public V getSecond() {
            return second;
        }
        
        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;
            Pair<?, ?> pair = (Pair<?, ?>) o;
            return Objects.equals(first, pair.first) && Objects.equals(second, pair.second);
        }
        
        @Override
        public int hashCode() {
            return Objects.hash(first, second);
        }

        public String toString() {
            return "(" + first + ", " + second + ")";
        }
    }
    public static int solve(int N, int initX, int initY, ArrayList<Pair<Integer,Integer>> arr) {
        int M = arr.size();
        int ans = -1;
        // Place your code here
        
        return ans;
    }
}
