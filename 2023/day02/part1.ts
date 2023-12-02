import * as fs from "fs";

const gameIsValid = (game: string): boolean => {
  const LIMITS = {
    red: 13,
    blue: 14,
    green: 15,
  };
  console.log("Skal løse game:");
  console.log(game);
  const bits = game.split(":")[1].split(";");
  console.log(bits);
  const rgb = [0, 0, 0];
  console.log(rgb);
  rgb[1] = 2;
  console.log(rgb);
  return bits.every((bit) => {
    console.log(bit);
    const split = bit.split(",").map((x) => x.trim());
    console.log(split);
    split.forEach((op) => {
      const [valueStr, color] = op.split(" ");
      const val = parseInt(valueStr);
      if (color === "red") {
        rgb[0] += val;
      } else if (color === "blue") {
        rgb[1] += val;
      } else if (color === "green") {
        rgb[2] += val;
      } else {
        console.error("Invalid color?? Wack");
        return -9999;
      }
    });
    if (rgb[0] > LIMITS.red || rgb[1] > LIMITS.blue || rgb[2] > LIMITS.green) {
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
const part1 = (fileName: string): number => {
  const lines = fs.readFileSync(fileName, "utf-8").split("\n").filter(Boolean);
  console.log(lines);
  console.log("hello");
  return lines.reduce((acc, line) => {
    if (gameIsValid(line)) {
      return acc + getIdFromLine(line);
    }
    return acc;
  }, 0);
};

console.log(part1("example"));
