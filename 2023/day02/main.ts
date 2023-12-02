import * as fs from "fs";

const part1 = (fileName: string): number => {
  const LIMITS = {
    red: 12,
    green: 13,
    blue: 14,
  };

  const gameIsValid = (game: string): boolean => {
    const bits = game.split(":")[1].split(";");
    const rgb = [0, 0, 0];
    return bits.every((bit) => {
      const split = bit.split(",").map((x) => x.trim());
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

  return lines.reduce((acc, line) => {
    if (gameIsValid(line)) {
      return acc + getIdFromLine(line);
    }
    return acc;
  }, 0);
};
const part2 = (fileName: string): number => {
  const getPowerOfGame = (game: string): number => {
    const bits = game.split(":")[1].split(";");
    const rgb = [0, 0, 0];
    bits.forEach((bit) => {
      const split = bit.split(",").map((x) => x.trim());
      split.forEach((op) => {
        const [value, color] = op.split(" ");
        const idx = ["red", "green", "blue"].indexOf(color);
        const parsed = parseInt(value);
        rgb[idx] = Math.max(parsed, rgb[idx]);
      });
    });
    return rgb.reduce((acc, val) => acc * val, 1);
  };
  const lines = fs.readFileSync(fileName, "utf-8").split("\n").filter(Boolean);
  return lines.reduce((acc, line) => acc + getPowerOfGame(line), 0);
};

console.log("Part 1:");
console.log(part1("example"));
console.log(part1("input"));
// Første resultat: 227. For lavt
// Andre res: 128. (Også for lavt (lol))
// Trede res: 2151. (Også for lavt??)
// Fjerde res: 2239. Riktig

console.log("Part 2:");
console.log(part2("example"));
console.log(part2("input"));
// Res: 83435. Riktig på første forsøk
