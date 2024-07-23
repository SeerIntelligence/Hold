#include <hold/memoryOP.h>

#include <ctime>
#include <numeric>

ShuffleArray::ShuffleArray() { rng.seed(std::random_device()()); }

std::vector<int> ShuffleArray::shuffle(std::vector<uint8_t>& data) {
  std::vector<int> code(data.size());
  std::iota(code.begin(), code.end(), 0);
  std::shuffle(code.begin(), code.end(), rng);

  std::vector<uint8_t> original(data);
  for (size_t i = 0; i < data.size(); ++i) {
    data[i] = original[code[i]];
  }

  return code;
}

void ShuffleArray::reassemble(std::vector<uint8_t>& data, const std::vector<int>& code) {
  std::vector<uint8_t> shuffled(data.size());
  for (size_t i = 0; i < data.size(); ++i) {
    shuffled[code[i]] = data[i];
  }
  data = shuffled;
}
