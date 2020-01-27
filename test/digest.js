const fs = require('fs');
const expect = require('chai').expect;
const sash = require('../index.js');

describe('create()', function(){

  it('Empty initialization: create()', function() {
    const s = sash.create();
    expect(s.digest()).to.equal("0x75cc611bb69638c08fc7dfe3044c9adaafb943cb1e2ee4acfdbdb5b1406862b2");
  });

  it('String "hello world!": create()', function() {
    const s = sash.create("hello world!");
    expect(s.digest()).to.equal("0x68e51c247facdfc71e1ac8a5d5ac0276a4c1f86e6530bb57bebc5cf527506858");
  });

  it('File "binding.gyp": create()', function() {
    const s = sash.create();
    let fileContent;
    fs.createReadStream("binding.gyp", { encoding: 'utf8' }).on('data', chunk => {
      fileContent += chunk;
    }).on('end', () => {
      s.update(fileContent);
      expect(s.digest()).to.equal("0x87c01efc2c70482d632ec32011719a66b6fe4a2122d610d819f884bd2fadeab0");
    });
  });

});

describe('update()', function(){

  it('Empty initialization: update()', function() {
    const s = sash.create();
    s.update("");
    expect(s.digest()).to.equal("0x75cc611bb69638c08fc7dfe3044c9adaafb943cb1e2ee4acfdbdb5b1406862b2");
  });

  it('String "hello world!": update()', function() {
    const s = sash.create();
    s.update("hello world!");
    expect(s.digest()).to.equal("0x68e51c247facdfc71e1ac8a5d9b43056f9bb62b64ce8fdef19986821ac383418");
  });

  it('File "binding.gyp": update()', function() {
    const s = sash.create();
    fs.createReadStream("binding.gyp", { encoding: 'utf8' }).on('data', chunk => {
      s.update(chunk);
    }).on('end', () => {
      expect(s.digest()).to.equal("0x3ecdaa34ecd2f4213fd587fc671ee6c832cef9a430cb9c6b3344b3178d5bfd62");
    });
  });

});
