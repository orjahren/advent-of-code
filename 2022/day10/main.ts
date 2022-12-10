"use scrict";
const fs = require("fs");
const lines: string[] = fs.readFileSync("input", "utf8").split("\n");
const doPart1 = (currentCycle: number, reg: number): number =>
  currentCycle == 20 ||
  currentCycle == 60 ||
  currentCycle == 100 ||
  currentCycle == 140 ||
  currentCycle == 180 ||
  currentCycle == 220
    ? currentCycle * reg
    : 0;

const drawCRT = (reg: number, horIdx: number) => {
  if (reg - 1 <= horIdx && reg + 1 >= horIdx) {
    process.stdout.write("█");
  } else {
    process.stdout.write(" ");
  }
};
(() => {
  let currentCycle = 0;
  let reg = 1;
  let part1Res = 0;
  let pop1 = 0;
  let pop2 = 0;
  let horIdx = 0;
  let line = "";
  console.log("Part 2: ");
  while (true) {
    currentCycle++;
    part1Res += doPart1(currentCycle, reg);
    drawCRT(reg, horIdx);
    pop1 = pop2;
    pop2 = 0;
    if (pop1 !== 0) {
      reg += pop1;
    } else {
      line = lines.shift() ?? " ";
    }
    if (line[0] === "a") {
      pop2 = parseInt(line.split(" ")[1]);
    } else if (!(pop1 != 0 || pop2 != 0 || line[0] === "n")) {
      break;
    }
    line = " ";
    horIdx =
      horIdx === 39
        ? (() => {
            console.log(" ");
            return 0;
          })()
        : horIdx + 1;
  }
  console.log("Part 1: ", part1Res);
})();
