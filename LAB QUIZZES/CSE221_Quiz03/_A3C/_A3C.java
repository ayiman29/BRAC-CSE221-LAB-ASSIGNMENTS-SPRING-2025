import java.util.*;
import java.io.*;

public class _A3C {
    public static Random rng = new Random();
    public static long start, finish, elapsed = 0, ten_9 = 1000000000, MOD = 1000003;
    public static int test = 0, best = 0, score = 0, batch = 0, total = 0;
    public static int timeLimit = 1, nBatch = 14;
    public static int weight[] = { 0, 5, 5, 5, 5, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8 };
    public static int nTest[] = { 0, 1, 1, 1, 1, 1000, 1000, 10000, 1000, 10000, 10, 1000, 1000, 10000, 10000 };
    public static long maxN[] = { 0, 0, 0, 0, 0, 10, 100, 100, 1000, 1000, 1000000, 1000000, ten_9, ten_9 * 1000,
            ten_9 * ten_9 };
    public static Long A, N;
    public static Long res = 0L, ans;

    public static void printCase(String verdict, int test, Long A, Long N)
            throws Exception {
        if (new File(verdict + ".txt").length() == 0) {
            BufferedWriter fout = new BufferedWriter(new FileWriter(verdict + ".txt"));
            fout.write("batch = " + batch + "\ntest = " + test + "\n");
            fout.write("A = " + A + "\n");
            fout.write("N = " + N + "\n");
            fout.close();
        }
        System.out.print(verdict + " on Batch " + batch + "\n");
    }

    public static void exitCase(String verdict) throws Exception {
        printCase(verdict, test, A, N);
        System.exit(1);
    }

    public static void checkSoln() throws Exception {
        start = System.nanoTime();
        res = _A3C_Solution.solve(A, N);
        finish = System.nanoTime();
        elapsed += finish - start;
        if (1000000000L * timeLimit < elapsed)
            exitCase("TimeLimitExceeded");
        if (res < 0 || res >= MOD)
            exitCase("WrongAnswer");
        long tempN=N;
        for (ans = 1L; N > 0; ans = ((N & 1) == 1 ? ans * A % MOD : ans), N >>= 1, A = A * A % MOD)
            ;
        N = tempN;
        if ((long) res != (long) ans)
            exitCase("WrongAnswer");
    }

    public static void processBatch() throws Exception {
        if (batch == 1) {
            test = 1;
            A = 100L;
            N = 3L;
            checkSoln();
            return;
        }
        if (batch == 2) {
            test = 1;
            A = 100L;
            N = 7L;
            checkSoln();
            return;
        }
        if (batch == 3) {
            test = 1;
            A = 1000000L;
            N = ten_9 * ten_9;
            checkSoln();
            return;
        }
        if (batch == 4) {
            test = 1;
            A = 1L;
            N = ten_9;
            checkSoln();
            return;
        }
        for (test = 1; test <= nTest[batch]; ++test) {
            A = rng.nextLong() % 1000000L;
            N = rng.nextLong() % maxN[batch];
            if(A < 0)A = -A;
            if(N < 0)N = -N;
            A++;N++;
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
        if (new File("_A3C_" + ID + ".java").exists()) {
            fin = new BufferedReader(new FileReader("_A3C_" + ID + ".java"));
            best = Integer.parseInt(fin.readLine().split("\\s+", 4)[2]);
            fin.close();
        }
        new FileOutputStream("WrongAnswer.txt").close();
        new FileOutputStream("TimeLimitExceeded.txt").close();
        for (batch = 1; batch <= nBatch; total += weight[batch], ++batch) {
            Process process = new ProcessBuilder("java", "_A3C", "" + batch).start();
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
            BufferedWriter fout = new BufferedWriter(new FileWriter("_A3C_" + ID + ".java"));
            fout.write("// " + ID + " " + score + "\n");
            fout.close();
            new ProcessBuilder("cmd", "/c", "echo // %COMPUTERNAME% %USERNAME%>>_A3C_" + ID + ".java").start()
                    .waitFor();
            fout = new BufferedWriter(new FileWriter("_A3C_" + ID + ".java", true));
            fin = new BufferedReader(new FileReader("_A3C_Solution.java"));
            fout.write(fin.lines().collect(java.util.stream.Collectors.joining(System.lineSeparator())));
            fin.close();
            fout.close();
        }
        System.out.print("Tentative score = " + (score / (double) total) + "/1\n");
        System.exit(0);
    }
}
