import java.util.*;
import java.io.*;

public class _A7E {
    public static Random rng = new Random();
    public static long start, finish, elapsed = 0, MOD = 1000003;
    public static int test = 0, best = 0, score = 0, batch = 0, total = 0;
    public static int timeLimit = 2, nBatch = 14;
    public static int weight[] = { 0, 5, 5, 5, 5, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8};
     public static int nTest[] = { 0, 1, 1, 1, 1, 40, 40, 40, 40, 20, 20, 10, 10, 5, 5};
    public static int N, M;
    public static Long res;
    public static ArrayList<Integer> Us = new ArrayList<>();
    public static ArrayList<Integer> Vs = new ArrayList<>();
    public static ArrayList<Integer> Ws = new ArrayList<>();

    public static void printCase(String verdict, int test, int N, int M, ArrayList<Integer> Us, ArrayList<Integer> Vs, ArrayList<Integer> Ws) throws Exception {
        if (new File(verdict + ".txt").length() == 0) {
            BufferedWriter fout = new BufferedWriter(new FileWriter(verdict + ".txt"));
            fout.write("batch = " + batch + "\ntest = " + test + "\n");
            fout.write("N = " + N + "\n");
            fout.write("M = " + M + "\n");
            fout.write("Us = " + Us + "\n");
            fout.write("Vs = " + Vs + "\n");
            fout.write("Ws = " + Ws + "\n");
            fout.close();
        }
        System.out.print(verdict + " on Batch " + batch + "\n");
    }

    public static void exitCase(String verdict) throws Exception {
        printCase(verdict, test, N, M, Us, Vs, Ws);
        System.exit(1);
    }

    public static void checkSoln() throws Exception {
        start = System.nanoTime();
        res = _A7E_Solution.solve(N, M, Us, Vs, Ws);
        finish = System.nanoTime();
        elapsed += finish - start;
        if (1000000000L * timeLimit < elapsed)
            exitCase("TimeLimitExceeded");

        BufferedWriter fout = new BufferedWriter(new FileWriter("_A7E_output.txt"));
        fout.write(res + "\n");
        fout.close();

        Process process = new ProcessBuilder("cmd.exe", "/c", "_A7E_Judge.out  _A7E_input.txt _A7E_output.txt").start();
        process.waitFor();
        if (process.exitValue() != 0)
            exitCase("WrongAnswer");
    }

    public static void processBatch() throws Exception {
        
        for (test = 1; test <= nTest[batch]; ++test) {
            String cmd = "_A7E_Gen.out " + batch + " " + test + " > _A7E_input.txt";
            Process process = new ProcessBuilder("cmd.exe", "/c", cmd).start();
            process.waitFor();

            BufferedReader fin = new BufferedReader(new FileReader("_A7E_input.txt"));
            String[] nums = fin.readLine().split(" ");
            N = Integer.parseInt(nums[0]);
            M = Integer.parseInt(nums[1]);
            Us.clear();
            Vs.clear();
            Ws.clear();
            for (int i = 0; i < M; i++) {
                String[] temp = fin.readLine().split(" ");
                int u = Integer.parseInt(temp[0]);
                int v = Integer.parseInt(temp[1]);
                int w = Integer.parseInt(temp[2]);
                Us.add(u);
                Vs.add(v);
                Ws.add(w);
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
        if (new File("_A7E_" + ID + ".java").exists()) {
            fin = new BufferedReader(new FileReader("_A7E_" + ID + ".java"));
            best = Integer.parseInt(fin.readLine().split("\\s+", 4)[2]);
            fin.close();
        }
        new FileOutputStream("WrongAnswer.txt").close();
        new FileOutputStream("TimeLimitExceeded.txt").close();
        for (batch = 1; batch <= nBatch; total += weight[batch], ++batch) {
            Process process = new ProcessBuilder("java", "-Xss128m", "_A7E", "" + batch).start();
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
            BufferedWriter fout = new BufferedWriter(new FileWriter("_A7E_" + ID + ".java"));
            fout.write("// " + ID + " " + score + "\n");
            fout.close();
            new ProcessBuilder("cmd", "/c", "echo // %COMPUTERNAME% %USERNAME%>>_A7E_" + ID + ".java").start()
                    .waitFor();
            fout = new BufferedWriter(new FileWriter("_A7E_" + ID + ".java", true));
            fin = new BufferedReader(new FileReader("_A7E_Solution.java"));
            fout.write(fin.lines().collect(java.util.stream.Collectors.joining(System.lineSeparator())));
            fin.close();
            fout.close();
        }
        System.out.print("Tentative score = " + (score / (double) total) + "/1\n");
        System.exit(0);
    }
}
