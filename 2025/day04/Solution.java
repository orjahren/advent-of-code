import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.TimeUnit;

class Pair {
    int left, right;

    Pair() {
    }

    Pair(int left, int right) {
        this.left = left;
        this.right = right;
    }

    @Override
    public String toString() {
        return "{" + left + ", " + right + "}";
    }
}

class Solution {

    public final static boolean DEBUG = false;

    private char[][] globalGrid;
    private List<String> lines;

    Solution(List<String> lines) {
        int x = lines.get(0).length();
        int y = lines.size();
        this.globalGrid = new char[x][y];
        this.lines = lines;
    }

    private void processLines() {
        for (int i = 0; i < lines.size(); i++) {
            final String line = lines.get(i);
            // TODO: Alle linjer vil ha samme lengde, kan forenkle?
            for (int j = 0; j < line.length(); j++) {
                final char c = line.charAt(j);
                if (DEBUG)
                    System.out.println("{" + i + ", " + j + "}");
                globalGrid[i][j] = c;
            }
            if (DEBUG)
                System.out.println();
        }
    }

    private boolean isInBounds(int val) {
        return val >= 0 && val < globalGrid.length && val < globalGrid[0].length;

    }

    private boolean isInBounds(Pair p) {
        return isInBounds(p.left) && isInBounds(p.right);
    }

    private List<Pair> getNeighbors(int x, int y, char[][] grid) {
        final List<Pair> res = new ArrayList<>();
        final int[][] coords = new int[][] {
                { -1, -1 }, { -1, 0 }, { -1, 1 },
                { 0, -1 }, { 0, 1 },
                { 1, -1 }, { 1, 0 }, { 1, 1 },

        };
        for (int i = 0; i < coords.length; i++) {
            final int[] stem = coords[i];
            final Pair p = new Pair(x + stem[0], y + stem[1]);
            if (isInBounds(p)) {
                res.add(p);
            }
        }
        return res;
    }

    private boolean isElidgeble(int x, int y, int maxOccupied, char[][] grid) {
        final List<Pair> neighbors = getNeighbors(x, y, grid);
        int numOccupiedNeighbors = 0;
        for (Pair p : neighbors) {
            final char other = grid[p.left][p.right];
            if (other == '@') {
                numOccupiedNeighbors++;
            }
        }
        if (DEBUG) {
            System.out.println("Jeg er " + x + " , " + y + ", og dette er mine naboer: ");
            System.out.println(neighbors);
            System.out.println("Denne har " + numOccupiedNeighbors + " occupied :o ");
        }
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

    private char[][] getDeepGridCopy(char[][] grid) {
        final char[][] mutatedGrid = new char[grid.length][grid[0].length];
        for (int i = 0; i < grid.length; i++) {
            mutatedGrid[i] = Arrays.copyOf(grid[i], grid[i].length);
        }
        return mutatedGrid;
    }

    private Pair solve() {
        processLines();
        printGrid(this.globalGrid);

        final long startTimeSeq = System.nanoTime();

        char[][] currentGrid = getDeepGridCopy(this.globalGrid);

        final List<Integer> gains = new LinkedList<>();
        do {
            final char[][] nextGrid = getDeepGridCopy(currentGrid);

            int generation = 0;

            // TODO: Kan bruke heuristics for å ikke itererere over known deadspots mange
            // ganger
            for (int i = 0; i < currentGrid.length; i++) {
                for (int j = 0; j < currentGrid[i].length; j++) {
                    final char c = currentGrid[i][j];
                    if (c == '.' || c == 'x') {
                        continue;
                    }
                    if (DEBUG) {
                        System.out.println("SJekker naboer for " + c + " på pos " + i + ", " + j);
                    }
                    if (isElidgeble(i, j, 4, currentGrid)) {
                        generation++;
                        nextGrid[i][j] = '.';
                    }
                }
                if (DEBUG) {
                    System.out.println();
                }
            }
            gains.add(generation);
            currentGrid = nextGrid;
        } while (gains.getLast() > 0);

        final long endTimeSeq = System.nanoTime();
        final long seqDuration = endTimeSeq - startTimeSeq;

        System.out.println("\nMutated grid: ");
        printGrid(currentGrid);

        System.out.println("Sequential execution took " + TimeUnit.NANOSECONDS.toMillis(seqDuration) + "ms");

        final int p1 = gains.get(0);
        final int p2 = gains.stream().mapToInt(Integer::intValue).sum();

        return new Pair(p1, p2);

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
        final Pair res = solution.solve();
        System.out.println("Part 1: " + res.left);
        System.out.println("Part 2: " + res.right);

    }
}