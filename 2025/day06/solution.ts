const fs = require("fs");

const data = fs.readFileSync("example", "utf8").split("\n").filter(Boolean);

console.log(data);
