import java.util.*;
import java.io.*;



public class _412 {
    public static Random rng = new Random();
    public static long start, finish, elapsed = 0;
    public static int test = 0, best = 0, score = 0, batch = 0, total = 0;
    public static int timeLimit = 1, nBatch = 10, N = 0, nSample = 2, M = 0, initX = -1, initY = -1;
    public static int weight[] = { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1   };
    public static int nTest[] = { 0, 1, 1, 100, 10,  1000, 10, 1,   100,    1000, 100 };
    public static int maxNM[] = { 0, 10, 100, 10, 500,  50,  5000, 10000,   1000,    1000, 5000};
    public static ArrayList<_412_Solution.Pair<Integer, Integer>> arr = new ArrayList<>();
    public static _412_Solution.Pair<Integer, Integer> b1 = new _412_Solution.Pair<>(7,7);

    public static _412_Solution.Pair<Integer, Integer> b2 = new _412_Solution.Pair<>(1,1);
    public static _412_Solution.Pair<Integer, Integer> b3 = new _412_Solution.Pair<>(1,2);

    public static ArrayList<_412_Solution.Pair<Integer, Integer> > sampleArr1 = new ArrayList<>();
    public static ArrayList<_412_Solution.Pair<Integer, Integer> > sampleArr2 = new ArrayList<>();
    public static ArrayList<Integer> sampleAns = new ArrayList<>(Arrays.asList(0,7,1));
    public static ArrayList<Integer> sampleN = new ArrayList<>(Arrays.asList(0,10,2));
    public static ArrayList<Integer> sampleInitX = new ArrayList<>(Arrays.asList(0,6,2));
    public static ArrayList<Integer> sampleInitY = new ArrayList<>(Arrays.asList(0,7,2));
    public static ArrayList<ArrayList<Integer>> samples = new ArrayList<>( Arrays.asList( new ArrayList<>(), new ArrayList<>(Arrays.asList(4, 2, 1, 5, 3)), new ArrayList<>(Arrays.asList(1, 4, 3, 10)),
            new ArrayList<>(Arrays.asList(9, 6, 400000, 2, 12, 5, 300000, 7, 1, 15, 13)), new ArrayList<>(Arrays.asList(23, 11, 5, 2)))
    );
    public static int res;

    public static void printCase(String verdict, int test, int N, int initX, int initY, ArrayList<_412_Solution.Pair<Integer, Integer>> arr)
            throws Exception {
        if (new File(verdict + ".txt").length() == 0) {
            BufferedWriter fout = new BufferedWriter(new FileWriter(verdict + ".txt"));
            fout.write("batch = " + batch + "\ntest = " + test + "\n");
            fout.write("N = " + N + "\n");
            fout.write("M = " + arr.size() + "\n");
            fout.write("initX = " + initX + "\n");
            fout.write("initY = " + initY + "\n");
            fout.write("arr = " + arr + "\n");
            fout.close();
        }
        System.out.print(verdict + " on Batch " + batch + "\n");
    }

    public static void exitCase(String verdict) throws Exception {
        printCase(verdict, test, N, initX, initY, new ArrayList<>(arr));
        System.exit(1);
    }

    

    public static void checkSoln(int val) throws Exception {
        start = System.nanoTime();
        res = _412_Solution.solve(N, initX, initY, new ArrayList<>(arr));
        finish = System.nanoTime();
        elapsed += finish - start;
        if (1000000000L * timeLimit < elapsed)
            exitCase("TimeLimitExceeded");
        
        if (val != res)
            exitCase("WrongAnswer");
    }

    public static void processBatch() throws Exception {
        /* 
        if (batch <= nSample) {
            test = 1;
            arr = samples.get(batch);
            N = arr.size();
            checkSoln();
            return;
        }
            */
        if (batch == 1)
        {
            N = sampleN.get(batch);
            initX = sampleInitX.get(batch);
            initY = sampleInitY.get(batch);
            sampleArr1.add(b1);
            sampleArr1.add(b2);
            arr = sampleArr1;
            checkSoln(sampleAns.get(batch));
            return;
        }
        else if(batch == 2)
        {
            N = sampleN.get(batch);
            initX = sampleInitX.get(batch);
            initY = sampleInitY.get(batch);
            sampleArr2.add(b2);
            sampleArr2.add(b3);
            arr = sampleArr2;
            checkSoln(sampleAns.get(batch));
            return;
        }
            for (int test = 1; test <= nTest[batch]; ++test) {
                int tot = 0;
                Set<_412_Solution.Pair<Integer, Integer>> block = new HashSet<>();
                Set<_412_Solution.Pair<Integer, Integer>> st2 = new HashSet<>();
                N = 2 + rng.nextInt(maxNM[batch]);
                M = 1 + rng.nextInt(Math.min(100, N * N - 1));
                initX = 1 + rng.nextInt(N);
                initY = 1 + rng.nextInt(N);
                
                while (st2.size() < M) {
                    int x = 1 + rng.nextInt(N);
                    int y = 1 + rng.nextInt( N);
                    if (x == initX && y == initY)
                        continue;
                    st2.add(new _412_Solution.Pair<>(x, y));
                    if (Math.abs(x - initX) < 2 && Math.abs(y - initY) < 2) {
                        int dx = x - initX;
                        int dy = y - initY;
                        _412_Solution.Pair<Integer, Integer> p = new _412_Solution.Pair<>(dx, dy);
                        if (!block.contains(p)) {
                            tot += 1;
                            block.add(p);
                        }
                    }
                }
                
                arr = new ArrayList<>(st2);
                int ans = 8;
                if ((initX == 1 || initX == N) && (initY == 1 || initY == N))
                    ans -= 5;
                else if (initX == 1 || initX == N)
                    ans -= 3;
                else if (initY == 1 || initY == N)
                    ans -= 3;
                checkSoln(ans - tot);
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
        if (new File("_412_" + ID + ".java").exists()) {
            fin = new BufferedReader(new FileReader("_412_" + ID + ".java"));
            best = Integer.parseInt(fin.readLine().split("\\s+", 4)[2]);
            fin.close();
        }
        new FileOutputStream("WrongAnswer.txt").close();
        new FileOutputStream("TimeLimitExceeded.txt").close();
        for (batch = 1; batch <= nBatch; total += weight[batch], ++batch) {
            Process process = new ProcessBuilder("java", "_412", "" + batch).start();
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
            BufferedWriter fout = new BufferedWriter(new FileWriter("_412_" + ID + ".java"));
            fout.write("// " + ID + " " + score + "\n");
            fout.close();
            new ProcessBuilder("cmd", "/c", "echo // %COMPUTERNAME% %USERNAME%>>_412_" + ID + ".java").start()
                    .waitFor();
            fout = new BufferedWriter(new FileWriter("_412_" + ID + ".java", true));
            fin = new BufferedReader(new FileReader("_412_Solution.java"));
            fout.write(fin.lines().collect(java.util.stream.Collectors.joining(System.lineSeparator())));
            fin.close();
            fout.close();
        }
        System.out.print("Tentative score = " + (score / (double) total) + "/1\n");
        System.exit(0);
    }
}
