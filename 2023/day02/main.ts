import * as fs from "fs";

const part1 = (fileName: string): number => {
  const getIdIfValid = (game: string): number => {
    const rgb = [0, 0, 0];
    const [idStr, content] = game.split(":");
    return content.split(";").every((bit) => {
      bit
        .split(",")
        .map((x) => x.trim())
        .forEach((op) => {
          const [value, color] = op.split(" ");
          rgb[["red", "green", "blue"].indexOf(color)] = parseInt(value);
        });
      return rgb[0] < 13 && rgb[1] < 14 && rgb[2] < 15;
    })
      ? parseInt(idStr.substring(5))
      : 0;
  };
  return fs
    .readFileSync(fileName, "utf-8")
    .split("\n")
    .filter(Boolean)
    .reduce((acc, line) => getIdIfValid(line) + acc, 0);
};

const part2 = (fileName: string): number => {
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
            const [value, color] = op.split(" ");
            const idx = ["red", "green", "blue"].indexOf(color);
            rgb[idx] = Math.max(parseInt(value), rgb[idx]);
          })
      );
    return rgb.reduce((acc, val) => acc * val, 1);
  };
  return fs
    .readFileSync(fileName, "utf-8")
    .split("\n")
    .filter(Boolean)
    .reduce((acc, line) => getPowerOfGame(line) + acc, 0);
};

console.log("Part 1:");
console.log(part1("example"));
console.log(part1("input"));

console.log("Part 2:");
console.log(part2("example"));
console.log(part2("input"));
