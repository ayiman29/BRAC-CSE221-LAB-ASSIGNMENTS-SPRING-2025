import java.util.*;
import java.io.*;

public class _312 {
    public static Random rng = new Random();
    public static long start, finish, elapsed = 0;
    public static int test = 0, best = 0, score = 0, batch = 0, total = 0;
    public static int timeLimit = 1, sBatch = 2, nBatch = 10, N = 0;
    public static int weight[] = { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    public static int nTest[] = { 0, 1, 1, 1, 1, 100, 10000, 1, 100, 10000, 1000000 };
    public static int maxNM[] = { 0, 5, 10, 100, 1000, 100, 10, 10000, 1000, 100, 10 };
    public static ArrayList<ArrayList<Integer>> preOrderSample = new ArrayList<>(
            Arrays.asList(new ArrayList<>(), new ArrayList<>(Arrays.asList(3, 9, 20, 15, 7)),
                    new ArrayList<>(Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8, 9, 500000))));
    public static ArrayList<ArrayList<Integer>> postOrderSample = new ArrayList<>(
            Arrays.asList(new ArrayList<>(), new ArrayList<>(Arrays.asList(9, 15, 7, 20, 3)),
                    new ArrayList<>(Arrays.asList(500000, 9, 8, 7, 6, 5, 4, 3, 2, 1))));
    public static ArrayList<Integer> preOrder = new ArrayList<>(), postOrder = new ArrayList<>(), result,
            newOrder = new ArrayList<>();

    public static void printCase(String verdict, int test, ArrayList<Integer> preOrder, ArrayList<Integer> postOrder)
            throws Exception {
        if (new File(verdict + ".txt").length() == 0) {
            BufferedWriter fout = new BufferedWriter(new FileWriter(verdict + ".txt"));
            fout.write("batch = " + batch + "\ntest = " + test + "\n");
            fout.write("N = " + preOrder.size() + "\n");
            fout.write("preOrder = " + preOrder + "\n");
            fout.write("postOrder = " + postOrder + "\n");
            fout.close();
        }
        System.out.print(verdict + " on Batch " + batch + "\n");
    }

    public static void exitCase(String verdict) throws Exception {
        printCase(verdict, test, new ArrayList<>(preOrder), new ArrayList<>(postOrder));
        System.exit(1);
    }

    public static void build2(int preLeft, int resLeft, int span) {
        if (span < 1)
            return;
        for (int i = 0;; ++i)
            if (preOrder.get(preLeft).equals(result.get(resLeft + i))) {
                build2(preLeft + 1, resLeft, i);
                build2(preLeft + 1 + i, resLeft + i + 1, span - 1 - i);
                break;
            }
        newOrder.add(preOrder.get(preLeft));
    }

    public static void checkSoln() throws Exception {
        start = System.nanoTime();
        result = _312_Solution.solve(new ArrayList<>(preOrder), new ArrayList<>(postOrder));
        finish = System.nanoTime();
        elapsed += finish - start;
        if (1000000000L * timeLimit < elapsed)
            exitCase("TimeLimitExceeded");
        if (result.size() != N)
            exitCase("WrongAnswer");
        newOrder.clear();
        build2(0, 0, N);
        if (!postOrder.equals(newOrder))
            exitCase("WrongAnswer");
    }

    public static void build(int left, int right) {
        if (right < left)
            return;
        if (left < right) {
            int mid = left + 1 + rng.nextInt(right - left);
            build(left + 1, mid);
            build(mid + 1, right);
        }
        postOrder.add(preOrder.get(left));
    }

    public static void processBatch() throws Exception {
        if (batch <= sBatch) {
            test = 1;
            preOrder = preOrderSample.get(batch);
            postOrder = postOrderSample.get(batch);
            N = preOrder.size();
            checkSoln();
            return;
        }
        for (test = 1; test <= nTest[batch]; ++test) {
            N = 1 + rng.nextInt(maxNM[batch]);
            preOrder.clear();
            postOrder.clear();
            HashSet<Integer> hashTable = new HashSet<>();
            for (int i = 0, j; i < N; ++i) {
                for (j = 1 + rng.nextInt(500000); hashTable.contains(j); j = 1 + rng.nextInt(500000))
                    ;
                hashTable.add(j);
                preOrder.add(j);
            }
            build(0, N - 1);
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
        if (new File("_312_" + ID + ".java").exists()) {
            fin = new BufferedReader(new FileReader("_312_" + ID + ".java"));
            best = Integer.parseInt(fin.readLine().split("\\s+", 4)[2]);
            fin.close();
        }
        new FileOutputStream("WrongAnswer.txt").close();
        new FileOutputStream("TimeLimitExceeded.txt").close();
        for (batch = 1; batch <= nBatch; total += weight[batch], ++batch) {
            Process process = new ProcessBuilder("java", "_312", "" + batch).start();
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
            BufferedWriter fout = new BufferedWriter(new FileWriter("_312_" + ID + ".java"));
            fout.write("// " + ID + " " + score + "\n");
            fout.close();
            new ProcessBuilder("cmd", "/c", "echo // %COMPUTERNAME% %USERNAME%>>_312_" + ID + ".java").start()
                    .waitFor();
            fout = new BufferedWriter(new FileWriter("_312_" + ID + ".java", true));
            fin = new BufferedReader(new FileReader("_312_Solution.java"));
            fout.write(fin.lines().collect(java.util.stream.Collectors.joining(System.lineSeparator())));
            fin.close();
            fout.close();
        }
        System.out.print("Tentative score = " + (score / (double) total) + "/1\n");
        System.exit(0);
    }
}
