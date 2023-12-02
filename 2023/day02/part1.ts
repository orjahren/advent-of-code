import * as fs from "fs";

const part1 = (fileName: string): number => {
  const LIMITS = {
    red: 12,
    green: 13,
    blue: 14,
  };

  const gameIsValid = (game: string): boolean => {
    console.log("Skal løse game:");
    console.log(game);
    const bits = game.split(":")[1].split(";");
    console.log(bits);
    const rgb = [0, 0, 0];
    console.log(rgb);
    return bits.every((bit) => {
      console.log(bit);
      const split = bit.split(",").map((x) => x.trim());
      console.log(split);
      console.log(rgb);
      split.forEach((op) => {
        const [value, color] = op.split(" ");
        rgb[["red", "green", "blue"].indexOf(color)] = parseInt(value);
      });
      if (
        rgb[0] > LIMITS.red ||
        rgb[1] > LIMITS.green ||
        rgb[2] > LIMITS.blue
      ) {
        return false;
      }
      return true;
    });
  };

  // TODO: Muligens mer smooth å bare returnere id fra valid, 0 hvis ikke valid
  const getIdFromLine = (line: string): number => {
    const x = line.split(":")[0];
    return parseInt(x.split(" ")[1]);
  };

  const lines = fs.readFileSync(fileName, "utf-8").split("\n").filter(Boolean);

  console.log(lines);
  return lines.reduce((acc, line) => {
    if (gameIsValid(line)) {
      console.log("Valid game: " + getIdFromLine(line));
      return acc + getIdFromLine(line);
    }
    return acc;
  }, 0);
};

console.log(part1("example"));
console.log(part1("input"));
// Første resultat: 227. For lavt
// Andre res: 128. (Også for lavt (lol))
// Trede res: 2151. (Også for lavt??)
// Fjerde res: 2239. Riktig
