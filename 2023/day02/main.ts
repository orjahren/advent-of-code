import * as fs from "fs";

const idx = (color: string) => ["red", "green", "blue"].indexOf(color);
const part1 = (lines: string[]): number => {
  const getIdIfValid = (game: string): number => {
    const rgb = [0, 0, 0];
    const [idStr, content] = game.split(":");
    return content.split(";").every((bit) => {
      bit
        .split(",")
        .map((x) => x.trim())
        .forEach((op) => {
          const [val, col] = op.split(" ");
          rgb[idx(col)] = parseInt(val);
        });
      return rgb[0] < 13 && rgb[1] < 14 && rgb[2] < 15;
    })
      ? parseInt(idStr.substring(5))
      : 0;
  };
  return lines.reduce((acc, line) => getIdIfValid(line) + acc, 0);
};

const part2 = (lines: string[]): number => {
  const getPowerOfGame = (game: string): number => {
    const rgb = [0, 0, 0];
    game
      .split(":")[1]
      .split(";")
      .forEach((bit) =>
        bit
          .split(",")
          .map((x) => x.trim())
          .forEach((op) => {
            const [val, col] = op.split(" ");
            rgb[idx(col)] = Math.max(parseInt(val), rgb[idx(col)]);
          })
      );
    return rgb.reduce((acc, val) => acc * val, 1);
  };
  return lines.reduce((acc, line) => getPowerOfGame(line) + acc, 0);
};

const getLines = (fileName: string): string[] =>
  fs.readFileSync(fileName, "utf-8").split("\n").filter(Boolean);

console.log("Part 1:");
console.log(part1(getLines("example")));
console.log(part1(getLines("input")));

console.log("Part 2:");
console.log(part2(getLines("example")));
console.log(part2(getLines("input")));
