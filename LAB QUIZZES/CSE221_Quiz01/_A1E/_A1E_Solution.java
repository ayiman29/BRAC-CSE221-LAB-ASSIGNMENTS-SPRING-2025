import java.util.*;

public class _A1E_Solution {
    public static ArrayList<Integer> solve(ArrayList<Integer> arr) {
        // Change the given code
        for (int i = 0; i < arr.size(); ++i)
            for (int j = 0; j < arr.size() - i - 1; ++j)
                if (arr.get(j) > arr.get(j + 1))
                    Collections.swap(arr, j, j + 1);
        return arr;
    }
}