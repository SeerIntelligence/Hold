#include <algorithm>
#include <random>
#include <vector>

class ShuffleArray {
public:
  ShuffleArray();

  std::vector<int> shuffle(std::vector<uint8_t>& data);
  void reassemble(std::vector<uint8_t>& data, const std::vector<int>& code);

private:
  std::mt19937 rng;
};
