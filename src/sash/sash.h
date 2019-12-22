class Sash {
public:
  Sash(std::string);
  void update(std::string);
  std::string digest();
private:
  uint8_t buffer_ [32];
  void initialize();
  void load(std::string);
  void cycle(int);
  std::string hexify(uint8_t);
};
