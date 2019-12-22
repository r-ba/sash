const fs = require('fs');
const expect = require('chai').expect;
const sash = require('../index.js');

describe('Digested hashes', function(){

  it('Empty initialization', function() {
    const s = sash.create();
    expect( s.digest() ).to.equal("0x75CC611BB69638C08FC7DFE3044C9ADAAFB943CB1E2EE4ACFDBDB5B1406862B2");
  });

  it('String: "hello world!"', function() {
    const s = sash.create("hello world!");
    expect( s.digest() ).to.equal("0x68E51C247FACDFC71E1AC8A5D5AC0276A4C1F86E6530BB57BEBC5CF527506858");
  });

  it('File: "binding.gyp"', function() {
    const s = sash.create();
    fs.createReadStream("binding.gyp", { encoding: 'utf8' }).on('data', chunk => {
      s.update(chunk);
    }).on('end', () => {
      expect(s.digest()).to.equal("0x3ECDAA34ECD2F4213FD587FC671EE6C832CEF9A430CB9C6B3344B3178D5BFD62");
    });
  })

});
