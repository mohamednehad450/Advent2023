import { readFileSync } from "node:fs";

const nums = [
  "one",
  "two",
  "three",
  "four",
  "five",
  "six",
  "seven",
  "eight",
  "nine",
];

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
    const index = nums.findIndex((str) => line.slice(0, i + 1).includes(str));
    if (index > -1) {
      str += index + 1;
      break;
    }
  }

  for (let i = line.length; i >= 0; i--) {
    const char = line[i];
    if (!isNaN(Number(char))) {
      str += char;
      break;
    }
    const index = nums.findIndex((str) =>
      line.slice(i, line.length).includes(str)
    );
    if (index > -1) {
      str += index + 1;
      break;
    }
  }

  digits.push(Number(str));
}

console.log(digits.reduce((acc, n) => acc + n));
