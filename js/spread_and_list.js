function sep(...keywords) {
  return keywords.map((keyword) => `${keyword}n`);
}

console.log(sep("NOT", "AND"));
