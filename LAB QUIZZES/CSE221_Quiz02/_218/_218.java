import java.util.*;
import java.io.*;

public class _218 {
    public static Random rng = new Random();
    public static long start, finish, elapsed = 0;
    public static int test = 0, best = 0, score = 0, batch = 0, total = 0;
    public static int timeLimit = 1, nBatch = 25, N = 0, M = 0;
    public static int weight[] = { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    public static int nTest[] = { 0, 2, 10, 1, 100, 10, 1, 1000, 100, 10, 1, 10000, 1000, 100, 10, 1, 100000, 10000,
            1000, 100, 10, 100000, 10000, 1000, 100, 10 };
    public static int maxNM[] = { 0, 10, 10, 100, 10, 100, 1000, 10, 100, 1000, 10000, 10, 100, 1000, 10000, 100000, 10,
            100, 1000, 10000, 100000, 100, 1000, 10000, 100000, 1000000 };
    public static ArrayList<Integer> list1 = new ArrayList<>(), list2 = new ArrayList<>(), res;

    public static void printCase(String verdict, int test, ArrayList<Integer> list1, ArrayList<Integer> list2)
            throws Exception {
        if (new File(verdict + ".txt").length() == 0) {
            BufferedWriter fout = new BufferedWriter(new FileWriter(verdict + ".txt"));
            fout.write("batch = " + batch + "\ntest = " + test + "\n");
            fout.write("N = " + list1.size() + "\n");
            fout.write("M = " + list2.size() + "\n");
            fout.write("list1 = " + list1 + "\n");
            fout.write("list1 = " + list2 + "\n");
            fout.close();
        }
        System.out.print(verdict + " on Batch " + batch + "\n");
    }

    public static void exitCase(String verdict) throws Exception {
        printCase(verdict, test, new ArrayList<>(list1), new ArrayList<>(list2));
        System.exit(1);
    }

    public static void checkSoln() throws Exception {
        start = System.nanoTime();
        res = _218_Solution.solve(new ArrayList<>(list1), new ArrayList<>(list2));
        finish = System.nanoTime();
        elapsed += finish - start;
        if (1000000000L * timeLimit < elapsed)
            exitCase("TimeLimitExceeded");
        int k = 0;
        for (int i = list1.size() - 1, j = list2.size() - 1; 0 <= i || 0 <= j; ++k) {
            if (k == res.size()
                    || ((0 <= i && !res.get(k).equals(list1.get(i))) && (0 <= j && !res.get(k).equals(list2.get(j)))))
                exitCase("WrongAnswer");
            for (; 0 <= i && list1.get(i).equals(res.get(k)); --i)
                ;
            for (; 0 <= j && list2.get(j).equals(res.get(k)); --j)
                ;
        }
        if (k != res.size())
            exitCase("WrongAnswer");
        for (k -= 1; 0 < k; --k)
            if (res.get(k) >= res.get(k - 1))
                exitCase("WrongAnswer");
    }

    public static void processBatch() throws Exception {
        if (batch == 1) {
            test = 1;
            list1 = new ArrayList<>(Arrays.asList(1, 2, 2, 3, 4));
            list2 = new ArrayList<>(Arrays.asList(2, 2, 3, 3, 5, 6));
            N = list1.size();
            M = list2.size();
            checkSoln();
            test = 2;
            list1 = new ArrayList<>(Arrays.asList(2, 4, 5, 5, 8, 9, 9, 12, 15));
            list2 = new ArrayList<>(Arrays.asList(1, 1, 5, 6, 7, 12, 12, 20));
            N = list1.size();
            M = list2.size();
            checkSoln();
            return;
        }
        for (test = 1; test <= nTest[batch]; ++test) {
            list1.clear();
            list2.clear();
            N = 1 + rng.nextInt(maxNM[batch]);
            M = 1 + rng.nextInt(maxNM[batch]);
            for (int i = 0; i < N; ++i) {
                if (0 < i && rng.nextInt(2) != 0)
                    list1.add(0);
                else
                    list1.add(1 + rng.nextInt(1000000000 / N));
                if (0 < i)
                    list1.set(i, Integer.min(1000000000, list1.get(i) + list1.get(i - 1)));
            }
            for (int i = 0; i < M; ++i) {
                if (0 < i && rng.nextInt(2) != 0)
                    list2.add(0);
                else
                    list2.add(1 + rng.nextInt(1000000000 / M));
                if (0 < i)
                    list2.set(i, Integer.min(1000000000, list2.get(i) + list2.get(i - 1)));
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
        if (new File("_218_" + ID + ".java").exists()) {
            fin = new BufferedReader(new FileReader("_218_" + ID + ".java"));
            best = Integer.parseInt(fin.readLine().split("\\s+", 4)[2]);
            fin.close();
        }
        new FileOutputStream("WrongAnswer.txt").close();
        new FileOutputStream("TimeLimitExceeded.txt").close();
        for (batch = 1; batch <= nBatch; total += weight[batch], ++batch) {
            Process process = new ProcessBuilder("java", "_218", "" + batch).start();
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
            BufferedWriter fout = new BufferedWriter(new FileWriter("_218_" + ID + ".java"));
            fout.write("// " + ID + " " + score + "\n");
            fout.close();
            new ProcessBuilder("cmd", "/c", "echo // %COMPUTERNAME% %USERNAME%>>_218_" + ID + ".java").start()
                    .waitFor();
            fout = new BufferedWriter(new FileWriter("_218_" + ID + ".java", true));
            fin = new BufferedReader(new FileReader("_218_Solution.java"));
            fout.write(fin.lines().collect(java.util.stream.Collectors.joining(System.lineSeparator())));
            fin.close();
            fout.close();
        }
        System.out.print("Tentative score = " + (score / (double) total) + "/1\n");
        System.exit(0);
    }
}