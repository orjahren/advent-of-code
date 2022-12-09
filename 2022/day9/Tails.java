package day9;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

class Tails {
    public static void main(String[] args) throws FileNotFoundException {
        System.out.println("Hello world");
        File f = new File("small");
        Scanner scanner = new Scanner(f);

        while (scanner.hasNextLine()) {
            String line = scanner.nextLine();
            char direction = line.charAt(0);
            int n = Integer.parseInt(line.split(" ")[1]);
            System.out.println("Head skal gå " + n + " steg mot " + direction);

        }
        scanner.close();
    }
}