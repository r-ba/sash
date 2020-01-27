#include <string>
#include "sash.h"

Sash::Sash(std::string seed) {
  this->initialize();
  this->load(seed);
}

// ensure buffer is empty
void Sash::initialize() {
  for (int i=0; i<32; i++) {
    this->buffer_[i] = 0;
  }
}

void Sash::update(std::string strChunk) {
  this->load(strChunk);
}

int hamming_weight(int n) {
  int count = 0;
  for (; n != 0;) {
    if ((n & 1) == 1) count++;
    n = n >> 1;
  }
  return count;
}

void Sash::cycle(int n) {
  int j;
  for (; n != 0 ; n--) {
    j = 0;
    for (int i=0; i<32; i++) {
      j = (j + this->buffer_[i]) % 256;
      this->buffer_[i] = j;
    }
  }
}

void Sash::load(std::string chunk) {
  int i = 0, n = 0;
  int prev_byte = 0, byte = 0;
  for (std::string::iterator chr=chunk.begin(); chr!=chunk.end(); ++chr) {
    byte = *chr;
    n += hamming_weight(byte);
    prev_byte = (prev_byte + byte) % 256;
    this->buffer_[i] = prev_byte;
    i = (i+1) % 32;
  }
  this->cycle(n);
}

// consume buffer and transform it into hex
std::string Sash::digest() {
  std::string hash = "0x";
  for (int i=0; i<32; i++) {
    hash += hexify(this->buffer_[i]);
    buffer_[i] = 0;
  }
  return hash;
}

// convert byte to it's corresponding hex representation
std::string Sash::hexify(uint8_t byte) {
  std::string alpha = "0123456789abcdef";
  std::string hex;
  for (int i=0; i<16; i++) {
    if (byte >= 16) {
      byte -= 16;
    } else {
      hex += alpha[i];
      break;
    }
  }
  hex += alpha[byte];
  return hex;
}
