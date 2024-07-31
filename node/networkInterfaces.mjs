#!/usr/bin/env node

import { networkInterfaces } from "node:os";

console.log(
  Object.values(networkInterfaces())
    .flat()
    .filter((item) => !item.internal)[0],
);
