import { readFileSync } from "node:fs";

const file: string = readFileSync("./input.txt", "utf8");

const lines = file.split("\n");

const digits: number[] = [];

for (const line of lines) {
  let str = "";
  for (let i = 0; i < line.length; i++) {
    const char = line[i];
    if (!isNaN(Number(char))) {
      str += char;
      break;
    }
  }

  for (let i = line.length + 1; i >= 0; i--) {
    const char = line[i];
    if (!isNaN(Number(char))) {
      str += char;
      break;
    }
  }

  digits.push(Number(str));
}

console.log(digits.reduce((acc, n) => acc + n));
