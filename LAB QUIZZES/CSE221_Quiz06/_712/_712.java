import java.util.*;
import java.io.*;

public class _712 {
    public static Random rng = new Random();
    public static long start, finish, elapsed = 0, MOD = 1000003;
    public static int test = 0, best = 0, score = 0, batch = 0, total = 0;
    public static int timeLimit = 1, nBatch = 10;
    public static int weight[] = {  0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    public static int nTest[] =  {0, 1, 50, 100, 100, 50, 20, 50, 50, 20, 50};
    public static int N, M, S, D, K;
    public static int res;
    public static ArrayList<Integer> arr;
    public static ArrayList<Integer> u, v, w;
    public static ArrayList<ArrayList<Integer> > edges;
    

    public static void printCase(String verdict, int test, int N, int M, int S, int D, int K, ArrayList <ArrayList<Integer> > edges)
            throws Exception {
        if (new File(verdict + ".txt").length() == 0) {
            BufferedWriter fout = new BufferedWriter(new FileWriter(verdict + ".txt"));
            fout.write("batch = " + batch + "\ntest = " + test + "\n");
            fout.write("N = " + N + "\n");
            fout.write("M = " + M + "\n");
            fout.write("S = " + S + "\n");
            fout.write("D = " + D + "\n");
            fout.write("K = " + K + "\n");
            fout.write("edges = " + edges + "\n");
            fout.close();
        }
        System.out.print(verdict + " on Batch " + batch + "\n");
    }

    public static void exitCase(String verdict) throws Exception {
        printCase(verdict, test, N, M, S, D, K, edges);
        System.exit(1);
    }

    public static void checkSoln() throws Exception {
        start = System.nanoTime();
        res = _712_Solution.solve(N, M, S, D, K, edges);
        finish = System.nanoTime();
        elapsed += finish - start;
        if (1000000000L * timeLimit < elapsed)
            exitCase("TimeLimitExceeded");

        BufferedWriter fout = new BufferedWriter(new FileWriter("_712_output.txt"));
        fout.write(Integer.toString(res) + "\n");
        fout.close();

        Process process = new ProcessBuilder("cmd.exe", "/c", "_712_Judge.out  _712_input.txt _712_output.txt").start();
        process.waitFor();
        if (process.exitValue() != 0)
            exitCase("WrongAnswer");
    }

    public static void processBatch() throws Exception {
        
        for (test = 1; test <= nTest[batch]; ++test) {
            String cmd = "_712_Gen.out " + batch + " " + test + " > _712_input.txt";
            Process process = new ProcessBuilder("cmd.exe", "/c", cmd).start();
            process.waitFor();

            BufferedReader fin = new BufferedReader(new FileReader("_712_input.txt"));
            String[] nums = fin.readLine().split(" ");
            N = Integer.parseInt(nums[0]);
            M = Integer.parseInt(nums[1]);
            S = Integer.parseInt(nums[2]);
            D = Integer.parseInt(nums[3]);
            K = Integer.parseInt(nums[4]);
            edges = new ArrayList<>();
            
            String[] temp = fin.readLine().split(" ");
            u = new ArrayList<>();
            for(int i = 0; i < M; i++){
                u.add(Integer.parseInt(temp[i]));
            }
            temp = fin.readLine().split(" ");
            v = new ArrayList<>();
            for(int i = 0; i < M; i++){
                v.add(Integer.parseInt(temp[i]));
            }
            temp = fin.readLine().split(" ");
            w = new ArrayList<>();
            for(int i = 0; i < M; i++){
                w.add(Integer.parseInt(temp[i]));
            }
            for(int i = 0; i < M; i++){
                ArrayList<Integer> ed = new ArrayList<>(Arrays.asList(u.get(i),v.get(i),w.get(i)));
                edges.add(ed);
            }

            checkSoln();
            fin.close();
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
        if (new File("_712_" + ID + ".java").exists()) {
            fin = new BufferedReader(new FileReader("_712_" + ID + ".java"));
            best = Integer.parseInt(fin.readLine().split("\\s+", 4)[2]);
            fin.close();
        }
        new FileOutputStream("WrongAnswer.txt").close();
        new FileOutputStream("TimeLimitExceeded.txt").close();
        for (batch = 1; batch <= nBatch; total += weight[batch], ++batch) {
            Process process = new ProcessBuilder("java", "-Xss128m", "_712", "" + batch).start();
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
            BufferedWriter fout = new BufferedWriter(new FileWriter("_712_" + ID + ".java"));
            fout.write("// " + ID + " " + score + "\n");
            fout.close();
            new ProcessBuilder("cmd", "/c", "echo // %COMPUTERNAME% %USERNAME%>>_712_" + ID + ".java").start()
                    .waitFor();
            fout = new BufferedWriter(new FileWriter("_712_" + ID + ".java", true));
            fin = new BufferedReader(new FileReader("_712_Solution.java"));
            fout.write(fin.lines().collect(java.util.stream.Collectors.joining(System.lineSeparator())));
            fin.close();
            fout.close();
        }
        System.out.print("Tentative score = " + (score / (double) total) + "/1\n");
        System.exit(0);
    }
}
