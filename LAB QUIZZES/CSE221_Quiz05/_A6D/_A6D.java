import java.util.*;
import java.io.*;

public class _A6D {
    public static Random rng = new Random();
    public static long start, finish, elapsed = 0, MOD = 1000003;
    public static int test = 0, best = 0, score = 0, batch = 0, total = 0;
    public static int timeLimit = 2, nBatch = 14;
    public static int weight[] = { 0, 5, 5, 5, 5, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8};
     public static int nTest[] = { 0, 1, 1, 1, 1, 40, 40, 40, 40, 20, 20, 10, 10, 5, 5};
    public static int N, R;
    public static ArrayList<Integer> res;
    public static ArrayList<_A6D_Solution.Pair<Integer, Integer>> edges = new ArrayList<>();

    public static void printCase(String verdict, int test, int N, int R, ArrayList<_A6D_Solution.Pair<Integer, Integer>> edges)
            throws Exception {
        if (new File(verdict + ".txt").length() == 0) {
            BufferedWriter fout = new BufferedWriter(new FileWriter(verdict + ".txt"));
            fout.write("batch = " + batch + "\ntest = " + test + "\n");
            fout.write("N = " + N + "\n");
            fout.write("R = " + R + "\n");
            fout.write("edges = " + edges + "\n");
            fout.close();
        }
        System.out.print(verdict + " on Batch " + batch + "\n");
    }

    public static void exitCase(String verdict) throws Exception {
        printCase(verdict, test, N, R, edges);
        System.exit(1);
    }

    public static void checkSoln() throws Exception {
        start = System.nanoTime();
        res = _A6D_Solution.solve(N, R, edges);
        finish = System.nanoTime();
        elapsed += finish - start;
        if (1000000000L * timeLimit < elapsed)
            exitCase("TimeLimitExceeded");
        if (res.size() != N + 1)
            exitCase("WrongAnswer");

        BufferedWriter fout = new BufferedWriter(new FileWriter("_A6D_output.txt"));
        res.set(0, 0);
        for (int i = 0; i <= N; ++i) {
            fout.write(res.get(i) + " ");
        }
        fout.write("\n");
        fout.close();

        Process process = new ProcessBuilder("cmd.exe", "/c", "_A6D_Judge.out  _A6D_input.txt _A6D_output.txt").start();
        process.waitFor();
        if (process.exitValue() != 0)
            exitCase("WrongAnswer");
    }

    public static void processBatch() throws Exception {
        
        for (test = 1; test <= nTest[batch]; ++test) {
            String cmd = "_A6D_Gen.out " + batch + " " + test + " > _A6D_input.txt";
            Process process = new ProcessBuilder("cmd.exe", "/c", cmd).start();
            process.waitFor();

            BufferedReader fin = new BufferedReader(new FileReader("_A6D_input.txt"));
            String[] nums = fin.readLine().split(" ");
            N = Integer.parseInt(nums[0]);
            R = Integer.parseInt(nums[1]);
            edges.clear();
            for (int i = 0; i < N - 1; i++) {
                String[] temp = fin.readLine().split(" ");
                int u = Integer.parseInt(temp[0]);
                int v = Integer.parseInt(temp[1]);
                edges.add(new _A6D_Solution.Pair<>(u, v));
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
        if (new File("_A6D_" + ID + ".java").exists()) {
            fin = new BufferedReader(new FileReader("_A6D_" + ID + ".java"));
            best = Integer.parseInt(fin.readLine().split("\\s+", 4)[2]);
            fin.close();
        }
        new FileOutputStream("WrongAnswer.txt").close();
        new FileOutputStream("TimeLimitExceeded.txt").close();
        for (batch = 1; batch <= nBatch; total += weight[batch], ++batch) {
            Process process = new ProcessBuilder("java", "-Xss128m", "_A6D", "" + batch).start();
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
            BufferedWriter fout = new BufferedWriter(new FileWriter("_A6D_" + ID + ".java"));
            fout.write("// " + ID + " " + score + "\n");
            fout.close();
            new ProcessBuilder("cmd", "/c", "echo // %COMPUTERNAME% %USERNAME%>>_A6D_" + ID + ".java").start()
                    .waitFor();
            fout = new BufferedWriter(new FileWriter("_A6D_" + ID + ".java", true));
            fin = new BufferedReader(new FileReader("_A6D_Solution.java"));
            fout.write(fin.lines().collect(java.util.stream.Collectors.joining(System.lineSeparator())));
            fin.close();
            fout.close();
        }
        System.out.print("Tentative score = " + (score / (double) total) + "/1\n");
        System.exit(0);
    }
}
