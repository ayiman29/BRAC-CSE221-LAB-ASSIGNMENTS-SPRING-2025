import java.util.*;
import java.io.*;

public class _A4D {
    public static Random rng = new Random();
    public static long start, finish, elapsed = 0, MOD = 1000003;
    public static int test = 0, best = 0, score = 0, batch = 0, total = 0;
    public static int timeLimit = 1, nBatch = 13;
    public static int weight[] = {  0, 6, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8};
    public static int nTest[] =  {0, 1, 1, 1, 10000, 10000, 1000, 1000, 100, 100, 50, 50, 20, 20};
    public static int maxN[] =  {0, 5, 5, 8, 10,  10, 100, 100, 1000, 1000, 10000, 10000, 100000, 100000};
    public static int N, o;
    public static boolean res;
    public static ArrayList<_A4D_Solution.Pair<Integer, Integer>> edges;
    public static ArrayList<Integer> par, perm;

    public static void printCase(String verdict, int test, int N, ArrayList<_A4D_Solution.Pair<Integer, Integer>> edges)
            throws Exception {
        if (new File(verdict + ".txt").length() == 0) {
            BufferedWriter fout = new BufferedWriter(new FileWriter(verdict + ".txt"));
            fout.write("batch = " + batch + "\ntest = " + test + "\n");
            fout.write("N = " + N + "\n");
            fout.write("edges = " + edges + "\n");
            fout.close();
        }
        System.out.print(verdict + " on Batch " + batch + "\n");
    }

    public static void exitCase(String verdict) throws Exception {
        printCase(verdict, test, N, edges);
        System.exit(1);
    }

    public static void checkSoln() throws Exception {
        start = System.nanoTime();
        res = _A4D_Solution.solve(N, edges);
        finish = System.nanoTime();
        elapsed += finish - start;
        if (1000000000L * timeLimit < elapsed)
            exitCase("TimeLimitExceeded");
        boolean a = (o == 0 || o == 2);
        if(res != a)
            exitCase("WrongAnswer");
    }

    public static void processBatch() throws Exception {
        if(batch == 1){
            N = 5;
            edges = new ArrayList<>();
            edges.add(new _A4D_Solution.Pair<Integer, Integer>(0, 1));
            edges.add(new _A4D_Solution.Pair<Integer, Integer>(0, 2));
            edges.add(new _A4D_Solution.Pair<Integer, Integer>(0, 3));
            edges.add(new _A4D_Solution.Pair<Integer, Integer>(0, 4));
            edges.add(new _A4D_Solution.Pair<Integer, Integer>(1, 2));
            edges.add(new _A4D_Solution.Pair<Integer, Integer>(1, 3));
            edges.add(new _A4D_Solution.Pair<Integer, Integer>(2, 3));
            edges.add(new _A4D_Solution.Pair<Integer, Integer>(2, 4));
            edges.add(new _A4D_Solution.Pair<Integer, Integer>(3, 4));
            o = 0;
            checkSoln();
            return; 
        }else if(batch == 2){
            N = 5;
            edges = new ArrayList<>();
            edges.add(new _A4D_Solution.Pair<Integer, Integer>(0, 1));
            edges.add(new _A4D_Solution.Pair<Integer, Integer>(0, 2));
            edges.add(new _A4D_Solution.Pair<Integer, Integer>(0, 3));
            edges.add(new _A4D_Solution.Pair<Integer, Integer>(2, 3));
            edges.add(new _A4D_Solution.Pair<Integer, Integer>(2, 4));
            edges.add(new _A4D_Solution.Pair<Integer, Integer>(3, 4));
            o = 1;
            checkSoln();
            return;
        }else if(batch == 3){
            N = 8;
            edges = new ArrayList<>();
            edges.add(new _A4D_Solution.Pair<Integer, Integer>(0, 2));
            edges.add(new _A4D_Solution.Pair<Integer, Integer>(0, 4));
            edges.add(new _A4D_Solution.Pair<Integer, Integer>(1, 0));
            edges.add(new _A4D_Solution.Pair<Integer, Integer>(1, 4));
            edges.add(new _A4D_Solution.Pair<Integer, Integer>(1, 6));
            edges.add(new _A4D_Solution.Pair<Integer, Integer>(1, 5));
            edges.add(new _A4D_Solution.Pair<Integer, Integer>(2, 4));
            edges.add(new _A4D_Solution.Pair<Integer, Integer>(2, 5));
            edges.add(new _A4D_Solution.Pair<Integer, Integer>(3, 2));
            edges.add(new _A4D_Solution.Pair<Integer, Integer>(4, 3));
            edges.add(new _A4D_Solution.Pair<Integer, Integer>(4, 7));
            edges.add(new _A4D_Solution.Pair<Integer, Integer>(5, 3));
            edges.add(new _A4D_Solution.Pair<Integer, Integer>(6, 4));
            edges.add(new _A4D_Solution.Pair<Integer, Integer>(6, 2));
            edges.add(new _A4D_Solution.Pair<Integer, Integer>(6, 5));
            edges.add(new _A4D_Solution.Pair<Integer, Integer>(7, 0));
            o = 0;
            checkSoln();
            return;
        }
        for (test = 1; test <= nTest[batch]; ++test) {
            N = rng.nextInt(maxN[batch]) + 1;
            int M = rng.nextInt(2 * maxN[batch] - N + 1) + N - 1;
            perm = new ArrayList<Integer>();
            par = new ArrayList<Integer>();
            edges = new ArrayList<_A4D_Solution.Pair<Integer, Integer>>();
            o = 0;
            for(int i = 0; i < N; i++){
                perm.add(i);
                par.add(0);
            }
            Collections.shuffle(perm);
            for(int i = 1; i < N; i++){
                int u = perm.get(rng.nextInt(i));
                int v = perm.get(i);
                par.set(u, par.get(u) ^ 1); par.set(v, par.get(v) ^ 1);
                if(par.get(u) == par.get(v))o += 4 * par.get(u) - 2;
                edges.add(new _A4D_Solution.Pair<Integer, Integer>(u, v));
                M--;
            }
            int A = rng.nextInt(3);
            if(N <= 3 || A == 2){
                while(M > N / 2){
                    int u = rng.nextInt(N);
                    int v = rng.nextInt(N);
                    par.set(u, par.get(u) ^ 1); par.set(v, par.get(v) ^ 1);
                    if(u != v && par.get(u) == par.get(v))o += 4 * par.get(u) - 2;
                    edges.add(new _A4D_Solution.Pair<Integer, Integer>(u, v));
                    M--;
                }
                ArrayList<Integer> oo = new ArrayList<Integer>();
                for(int i = 0; i < N; i++)
                    if(par.get(i) == 1)oo.add(i);
                Collections.shuffle(oo);
                for(int i = 0; i < oo.size(); i += 2){
                    int u = oo.get(i);
                    int v = oo.get(i + 1);
                    par.set(u, par.get(u) ^ 1); par.set(v, par.get(v) ^ 1);
                    if(u != v && par.get(u) == par.get(v))o += 4 * par.get(u) - 2;
                    edges.add(new _A4D_Solution.Pair<Integer, Integer>(u, v));
                    M--;
                }
            }else{
                while(M > A){
                    int u = rng.nextInt(N);
                    int v = rng.nextInt(N);
                    par.set(u, par.get(u) ^ 1); par.set(v, par.get(v) ^ 1);
                    if(u != v && par.get(u) == par.get(v))o += 4 * par.get(u) - 2;
                    edges.add(new _A4D_Solution.Pair<Integer, Integer>(u, v));
                    M--;
                }
                if(A == 1 && o <= 2){
                    ArrayList<Integer> ee = new ArrayList<>();
                    for(int i = 0; i < N; i++){
                        if(par.get(i) == 0)ee.add(i);
                    }
                    int u = ee.get(0);
                    int v = ee.get(1);
                    par.set(u, par.get(u) ^ 1); par.set(v, par.get(v) ^ 1);
                    if(u != v && par.get(u) == par.get(v))o += 4 * par.get(u) - 2;
                    edges.add(new _A4D_Solution.Pair<Integer, Integer>(u, v));
                    M--;
                }
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
        if (new File("_A4D_" + ID + ".java").exists()) {
            fin = new BufferedReader(new FileReader("_A4D_" + ID + ".java"));
            best = Integer.parseInt(fin.readLine().split("\\s+", 4)[2]);
            fin.close();
        }
        new FileOutputStream("WrongAnswer.txt").close();
        new FileOutputStream("TimeLimitExceeded.txt").close();
        for (batch = 1; batch <= nBatch; total += weight[batch], ++batch) {
            Process process = new ProcessBuilder("java", "_A4D", "" + batch).start();
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
            BufferedWriter fout = new BufferedWriter(new FileWriter("_A4D_" + ID + ".java"));
            fout.write("// " + ID + " " + score + "\n");
            fout.close();
            new ProcessBuilder("cmd", "/c", "echo // %COMPUTERNAME% %USERNAME%>>_A4D_" + ID + ".java").start()
                    .waitFor();
            fout = new BufferedWriter(new FileWriter("_A4D_" + ID + ".java", true));
            fin = new BufferedReader(new FileReader("_A4D_Solution.java"));
            fout.write(fin.lines().collect(java.util.stream.Collectors.joining(System.lineSeparator())));
            fin.close();
            fout.close();
        }
        System.out.print("Tentative score = " + (score / (double) total) + "/1\n");
        System.exit(0);
    }
}
