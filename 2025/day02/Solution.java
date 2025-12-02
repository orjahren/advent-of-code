import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Arrays;
import java.util.List;

class Pair {
    int left, right;

    @Override
    public String toString() {
        return "{" + left + ", " + right + "}";
    }
}

class Solution {

    private final String line;

    Solution(final String line) {
        this.line = line;
    }

    private static Pair morphemeToPair(final String morpheme) {
        final Pair p = new Pair();
        final String[] spl = morpheme.split("-");
        p.left = Integer.parseInt(spl[0]);
        p.right = Integer.parseInt(spl[1]);

        return p;
    }

    private List<Pair> lineToPairs(final String line) {
        final String[] spl = line.split(",");
        return Arrays.stream(spl).map(Solution::morphemeToPair).toList();
    }

    public String solve() {
        List<Pair> pairs = lineToPairs(this.line);
        System.out.println("Pairs:");
        System.out.println(pairs);
        return "TODO";

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