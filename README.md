# Sash

[![master branch tests](https://img.shields.io/travis/r-ba/sash/master.svg?label=master%20branch)](https://travis-ci.com/r-ba/sash)
[![GitHub license](https://img.shields.io/badge/License-MIT-blue.svg)](https://raw.githubusercontent.com/r-ba/sash/master/LICENSE)

An experimental hashing algorithm implemented in C++, provided with bindings for use as a node.js addon.

*Please be advised that this project should only be used in non-critical applications or for educational purposes only.*

## Build instructions for Node

First install dependencies with `npm install` and then build the project with `npm run build`.

## Example usage with Node

Hashing a string:
```js
const sash = require('./index.js');

const s = sash.create("hello world");
console.log(s.digest()); // 0x6815bad153d206b56fa5b2b25a48045a06138eb1cbca8e7d076b06b0840450a8
```

Hashing a stream:
```js
const fs = require('fs');
const sash = require('./index.js');

const s = sash.create();
fs.createReadStream("package.json", { encoding: 'utf8' }).on('data', chunk => {
  s.update(chunk);
}).on('end', () => {
  console.log(s.digest()); // 0xfb647bf24bf097e0f46222e056f4be828247d6a7c46d27c94547825a639cd7d3
});
```

## Standalone example

Consider the following `main.cpp` program:

```c++
#include <iostream>
#include "sash.h"

int main() {

  Sash sash("");
  std::string line;

  while (std::getline(std::cin, line)) {
   sash.update(line);
  }

  std::cout << sash.digest() << std::endl;

  return 0;
}
```

After building with e.g. `g++ -o sash main.cpp sash.cpp`, you may pipe in files from stdin.

```
$ cat main.cpp | ./sash
0x7daeb3e35533af49b2dbdbab246dfebc3f5a17b9f521f8c7aeb1fe4d7f1be56b
```
