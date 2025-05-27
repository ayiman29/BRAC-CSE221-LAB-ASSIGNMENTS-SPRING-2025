import java.util.*;
import java.io.*;

public class _A2A {
    public static Random rng = new Random();
    public static int test = 0, best = 0, score = 0, batch = 0, total = 0;
    public static int timeLimit = 1, nBatch = 10;
    public static int weight[] = { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    public static int nTest[] = { 0, 10, 100, 100, 100, 100, 100, 100, 10, 10, 10 };
    public static int maxN[] = { 0, 10, 10, 100, 100, 1000, 1000, 10000, 100000, 1000000, 1000000 };
    public static int maxS[] = { 0, 1_000, 1_000_000, 1_000_000, 1_000_000_000, 1_000_000, 1_000_000_000, 1_000_000,
            1_000_000_000, 1_000_000, 1_000_000_000 };
    public static ArrayList<Integer> A = new ArrayList<>();
    public static Integer S = 0;
    public static Integer N = 0;

    public static _A2A_Solution.Pair<Integer, Integer> res;

    public static void printCase(String verdict, int test, Integer N, Integer S, ArrayList<Integer> A)
            throws Exception {
        if (new File(verdict + ".txt").length() == 0) {
            BufferedWriter fout = new BufferedWriter(new FileWriter(verdict + ".txt"));
            fout.write("batch = " + batch + "\ntest = " + test + "\n");
            fout.write("N = " + N + "\n");
            fout.write("S = " + S + "\n");
            fout.write("A = " + A + "\n");
            fout.close();
        }
        System.out.print(verdict + " on Batch " + batch + "\n");
    }

    public static void exitCase(String verdict) throws Exception {
        printCase(verdict, test, N, S, A);
        System.exit(1);
    }

    public static boolean validIndex(int i) {
        return i > 0 && i <= N;
    }

    public static void checkSoln() throws Exception {
        if (res.key != -1) {
            if (!validIndex(res.key) || !validIndex(res.value) || res.key == res.value)
                exitCase("WrongAnswer");
            if (A.get(res.key - 1) + A.get(res.value - 1) != S)
                exitCase("WrongAnswer");
        } else {
            for (int i = 0, j = N - 1; i < j; i += (A.get(i) + A.get(j) > S ? (--j > 0 ? 0 : 0) : 1))
                if (A.get(i) + A.get(j) == S)
                    exitCase("WrongAnswer");
        }
    }

    public static void processBatch() throws Exception {
        for (test = 1; test <= nTest[batch]; ++test) {
            N = 2 + rng.nextInt(maxN[batch] - 1);
            A.clear();
            int D = maxS[batch] / N;
            for (int i = 0; i < N; ++i)
                A.add((i == 0 ? 1 + rng.nextInt(maxS[batch] - (N - i - 1) * D)
                        : A.get(i - 1) + rng.nextInt(maxS[batch] - (N - i - 1) * D - A.get(i - 1) + 1)));
            boolean OK = (rng.nextInt(2) == 1);
            if (OK) {
                int i = rng.nextInt(N);
                int j = i;
                while (i == j)
                    j = rng.nextInt(N);
                S = A.get(i) + A.get(j);
            } else {
                S = 1 + rng.nextInt(maxS[batch]);
            }
            res = _A2A_Solution.solve(N, S, new ArrayList(A));
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
        if (new File("_A2A_" + ID + ".java").exists()) {
            fin = new BufferedReader(new FileReader("_A2A_" + ID + ".java"));
            best = Integer.parseInt(fin.readLine().split("\\s+", 4)[2]);
            fin.close();
        }
        new FileOutputStream("WrongAnswer.txt").close();
        new FileOutputStream("TimeLimitExceeded.txt").close();
        for (batch = 1; batch <= nBatch; total += weight[batch], ++batch) {
            Process process = new ProcessBuilder("java", "_A2A", "" + batch).start();
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
            BufferedWriter fout = new BufferedWriter(new FileWriter("_A2A_" + ID + ".java"));
            fout.write("// " + ID + " " + score + "\n");
            fout.close();
            new ProcessBuilder("cmd", "/c", "echo // %COMPUTERNAME% %USERNAME%>>_A2A_" + ID + ".java").start()
                    .waitFor();
            fout = new BufferedWriter(new FileWriter("_A2A_" + ID + ".java", true));
            fin = new BufferedReader(new FileReader("_A2A_Solution.java"));
            fout.write(fin.lines().collect(java.util.stream.Collectors.joining(System.lineSeparator())));
            fin.close();
            fout.close();
        }
        System.out.print("Tentative score = " + (score / (double) total) + "/1\n");
        System.exit(0);
    }
}
