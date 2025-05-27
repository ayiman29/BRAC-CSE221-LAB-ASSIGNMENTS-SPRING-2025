import java.util.*;
import java.io.*;

public class _A1E {
    public static Random rng = new Random();
    public static int test = 0, best = 0, score = 0, batch = 0, total = 0;
    public static int timeLimit = 2, nBatch = 5, N = 0;
    public static int weight[] = { 0, 1, 2, 2, 2, 3 };
    public static int nTest[] = { 0, 1000000, 10000, 100, 500, 50 };
    public static int maxN[] = { 0, 10, 100, 1000, 10000, 100000 };
    public static ArrayList<Integer> arr = new ArrayList<>(), res = new ArrayList<>();

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
        System.exit(1);
    }

    public static void checkSoln(ArrayList<Integer> res)
            throws Exception {
        ArrayList<Integer> brr = new ArrayList<>(res);
        Collections.sort(brr);
        if (!res.equals(brr))
            printCase("WrongAnswer", test, new ArrayList<>(arr));
    }

    public static void limitTime() {
        try {
            Thread.sleep(1000 * timeLimit);
            printCase("TimeLimitExceeded", test, new ArrayList<>(arr));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String args[]) throws Exception {
        if (args.length == 1)
            rng = new Random(batch = Integer.parseInt(args[0]));
        if (args.length != 1 || batch < 1 || nBatch < batch) {
            BufferedReader fin = new BufferedReader(new FileReader("EnterIDandLanguage.txt"));
            String ID = fin.readLine().split("\\s+", 2)[0];
            fin.close();
            if (new File("_A1E_" + ID + ".java").exists()) {
                fin = new BufferedReader(new FileReader("_A1E_" + ID + ".java"));
                best = Integer.parseInt(fin.readLine().split("\\s+", 4)[2]);
                fin.close();
            }
            new FileOutputStream("WrongAnswer.txt").close();
            new FileOutputStream("TimeLimitExceeded.txt").close();
            for (batch = 1; batch <= nBatch; total += weight[batch], ++batch) {
                Process process = new ProcessBuilder("java", "_A1E", "" + batch).start();
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
                BufferedWriter fout = new BufferedWriter(new FileWriter("_A1E_" + ID + ".java"));
                fout.write("// " + ID + " " + score + "\n");
                fout.close();
                new ProcessBuilder("cmd", "/c", "echo // %COMPUTERNAME% %USERNAME%>>_A1E_" + ID + ".java").start()
                        .waitFor();
                fout = new BufferedWriter(new FileWriter("_A1E_" + ID + ".java", true));
                fin = new BufferedReader(new FileReader("_A1E_Solution.java"));
                fout.write(fin.lines().collect(java.util.stream.Collectors.joining(System.lineSeparator())));
                fin.close();
                fout.close();
            }
            System.out.print("Tentative score = " + (score / (double) total) + "/1\n");
            System.exit(0);
        }
        System.out.println("Running on Batch " + batch);
        long start = System.nanoTime();
        new Thread(() -> limitTime()).start();
        if (1 <= batch && batch <= nBatch) {
            for (test = 1; test <= nTest[batch]; ++test) {
                res.clear();
                arr.clear();
                N = 1 + rng.nextInt(maxN[batch]);
                arr.ensureCapacity(N);
                for (int i = 1; i <= N; ++i)
                    arr.add(1 + rng.nextInt(1000000000));
                if (1000 < N)
                    arr.sort(null);
                res = _A1E_Solution.solve(new ArrayList<>(arr));
                checkSoln(res);
            }
        }
        long finish = System.nanoTime();
        long elapsed = finish - start;
        System.out.printf("Passed Batch " + batch + " in %.9fs\n", elapsed * 1e-9);
        System.exit(0);
    }
}