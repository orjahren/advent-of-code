const fs = require("fs");

//const INPUT_FILE = "example";
const INPUT_FILE = "input";

const data = fs
  .readFileSync(INPUT_FILE, "utf8")
  .split("\n")
  .map((x) => x.trim())
  .filter(Boolean)
  .map((x) => x.split(/\s+/))
  .map((line) => (isNaN(line[0]) ? line : line.map((x) => parseInt(x))));

console.log(data);
//console.log(typeof data);
console.log(data[0]);
//console.log(typeof data[0]);
console.log(data[0][0]);
//console.log(typeof data[0][0]);

// The number of columns
const numProblems = data[0].length;

let p1 = 0;

for (let i = 0; i < numProblems; i++) {
  const trans = Array.from({ length: data.length }).map((_, j) => data[j][i]);
  console.log(trans);

  const op = trans[trans.length - 1];
  console.log(op);
  const fn = op == "+" ? (a, b) => a + b : (a, b) => a * b;
  const ans = trans.splice(0, trans.length - 1).reduce(fn);
  console.log(ans);
  p1 += ans;
}

console.log("Part1: " + p1);
