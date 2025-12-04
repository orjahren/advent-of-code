import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
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

    private char[][] grid;
    private List<String> lines;

    Solution(List<String> lines) {
        int x = lines.get(0).length();
        int y = lines.size();
        this.grid = new char[x][y];
        this.lines = lines;
    }

    private void processLines() {
        // for (String line : lines) {
        for (int i = 0; i < lines.size(); i++) {
            final String line = lines.get(i);
            // final String[] spl = line.split("");
            // TODO: Alle linjer vil ha samme lengde, kan forenkle?
            for (int j = 0; j < line.length(); j++) {
                final char c = line.charAt(j);
                System.out.println("{" + i + ", " + j + "}");
                grid[i][j] = c;
            }
            System.out.println();
        }
    }

    private void printGrid(char[][] grid) {
        for (int i = 0; i < grid.length; i++) {
            for (int j = 0; j < grid[i].length; j++) {
                final char c = grid[i][j];
                System.out.print(c);
            }
            System.out.println();
        }
    }

    private int solve() {
        processLines();

        printGrid(this.grid);

        final long startTimeSeq = System.nanoTime();
        final long seqSolution = -1;// solveSeq(pairs);
        final long endTimeSeq = System.nanoTime();
        final long seqDuration = endTimeSeq - startTimeSeq;

        System.out.println("Sequential execution took " + TimeUnit.NANOSECONDS.toMillis(seqDuration) + "ms");

        return (int) seqSolution;

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

        final Solution solution = new Solution(input.lines().toList());
        final int p1 = solution.solve();
        System.out.println("Part 1: " + p1);

    }
}