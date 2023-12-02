import * as fs from "fs";

const part1 = (fileName: string) => {
  const lines = fs.readFileSync(fileName, "utf-8").split("\n").filter(Boolean);
  console.log(lines);
  console.log("hello");
};

part1("example");
