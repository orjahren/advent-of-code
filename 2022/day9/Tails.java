import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Scanner;

class Tails {

    private class Knot {
        int x;
        int y;

        Knot(int x, int y) {
            this.x = x;
            this.y = y;
        }

        public boolean equals(Knot other) {
            return this.x == other.x && this.y == other.y;
        }

    }

    private Knot updateTail(Knot tail, Knot head, Knot[][] tests) {
        Knot tup = new Knot(head.x - tail.x, head.y - tail.y);
        Knot ret = new Knot(tail.x, tail.y);
        for (Knot k : tests[0]) {
            if (tup.equals(k)) {
                ret.y++;
                break;
            }
        }
        for (Knot k : tests[1]) {
            if (tup.equals(k)) {
                ret.x++;
                break;
            }

        }
        for (Knot k : tests[2]) {
            if (tup.equals(k)) {
                ret.y--;
                break;
            }
        }
        for (Knot k : tests[3]) {
            if (tup.equals(k)) {
                ret.x--;
                break;
            }
        }
        return ret;
    }

    public int solve(String fileName) throws FileNotFoundException {

        File f = new File(fileName);
        Scanner scanner = new Scanner(f);

        ArrayList<Knot> allKnots = new ArrayList<>();
        for (int i = 0; i < 10; i++) {
            allKnots.add(new Knot(0, 0));
        }

        Knot tail = allKnots.get(9);
        Knot head = allKnots.get(0);

        LinkedList<Knot> visitedByTail = new LinkedList<>();

        Knot[] dt = { new Knot(-2, 1), new Knot(-1, 2), new Knot(0, 2), new Knot(1, 2), new Knot(2, 1) };
        Knot[] rt = { new Knot(1, 2), new Knot(2, 1), new Knot(2, 0), new Knot(2, -1), new Knot(1, -2) };
        Knot[] ot = { new Knot(2, -1), new Knot(1, -2), new Knot(0, -2), new Knot(-1, -2), new Knot(-2, -1) };
        Knot[] lt = { new Knot(-1, -2), new Knot(-2, -1), new Knot(-2, 0), new Knot(-2, 1), new Knot(-1, 2) };

        Knot[][] tests = { dt, rt, ot, lt };

        while (scanner.hasNextLine()) {
            String line = scanner.nextLine();
            char direction = line.charAt(0);
            int n = Integer.parseInt(line.split(" ")[1]);

            for (short i = 0; i < n; i++) {
                switch (direction) {
                    case 'U':
                        head.y++;
                        break;
                    case 'D':
                        head.y--;
                        break;
                    case 'R':
                        head.x++;
                        break;
                    case 'L':
                        head.x--;
                }
                tail = updateTail(tail, head, tests);
                boolean tailIsVisited = false;
                for (Knot k : visitedByTail) {
                    if (k.equals(tail)) {
                        tailIsVisited = true;
                        break;
                    }
                }
                if (!tailIsVisited) {
                    visitedByTail.add(tail);
                }
            }

        }
        scanner.close();
        return visitedByTail.size();
    }

    public static void main(String[] args) {
        Tails solver = new Tails();
        for (String filename : new String[] { "small", "input" }) {
            try {
                int part1 = solver.solve(filename);
                System.out.println("Part 1: " + part1);
            } catch (FileNotFoundException e) {
                e.printStackTrace();
                System.exit(1);
            }
        }
    }
}