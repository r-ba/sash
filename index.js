const sash = require('./build/Release/sash.node');

module.exports = {
  create: (seed) => new sash.create(seed)
};
