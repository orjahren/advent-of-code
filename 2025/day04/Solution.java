import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.concurrent.TimeUnit;

class Pair {
    int left, right;

    @Override
    public String toString() {
        return "{" + left + ", " + right + "}";
    }
}

class Solution {

    public final static boolean DEBUG = true;
    public long p1Seq, p2Seq, p2Par;

    Solution() {
    }

    private static Pair morphemeToPair(final String morpheme) {
        final Pair p = new Pair();
        final String[] spl = morpheme.split("");
        p.left = -1;
        p.right = -1;

        return p;
    }

    private static List<Pair> lineToCoords(final String line) {
        final String[] spl = line.split("");
        System.out.println(spl);
        return Arrays.stream(spl).map(Solution::morphemeToPair).toList();
    }

    private String solve(final List<String> lines) {
        final List<Pair> coords = new ArrayList<>();
        for (String line : lines) {
            List<Pair> lineCoords = lineToCoords(line);
            coords.addAll(lineCoords);
        }

        if (DEBUG)
            System.out.println("Coords:");
        if (DEBUG)
            System.out.println(coords);

        final long startTimeSeq = System.nanoTime();
        final long seqSolution = -1;// solveSeq(pairs);
        final long endTimeSeq = System.nanoTime();
        final long seqDuration = endTimeSeq - startTimeSeq;

        System.out.println("Sequential execution took " + TimeUnit.NANOSECONDS.toMillis(seqDuration) + "ms");

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
        // if (DEBUG)
        System.out.println(input);

        final Solution solution = new Solution();
        final long p1 = solution.p1Seq;
        final long p2 = solution.p2Par;
        System.out.println("Part 1: " + p1);
        System.out.println("Part 2: " + p2);

    }
}