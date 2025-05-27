import java.util.*;
import java.io.*;

public class _311 {
    public static Random rng = new Random();
    public static long start, finish, elapsed = 0;
    public static int test = 0, best = 0, score = 0, batch = 0, total = 0;
    public static int timeLimit = 1, nBatch = 20, N = 0, nSample = 4;
    public static int weight[] = { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1  };
    public static int nTest[] = { 0, 1, 1, 1, 1, 100, 10, 1, 1000, 100, 10, 1, 10000, 1000, 100, 10, 100000, 10000, 1000, 100, 10 };
    public static int maxNM[] = { 0, 10, 10, 50, 100, 10, 500, 1000, 50, 100, 5000, 10000, 10, 500, 1000, 50000, 50, 100, 1000, 50000, 500000 };
    public static ArrayList<Integer> arr = new ArrayList<>();
    public static ArrayList<ArrayList<Integer>> samples = new ArrayList<>( Arrays.asList( new ArrayList<>(), new ArrayList<>(Arrays.asList(4, 2, 1, 5, 3)), new ArrayList<>(Arrays.asList(1, 4, 3, 10)),
            new ArrayList<>(Arrays.asList(9, 6, 400000, 2, 12, 5, 300000, 7, 1, 15, 13)), new ArrayList<>(Arrays.asList(23, 11, 5, 2)))
    );
    public static int res;

    public static void printCase(String verdict, int test, ArrayList<Integer> arr)
            throws Exception {
        if (new File(verdict + ".txt").length() == 0) {
            BufferedWriter fout = new BufferedWriter(new FileWriter(verdict + ".txt"));
            fout.write("batch = " + batch + "\ntest = " + test + "\n");
            fout.write("N = " + arr.size() + "\n");
            fout.write("arr = " + arr + "\n");
            fout.close();
        }
        System.out.print(verdict + " on Batch " + batch + "\n");
    }

    public static void exitCase(String verdict) throws Exception {
        printCase(verdict, test, new ArrayList<>(arr));
        System.exit(1);
    }

    public static int count(ArrayList<Integer> nums, int st, int ed) {
        if (st >= ed) return 0;
        int mid = st + (ed - st) / 2;
        int tot = count(nums, st, mid) + count(nums, mid + 1, ed);
        
        int j = mid + 1;
        for (int i = st; i <= mid; i++) {
            while (j <= ed && nums.get(i) > 2L * nums.get(j)) {
                j++;
            }
            tot += (j - (mid + 1));
        }
    
        int[] temp = new int[ed - st + 1];
        int left = st, right = mid + 1, idx = 0;
        while (left <= mid && right <= ed) {
            if (nums.get(left) <= nums.get(right)) {
                temp[idx++] = nums.get(left++);
            } else {
                temp[idx++] = nums.get(right++);
            }
        }
        while (left <= mid) temp[idx++] = nums.get(left++);
        while (right <= ed) temp[idx++] = nums.get(right++);
        
        for (int i = st; i <= ed; i++) {
            nums.set(i, temp[i - st]);
        }
    
        return tot;
    }
    

    public static void checkSoln() throws Exception {
        start = System.nanoTime();
        res = _311_Solution.solve(new ArrayList<>(arr));
        finish = System.nanoTime();
        elapsed += finish - start;
        if (1000000000L * timeLimit < elapsed)
            exitCase("TimeLimitExceeded");
        int k = count(new ArrayList<>(arr),0, arr.size() - 1);
        
        if (k != res)
            exitCase("WrongAnswer");
    }

    public static void processBatch() throws Exception {
        if (batch <= nSample) {
            test = 1;
            arr = samples.get(batch);
            N = arr.size();
            checkSoln();
            return;
        }
        for (test = 1; test <= nTest[batch]; ++test) {
            arr.clear();
            N = 1 + rng.nextInt(maxNM[batch]);
            for (int i = 0; i < N; ++i) {
                arr.add(1 + rng.nextInt(500000 + 1));
            }
            checkSoln();
        }
    }

    public static void limitTime() {
        try {
            for (long recall = -1; elapsed < 1000000000L * timeLimit && recall != elapsed;) {
                recall = elapsed;
                Thread.sleep(1000 * timeLimit << 1);
            }
            exitCase("TimeLimitExceeded");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String args[]) throws Exception {
        if (args.length == 1)
            rng.setSeed(batch = Integer.parseInt(args[0]));
        if (1 <= batch && batch <= nBatch) {
            System.out.println("Running on Batch " + batch);
            new Thread(() -> limitTime()).start();
            processBatch();
            System.out.printf("Accepted on Batch " + batch + " in %.9fs\n", elapsed * 1e-9);
            System.exit(0);
        }
        BufferedReader fin = new BufferedReader(new FileReader("EnterIDandLanguage.txt"));
        String ID = fin.readLine().split("\\s+", 2)[0];
        fin.close();
        if (new File("_311_" + ID + ".java").exists()) {
            fin = new BufferedReader(new FileReader("_311_" + ID + ".java"));
            best = Integer.parseInt(fin.readLine().split("\\s+", 4)[2]);
            fin.close();
        }
        new FileOutputStream("WrongAnswer.txt").close();
        new FileOutputStream("TimeLimitExceeded.txt").close();
        for (batch = 1; batch <= nBatch; total += weight[batch], ++batch) {
            Process process = new ProcessBuilder("java", "_311", "" + batch).start();
            fin = new BufferedReader(new InputStreamReader(process.getInputStream()));
            fin.lines().forEach(System.out::println);
            fin.close();
            fin = new BufferedReader(new InputStreamReader(process.getErrorStream()));
            fin.lines().forEach(System.out::println);
            fin.close();
            if (process.waitFor() == 0)
                score += weight[batch];
        }
        if (best <= score) {
            BufferedWriter fout = new BufferedWriter(new FileWriter("_311_" + ID + ".java"));
            fout.write("// " + ID + " " + score + "\n");
            fout.close();
            new ProcessBuilder("cmd", "/c", "echo // %COMPUTERNAME% %USERNAME%>>_311_" + ID + ".java").start()
                    .waitFor();
            fout = new BufferedWriter(new FileWriter("_311_" + ID + ".java", true));
            fin = new BufferedReader(new FileReader("_311_Solution.java"));
            fout.write(fin.lines().collect(java.util.stream.Collectors.joining(System.lineSeparator())));
            fin.close();
            fout.close();
        }
        System.out.print("Tentative score = " + (score / (double) total) + "/1\n");
        System.exit(0);
    }
}
