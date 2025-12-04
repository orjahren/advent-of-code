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

    private boolean isInBounds(int val) {
        return val >= 0 && val < grid.length && val < grid[0].length;

    }

    private List<Pair> getNeighbors(int x, int y) {
        final List<Pair> res = new ArrayList<>();
        final int[][] coords = new int[][] {
                { -1, -1 }, { -1, 0 }, { -1, 1 },
                { 0, -1 }, { 0, 1 },
                { 1, -1 }, { 1, 0 }, { 1, 1 },

        };
        for (int i = 0; i < coords.length; i++) {

            int a = coords[i][0];
            int b = coords[i][1];

            Pair p = new Pair();

            p.left = x + a;
            p.right = y + b;
            if (isInBounds(p.left) && isInBounds(p.right)) {
                res.add(p);
            }
        }
        return res;
    }

    private boolean isElidgeble(int x, int y, int maxOccupied) {

        final List<Pair> neighbors = getNeighbors(x, y);
        System.out.println("Jeg er " + x + " , " + y + ", og dette er mine naboer: ");
        System.out.println(neighbors);
        int numOccupiedNeighbors = 0;
        for (Pair p : neighbors) {
            char other = grid[p.left][p.right];
            System.out.print(other);
            if (other == '@') {
                numOccupiedNeighbors++;
            }
        }
        System.out.println();
        System.out.println("Denne har " + numOccupiedNeighbors + " occupied :o ");
        return numOccupiedNeighbors < maxOccupied;

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

        int seqSolution = 0;

        final char[][] mutatedGrid = new char[grid.length][grid[0].length];
        for (int i = 0; i < grid.length; i++) {
            mutatedGrid[i] = Arrays.copyOf(grid[i], grid[i].length);
        }

        for (int i = 0; i < grid.length; i++) {
            for (int j = 0; j < grid[i].length; j++) {
                final char c = grid[i][j];
                if (c == '.') {
                    continue;
                }
                // System.out.print(c);
                System.out.println("SJekker naboer for " + c + " på pos " + i + ", " + j);
                if (isElidgeble(i, j, 4)) {
                    seqSolution++;
                    mutatedGrid[i][j] = 'x';
                }
            }
            System.out.println();
        }

        final long endTimeSeq = System.nanoTime();
        final long seqDuration = endTimeSeq - startTimeSeq;

        System.out.println("Sequential execution took " + TimeUnit.NANOSECONDS.toMillis(seqDuration) + "ms");
        System.out.println("\nMutated grid: ");
        printGrid(mutatedGrid);

        return seqSolution;

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