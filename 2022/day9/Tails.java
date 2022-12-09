import java.io.File;
import java.io.FileNotFoundException;
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

    private boolean isMatch(Knot k1, Knot k2) {
        return k1.x == k2.x && k1.y == k2.y;
    }

    private Knot updateTail(Knot tail, Knot head) {
        Knot tup = new Knot(head.x - tail.x, head.y - tail.y);
        Knot ret = new Knot(tail.x, tail.y);
        Knot[] dt = { new Knot(-2, 1), new Knot(-1, 2), new Knot(0, 2), new Knot(1, 2), new Knot(2, 1) };
        Knot[] rt = { new Knot(1, 2), new Knot(2, 1), new Knot(2, 0), new Knot(2, -1), new Knot(1, -2) };
        Knot[] ot = { new Knot(2, -1), new Knot(1, -2), new Knot(0, -2), new Knot(-1, -2), new Knot(-2, -1) };
        Knot[] lt = { new Knot(-1, -2), new Knot(-2, -1), new Knot(-2, 0), new Knot(-2, 1), new Knot(-1, 2) };

        for (Knot k : dt) {
            if (tup.equals(k)) {
                ret.y++;
                break;
            }
        }
        for (Knot k : rt) {
            if (tup.equals(k)) {
                ret.x++;
                break;
            }

        }
        for (Knot k : ot) {
            if (tup.equals(k)) {
                ret.y--;
                break;
            }
        }
        for (Knot k : lt) {
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

        Knot head = new Knot(0, 0);
        Knot tail = new Knot(0, 0);

        LinkedList<Knot> visitedByTail = new LinkedList<>();

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
                tail = updateTail(tail, head);
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