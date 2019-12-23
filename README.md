![Sash logo](https://i.ibb.co/zbTz7PG/sash.png)

# Sash

[![master branch tests](https://img.shields.io/travis/r-ba/sash/master.svg?label=master%20branch)](https://travis-ci.com/r-ba/sash)
[![GitHub license](https://img.shields.io/badge/License-MIT-blue.svg)](https://raw.githubusercontent.com/r-ba/sash/master/LICENSE)

A custom hashing algorithm add-on for node.js, written in C++.

*Please be advised that the cryptographic strength of this project has yet to be verified. It should therefore be used in non-critical applications or for educational purposes only.*

## Build instructions

Install dependencies and build the project with `npm run install`.

## Example usage

Hashing a string:
```js
const sash = require('./index.js');

const s = sash.create("hello world");
console.log(s.digest()); // 0x6815BAD153D206B56FA5B2B25A48045A06138EB1CBCA8E7D076B06B0840450A8
```

Hashing a stream:
```js
const fs = require('fs');
const sash = require('./index.js');

const s = sash.create();
fs.createReadStream("package.json", { encoding: 'utf8' }).on('data', chunk => {
  s.update(chunk);
}).on('end', () => {
  console.log(s.digest()); // 0xFB647BF24BF097E0F46222E056F4BE828247D6A7C46D27C94547825A639CD7D3
});
```
