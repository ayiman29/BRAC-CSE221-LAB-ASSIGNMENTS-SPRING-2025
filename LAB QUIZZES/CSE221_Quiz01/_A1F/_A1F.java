import java.util.*;
import java.io.*;

public class _A1F {
    public static Random rng = new Random();
    public static int test = 0, best = 0, score = 0, batch = 0, total = 0;
    public static int timeLimit = 1, nBatch = 10, N = 0;
    public static int weight[] = { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    public static int nTest[] = { 0, 10, 1000, 100000, 10, 100, 1000, 10000, 1, 10, 100 };
    public static int maxN[] = { 0, 10, 10, 10, 100, 100, 100, 100, 1000, 1000, 1000 };
    public static ArrayList<Integer> sIDs = new ArrayList<>(), sMarks = new ArrayList<>();
    public static _A1F_Solution.Pair<Integer, ArrayList<_A1F_Solution.Pair<Integer, Integer>>> res;

    public static void printCase(String verdict, int test, ArrayList<Integer> sIDs, ArrayList<Integer> sMarks)
            throws Exception {
        if (new File(verdict + ".txt").length() == 0) {
            BufferedWriter fout = new BufferedWriter(new FileWriter(verdict + ".txt"));
            fout.write("batch = " + batch + "\ntest = " + test + "\n");
            fout.write("N = " + sIDs.size() + "\n");
            fout.write("sIDs = " + sIDs + "\n");
            fout.write("sMarks = " + sMarks + "\n");
            fout.close();
        }
        System.out.print(verdict + " on Batch " + batch + "\n");
    }

    public static void exitCase(String verdict) throws Exception {
        printCase(verdict, test, new ArrayList<>(sIDs), new ArrayList<>(sMarks));
        System.exit(1);
    }

    public static void checkSoln() throws Exception {
        int cnt = 0;
        ArrayList<_A1F_Solution.Pair<Integer, Integer>> arr = new ArrayList<>();
        arr.ensureCapacity(N);
        for (int i = 0; i < N; ++i)
            arr.add(new _A1F_Solution.Pair<>(-sMarks.get(i), sIDs.get(i)));
        for (int i = 0, j, k; i < N; ++i) {
            for (j = k = i; k < N; ++k)
                if (arr.get(j).key > arr.get(k).key
                        || (arr.get(j).key == arr.get(k).key && arr.get(j).value > arr.get(k).value))
                    j = k;
            if (i != j) {
                Collections.swap(arr, i, j);
                ++cnt;
            }
        }
        for (int i = 0; i < N; ++i)
            arr.set(i, new _A1F_Solution.Pair<>(arr.get(i).value, -arr.get(i).key));
        if (cnt != res.key || arr.equals(res.value))
            exitCase("WrongAnswer");
    }

    public static void processBatch() throws Exception {
        for (test = 1; test <= nTest[batch]; ++test) {
            sIDs.clear();
            sMarks.clear();
            N = 1 + rng.nextInt(maxN[batch]);
            for (int i = 1; i <= N; ++i) {
                sIDs.add(i + 1000 - N);
                sMarks.add(1 + rng.nextInt(1000));
            }
            Collections.shuffle(sIDs, rng);
            res = _A1F_Solution.solve(new ArrayList<>(sIDs), new ArrayList<>(sMarks));
            checkSoln();
        }
    }

    public static void limitTime() {
        try {
            Thread.sleep(1000 * timeLimit);
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
            long start = System.nanoTime();
            new Thread(() -> limitTime()).start();
            processBatch();
            long finish = System.nanoTime();
            long elapsed = finish - start;
            System.out.printf("Passed Batch " + batch + " in %.9fs\n", elapsed * 1e-9);
            System.exit(0);
        }
        BufferedReader fin = new BufferedReader(new FileReader("EnterIDandLanguage.txt"));
        String ID = fin.readLine().split("\\s+", 2)[0];
        fin.close();
        if (new File("_A1F_" + ID + ".java").exists()) {
            fin = new BufferedReader(new FileReader("_A1F_" + ID + ".java"));
            best = Integer.parseInt(fin.readLine().split("\\s+", 4)[2]);
            fin.close();
        }
        new FileOutputStream("WrongAnswer.txt").close();
        new FileOutputStream("TimeLimitExceeded.txt").close();
        for (batch = 1; batch <= nBatch; total += weight[batch], ++batch) {
            Process process = new ProcessBuilder("java", "_A1F", "" + batch).start();
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
            BufferedWriter fout = new BufferedWriter(new FileWriter("_A1F_" + ID + ".java"));
            fout.write("// " + ID + " " + score + "\n");
            fout.close();
            new ProcessBuilder("cmd", "/c", "echo // %COMPUTERNAME% %USERNAME%>>_A1F_" + ID + ".java").start()
                    .waitFor();
            fout = new BufferedWriter(new FileWriter("_A1F_" + ID + ".java", true));
            fin = new BufferedReader(new FileReader("_A1F_Solution.java"));
            fout.write(fin.lines().collect(java.util.stream.Collectors.joining(System.lineSeparator())));
            fin.close();
            fout.close();
        }
        System.out.print("Tentative score = " + (score / (double) total) + "/1\n");
        System.exit(0);
    }
}