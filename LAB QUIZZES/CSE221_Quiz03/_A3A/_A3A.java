import java.util.*;
import java.io.*;

public class _A3A {
    public static Random rng = new Random();
    public static long start, finish, elapsed = 0;
    public static int test = 0, best = 0, score = 0, batch = 0, total = 0;
    public static int timeLimit = 1, nBatch = 14, N = 0;
    public static int weight[] = { 0, 5, 5, 5, 5,   8,   8,   8,   8,    8,    8,    8,     8,     8,       8};
    public static int nTest[] =  { 0, 1, 1, 1, 1, 100, 100,  10, 100,   10,  100,  100,    10,    10,      10};
    public static int maxN[] =   { 0, 5, 5, 5, 7,  10,  20, 100, 100, 1000, 1000, 1000, 10000, 100000, 100000};
    public static ArrayList<Integer> A = new ArrayList<>();
    public static Long res = 0L;

    public static void printCase(String verdict, int test, ArrayList<Integer> A)
            throws Exception {
        if (new File(verdict + ".txt").length() == 0) {
            BufferedWriter fout = new BufferedWriter(new FileWriter(verdict + ".txt"));
            fout.write("batch = " + batch + "\ntest = " + test + "\n");
            fout.write("N = " + A.size() + "\n");
            fout.write("A = " + A + "\n");
            fout.close();
        }
        System.out.print(verdict + " on Batch " + batch + "\n");
    }

    public static void exitCase(String verdict) throws Exception {
        printCase(verdict, test, new ArrayList<>(A));
        System.exit(1);
    }

    public static void checkSoln() throws Exception {
        start = System.nanoTime();
        res = _A3A_Solution.solve(new ArrayList<>(A));
        finish = System.nanoTime();
        elapsed += finish - start;
        if (1000000000L * timeLimit < elapsed)
            exitCase("TimeLimitExceeded");
        int[] st = new int[2 * (N + 1)];
        int idx = 0;
        st[idx++] = 0;
        st[idx++] = A.size() - 1;
        ArrayList<Integer> temp = new ArrayList<>();
        while(idx > 0){
            int b = st[--idx];
            int a = st[--idx];
            if(a == b)continue;
            if(b < 0){
                b = -b;
                int m = a + b >> 1;
                int i = a, j = m + 1;
                while(i <= m || j <= b){
                    if(i > m || j <= b && A.get(j) < A.get(i))
                        temp.add(A.get(j++));
                    else{
                        res -= j - m - 1;
                        temp.add(A.get(i++));
                    }
                        
                }
                for(i = a; i <= b; i++)
                    A.set(i, temp.get(i - a));
                temp.clear();
            }else{
                int m = a + b >> 1;
                st[idx++] = a;
                st[idx++] = -b;
                st[idx++] = a;
                st[idx++] = m;
                st[idx++] = m + 1;
                st[idx++] = b;
            }
        }
        if(res != 0)
            exitCase("WrongAnswer");
    }

    public static void processBatch() throws Exception {
        if (batch == 1) {
            test = 1;
            A = new ArrayList<>(Arrays.asList(1, 2, 5, 4, 3));
            N = A.size();
            checkSoln();
            return;
        }
        if (batch == 2) {
            test = 1;
            A = new ArrayList<>(Arrays.asList(1, 2, 5, 4, 3));
            N = A.size();
            checkSoln();
            return;
        }
        if (batch == 3) {
            test = 1;
            A = new ArrayList<>(Arrays.asList(1, 2, 3, 4, 5));
            N = A.size();
            checkSoln();
            return;
        }
        if (batch == 4) {
            test = 1;
            A = new ArrayList<>(Arrays.asList(6, 4, 2, 5, 7, 3, 1));
            N = A.size();
            checkSoln();
            return;
        }
        
        for (test = 1; test <= nTest[batch]; ++test) {
            A.clear();
            N =  1 + rng.nextInt(maxN[batch]);
            int[] temp = new int[N + 1];
            for (int i = 0; i < N; ++i) {
                A.add(1 + rng.nextInt(N));
                temp[A.get(i)]++;
            }
            for(int i = 1; i <= N; i++)temp[i] += temp[i - 1];
            for(int i = 0; i < N; i++)A.set(i, temp[A.get(i)]--);
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
        if (new File("_A3A_" + ID + ".java").exists()) {
            fin = new BufferedReader(new FileReader("_A3A_" + ID + ".java"));
            best = Integer.parseInt(fin.readLine().split("\\s+", 4)[2]);
            fin.close();
        }
        new FileOutputStream("WrongAnswer.txt").close();
        new FileOutputStream("TimeLimitExceeded.txt").close();
        for (batch = 1; batch <= nBatch; total += weight[batch], ++batch) {
            Process process = new ProcessBuilder("java", "_A3A", "" + batch).start();
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
            BufferedWriter fout = new BufferedWriter(new FileWriter("_A3A_" + ID + ".java"));
            fout.write("// " + ID + " " + score + "\n");
            fout.close();
            new ProcessBuilder("cmd", "/c", "echo // %COMPUTERNAME% %USERNAME%>>_A3A_" + ID + ".java").start()
                    .waitFor();
            fout = new BufferedWriter(new FileWriter("_A3A_" + ID + ".java", true));
            fin = new BufferedReader(new FileReader("_A3A_Solution.java"));
            fout.write(fin.lines().collect(java.util.stream.Collectors.joining(System.lineSeparator())));
            fin.close();
            fout.close();
        }
        System.out.print("Tentative score = " + (score / (double) total) + "/1\n");
        System.exit(0);
    }
}
