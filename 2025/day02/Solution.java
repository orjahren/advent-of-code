import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.concurrent.TimeUnit;

class Pair {
    long left, right;

    @Override
    public String toString() {
        return "{" + left + ", " + right + "}";
    }
}

class Solution {

    public final static boolean DEBUG = false;

    private final String line;
    private final int nThreads;

    public long p1Seq, p2Seq, p2Par;

    Solution(final String line) {
        this.line = line;
        this.nThreads = Runtime.getRuntime().availableProcessors();
    }

    private static Pair morphemeToPair(final String morpheme) {
        final Pair p = new Pair();
        final String[] spl = morpheme.split("-");
        p.left = Long.parseLong(spl[0]);
        p.right = Long.parseLong(spl[1]);

        return p;
    }

    private List<Pair> lineToPairs(final String line) {
        final String[] spl = line.split(",");
        return Arrays.stream(spl).map(Solution::morphemeToPair).toList();
    }

    private boolean idIsValidP1(long id) {
        final String idAsString = String.valueOf(id);

        int middle = idAsString.length() / 2;

        final String first = idAsString.substring(0, middle);
        final String second = idAsString.substring(middle);

        if (DEBUG)
            System.out.println(first + ", " + second);

        return !first.equals(second);

    }

    private List<String> getShingles(final String stem) {
        final Set<String> shingleSet = new HashSet<>();
        for (int i = 1; i < stem.length(); i++) {
            final String shingle = stem.substring(0, i);
            shingleSet.add(shingle);
        }

        // Deduplicate
        final List<String> res = new ArrayList<>();
        // TODO: Finnes noe fancy syntax for dette?
        for (String s : shingleSet)
            res.add(s);

        return res;
    }

    private boolean idIsValidP2(long id) {
        final String idAsString = String.valueOf(id);

        final List<String> shingles = getShingles(idAsString);
        if (DEBUG)
            System.out.println("\tEvaluererer ID " + idAsString + " med følgende shingles: " + shingles);

        for (String shingle : shingles) {

            boolean allMatches = true;

            final int windowSize = shingle.length();
            if (DEBUG)
                System.out.println("\t\tProsesserer shingle: " + shingle + ", med window size " + windowSize);
            for (int i = windowSize; i < idAsString.length(); i += windowSize) {
                try {
                    final String window = idAsString.substring(i, i + windowSize);
                    if (DEBUG)
                        System.out.println("\t\t\tWindow: " + window + " (fra i: " + i + ")");
                    allMatches &= window.equals(shingle);

                } catch (StringIndexOutOfBoundsException e) {
                    // TODO: Burde finne på noe bedre her

                    if (DEBUG)
                        System.out.println("\t\t\tFikk ex med i=" + i);
                    allMatches = false;
                }
            }
            if (allMatches) {
                return false;
            }
        }
        return true;

    }

    public long solveSeq(final List<Pair> pairs) {
        long numInvalidIds = 0;
        for (Pair p : pairs) {
            if (DEBUG)
                System.out.println("\t ---- Pair: " + p);
            for (long i = p.left; i <= p.right; i++) {
                if (!idIsValidP2(i)) {
                    if (DEBUG)
                        System.out.println("Iden " + i + " er invalid");
                    numInvalidIds += i;
                }

            }
            if (DEBUG)
                System.out.println("\n\n");
        }
        return numInvalidIds;
    }

    class AoCSolver extends Thread {
        public final List<Pair> pairList;
        public long res;
        private int pairStart, pairEnd;

        AoCSolver(final List<Pair> allPairsRef, final int pairStart, final int pairEnd) {
            this.pairList = allPairsRef;
            this.res = 0;
            this.pairStart = pairStart;
            this.pairEnd = pairEnd;
            if (DEBUG)
                System.out.println("Tråd som skal deale med pairs fra " + pairStart + " til " + pairEnd);
        }

        @Override
        public void run() {
            for (long i = pairStart; i < pairEnd; i++) {
                final Pair p = pairList.get((int) i);
                for (long j = p.left; j <= p.right; j++) {
                    if (!idIsValidP2(j)) {
                        if (DEBUG)
                            System.out.println("Iden " + j + " er invalid");
                        res += j;
                    }
                }
            }

        }
    }

    public long solvePar(final List<Pair> pairs) {

        AoCSolver[] threads = new AoCSolver[nThreads];

        final int pairsPrThread = pairs.size() / nThreads;

        for (int i = 0; i < threads.length; i++) {
            AoCSolver t = new AoCSolver(pairs, i * pairsPrThread,
                    i == threads.length - 1 ? pairs.size() : (i + 1) * pairsPrThread);
            threads[i] = t;
            t.start();
        }

        this.p2Par = 0;
        for (int i = 0; i < threads.length; i++) {
            try {
                threads[i].join();
                this.p2Par += threads[i].res;
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        return this.p2Par;

    }

    public String solve() {
        final List<Pair> pairs = lineToPairs(this.line);

        if (DEBUG)
            System.out.println("Pairs:");
        if (DEBUG)
            System.out.println(pairs);

        final long startTimeSeq = System.nanoTime();
        final long seqSolution = solveSeq(pairs);
        final long endTimeSeq = System.nanoTime();
        final long seqDuration = endTimeSeq - startTimeSeq;

        System.out.println("Sequential execution took " + TimeUnit.NANOSECONDS.toMillis(seqDuration) + "ms");

        final long startTimePar = System.nanoTime();
        final long parSolution = solvePar(pairs);
        final long endTimePar = System.nanoTime();
        final long parDuration = endTimePar - startTimePar;

        if (seqSolution == parSolution) {
            System.out.println("Fant riktig svar parallellt :D ");
        } else {
            System.out.println("Fant FEIL svar parallellt :o ");
            System.out.println("Fikk " + parSolution + ", skal være " + seqSolution);
            System.exit(1);
        }

        final double speedup = (double) seqDuration / parDuration;
        System.out.println("Parallel execution took " + TimeUnit.NANOSECONDS.toMillis(parDuration) + "ms");
        System.out.println("Speedup: " + speedup);

        return String.valueOf(parSolution);

    }

    private static String getLine(final String fileName) throws FileNotFoundException, IOException {
        final File file = new File(fileName);
        final FileReader fr = new FileReader(file);

        final String line = fr.readAllAsString();
        fr.close();
        return line;
    }

    public static void main(String[] args) throws FileNotFoundException, IOException {
        assert args.length > 0;

        final String fileName = args[0];
        System.out.println("File name: " + fileName);

        final String input = getLine(fileName);
        if (DEBUG)
            System.out.println(input);

        final Solution solver = new Solution(input);
        final String answer = solver.solve();
        System.out.println("Answer: " + answer);

    }
}