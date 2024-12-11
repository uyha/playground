var p = new Promise((resolve, reject) => {
  resolve(1);
  reject(2);
  resolve(3);
});

p.then((x) => {
  console.log("resolved to " + x);
  return x;
})
  .then((x) => console.log(`more ${x}`))
  .catch((x) => console.log("never called " + x));

p.then((x) => console.log("one more " + x));
p.then((x) => console.log("two more " + x));
p.then((x) => console.log("three more " + x));
