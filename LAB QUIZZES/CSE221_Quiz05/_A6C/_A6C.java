import java.util.*;
import java.io.*;

public class _A6C {
    public static Random rng = new Random();
    public static long start, finish, elapsed = 0, MOD = 1000003;
    public static int test = 0, best = 0, score = 0, batch = 0, total = 0;
    public static int timeLimit = 2, nBatch = 14;
    public static int weight[] = { 0, 5, 5, 5, 5, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8};
     public static int nTest[] = { 0, 1, 1, 1, 1, 40, 40, 40, 40, 20, 20, 10, 10, 5, 5};
    public static int N, res;
    public static int X1, Y1, X2, Y2;

    public static void printCase(String verdict, int test, int N, int X1, int Y1, int X2, int Y2)
            throws Exception {
        if (new File(verdict + ".txt").length() == 0) {
            BufferedWriter fout = new BufferedWriter(new FileWriter(verdict + ".txt"));
            fout.write("batch = " + batch + "\ntest = " + test + "\n");
            fout.write("N = " + N + "\n");
            fout.write("X1 = " + X1 + "\n");
            fout.write("Y1 = " + Y1 + "\n");
            fout.write("X2 = " + X2 + "\n");
            fout.write("Y2 = " + Y2 + "\n");
            fout.close();
        }
        System.out.print(verdict + " on Batch " + batch + "\n");
    }

    public static void exitCase(String verdict) throws Exception {
        printCase(verdict, test, N, X1, Y1, X2, Y2);
        System.exit(1);
    }

    public static void checkSoln() throws Exception {
        start = System.nanoTime();
        res = _A6C_Solution.solve(N, X1, Y1, X2, Y2);
        finish = System.nanoTime();
        elapsed += finish - start;
        if (1000000000L * timeLimit < elapsed)
            exitCase("TimeLimitExceeded");

        BufferedWriter fout = new BufferedWriter(new FileWriter("_A6C_output.txt"));
        fout.write(Integer.toString(res));
        fout.close();

        Process process = new ProcessBuilder("cmd.exe", "/c", "_A6C_Judge.out  _A6C_input.txt _A6C_output.txt").start();
        process.waitFor();
        if (process.exitValue() != 0)
            exitCase("WrongAnswer");
    }

    public static void processBatch() throws Exception {
        
        for (test = 1; test <= nTest[batch]; ++test) {
            String cmd = "_A6C_Gen.out " + batch + " " + test + " > _A6C_input.txt";
            Process process = new ProcessBuilder("cmd.exe", "/c", cmd).start();
            process.waitFor();

            BufferedReader fin = new BufferedReader(new FileReader("_A6C_input.txt"));
            String[] nums = fin.readLine().split(" ");
            N = Integer.parseInt(nums[0]);
            nums = fin.readLine().split(" ");
            X1 = Integer.parseInt(nums[0]);
            Y1 = Integer.parseInt(nums[1]);
            nums = fin.readLine().split(" ");
            X2 = Integer.parseInt(nums[0]);
            Y2 = Integer.parseInt(nums[1]);
            fin.close();
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
        if (new File("_A6C_" + ID + ".java").exists()) {
            fin = new BufferedReader(new FileReader("_A6C_" + ID + ".java"));
            best = Integer.parseInt(fin.readLine().split("\\s+", 4)[2]);
            fin.close();
        }
        new FileOutputStream("WrongAnswer.txt").close();
        new FileOutputStream("TimeLimitExceeded.txt").close();
        for (batch = 1; batch <= nBatch; total += weight[batch], ++batch) {
            Process process = new ProcessBuilder("java", "-Xss128m", "_A6C", "" + batch).start();
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
            BufferedWriter fout = new BufferedWriter(new FileWriter("_A6C_" + ID + ".java"));
            fout.write("// " + ID + " " + score + "\n");
            fout.close();
            new ProcessBuilder("cmd", "/c", "echo // %COMPUTERNAME% %USERNAME%>>_A6C_" + ID + ".java").start()
                    .waitFor();
            fout = new BufferedWriter(new FileWriter("_A6C_" + ID + ".java", true));
            fin = new BufferedReader(new FileReader("_A6C_Solution.java"));
            fout.write(fin.lines().collect(java.util.stream.Collectors.joining(System.lineSeparator())));
            fin.close();
            fout.close();
        }
        System.out.print("Tentative score = " + (score / (double) total) + "/1\n");
        System.exit(0);
    }
}
