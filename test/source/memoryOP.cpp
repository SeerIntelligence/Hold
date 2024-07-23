#include <doctest/doctest.h>
#include <hold/hold.h>
#include <hold/memoryOP.h>
#include <hold/version.h>

#include <string>

TEST_CASE("ShuffleArray shuffle and reassemble") {
  ShuffleArray shuffler;

  SUBCASE("Shuffle and reassemble with 10 elements") {
    std::vector<uint8_t> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<uint8_t> original = data;

    std::vector<int> code = shuffler.shuffle(data);
    REQUIRE(data != original);

    shuffler.reassemble(data, code);
    REQUIRE(data == original);
  }

  SUBCASE("Shuffle and reassemble with 0 elements") {
    std::vector<uint8_t> data;
    std::vector<uint8_t> original = data;

    std::vector<int> code = shuffler.shuffle(data);
    REQUIRE(data == original);

    shuffler.reassemble(data, code);
    REQUIRE(data == original);
  }

  SUBCASE("Shuffle and reassemble with 1 element") {
    std::vector<uint8_t> data = {42};
    std::vector<uint8_t> original = data;

    std::vector<int> code = shuffler.shuffle(data);
    REQUIRE(data == original);

    shuffler.reassemble(data, code);
    REQUIRE(data == original);
  }

  SUBCASE("Shuffle and reassemble with 1000 elements") {
    std::vector<uint8_t> data(1000);
    std::iota(data.begin(), data.end(), 0);
    std::vector<uint8_t> original = data;

    std::vector<int> code = shuffler.shuffle(data);
    REQUIRE(data != original);

    shuffler.reassemble(data, code);
    REQUIRE(data == original);
  }

  SUBCASE("Reassemble with incorrect code") {
    std::vector<uint8_t> data = {1, 2, 3, 4, 5};
    std::vector<uint8_t> original = data;

    std::vector<int> code = shuffler.shuffle(data);
    REQUIRE(data != original);

    std::vector<int> incorrectCode = code;
    std::reverse(incorrectCode.begin(), incorrectCode.end());
    shuffler.reassemble(data, incorrectCode);
    REQUIRE(data != original);
  }
}
