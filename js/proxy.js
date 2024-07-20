const Downloader = new Proxy(
  {
    base: 1,
  },
  {
    get: function (target, prop, receiver) {
      const match = prop.match(/(.*?)(\d+)/);
      return target[match[1]] + +match[2];
    },
  },
);

console.log(Downloader.base1);
