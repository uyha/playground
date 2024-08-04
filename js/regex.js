const str = `\r\n`;

const strings = [`\r\n`, `\r`, `\n`, `\n\r`, `\n\ra`];

for (const str of strings) {
  console.log(str.match(/^\r\n|\r|\n$/));
}

/[^\r]\n/;
/\r[^\n]/;
/\r\n/;

/[^\r]\n\r/;
/[^\r]\n\n/;
/[^\r]\n\r\n/;
