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

    private final String line;
    private final int nThreads;

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
        System.out.println("\tEvaluererer ID " + idAsString + " med følgende shingles: " + shingles);

        for (String shingle : shingles) {

            boolean allMatches = true;

            final int windowSize = shingle.length();
            System.out.println("\t\tProsesserer shingle: " + shingle + ", med window size " + windowSize);
            for (int i = windowSize; i < idAsString.length(); i += windowSize) {
                try {
                    final String window = idAsString.substring(i, i + windowSize);
                    System.out.println("\t\t\tWindow: " + window + " (fra i: " + i + ")");
                    allMatches &= window.equals(shingle);

                    // System.out.println(idAsString.substring(0, windowSize));
                    // System.out.println(idAsString.substring(1, 2));
                    // System.out.println(idAsString.substring(i, windowSize));

                } catch (StringIndexOutOfBoundsException e) {

                    // TODO: handle exception
                    System.out.println("\t\t\tFikk ex med i=" + i);
                    // continue;
                    // return true;
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
            System.out.println("\t ---- Pair: " + p);
            for (long i = p.left; i <= p.right; i++) {

                if (!idIsValidP2(i)) {
                    System.out.println("Iden " + i + " er invalid");

                    // numInvalidIds++;
                    numInvalidIds += i;
                }

            }
            System.out.println("\n\n");
            // return -1;
        }
        return numInvalidIds;
    }

    public int solvePar(final List<Pair> pairs) {
        return -1;
    }

    public String solve() {
        List<Pair> pairs = lineToPairs(this.line);

        System.out.println("Pairs:");
        System.out.println(pairs);

        final long startTimeSeq = System.nanoTime();
        final long seqSolution = solveSeq(pairs);
        final long endTimeSeq = System.nanoTime();
        final long seqDuration = endTimeSeq - startTimeSeq;

        System.out.println("Sequential execution took " + TimeUnit.NANOSECONDS.toMillis(seqDuration) + "ms");

        /*
         * final long startTimePar = System.nanoTime();
         * final int parSolution = solvePar();
         * final long endTimePar = System.nanoTime();
         * final long parDuration = endTimePar - startTimePar;
         * 
         * final double speedup = seqDuration / parDuration;
         * System.out.println("Speedup: " + speedup);
         */

        return String.valueOf(seqSolution);

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
        System.out.println(input);

        final Solution solver = new Solution(input);
        final String answer = solver.solve();
        System.out.println("Answer: " + answer);

    }
}