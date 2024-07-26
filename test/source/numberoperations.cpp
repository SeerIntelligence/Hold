
#include <doctest/doctest.h>
#include <hold/numberoperations.h>

#include <cstddef>
TEST_CASE("Testing NumberOperations class") {
  NumberOperations numOp(5);
  // TODO: get a life
  //
  // Where did I go wrong? What should I have done instead?
  // When your mind starts looking for answers to these,
  // is when you realize you are in deep trouble.

  SUBCASE("Test isEven") { CHECK(numOp.isEven() == false); }

  SUBCASE("Test isOdd") { CHECK(numOp.isOdd() == true); }

  SUBCASE("Test isPositive") { CHECK(numOp.isPositive() == true); }

  SUBCASE("Test isNegative") { CHECK(numOp.isNegative() == false); }

  SUBCASE("Test isZero") { CHECK(numOp.isZero() == false); }

  SUBCASE("Test factorial") { CHECK(numOp.factorial() == 120); }

  SUBCASE("Test isPrime") { CHECK(numOp.isPrime() == true); }

  SUBCASE("Test absoluteValue") {
    NumberOperations negativeNumOp(-5);
    CHECK(negativeNumOp.absoluteValue() == 5);
  }

  SUBCASE("Test square") { CHECK(numOp.square() == 25); }

  SUBCASE("Test cube") { CHECK(numOp.cube() == 125); }
}
// Helper function to compare vectors of vectors
bool comparePartitions(const std::vector<std::vector<int>>& a,
                       const std::vector<std::vector<int>>& b) {
  if (a.size() != b.size()) return false;
  for (size_t i = 0; i < a.size(); ++i) {
    if (a[i] != b[i]) return false;
  }
  return true;
}

TEST_CASE("Testing Partition class") {
  SUBCASE("Test findPartitionSizes") {
    std::vector<int> list = {1, 2, 3, 4};
    std::vector<int> expectedSizes = {4, 2, 1};
    CHECK(Partition::findPartitionSizes(list) == expectedSizes);

    list = {1, 2, 3, 4, 5, 6};
    expectedSizes = {6, 3, 2, 1};
    CHECK(Partition::findPartitionSizes(list) == expectedSizes);
  }

  SUBCASE("Test generatePartitions") {
    std::vector<int> list = {1, 2, 3, 4};
    std::vector<int> partitionSizes = {4, 2, 1};
    std::vector<std::vector<std::vector<int>>> expectedPartitions
        = {{{1, 2, 3, 4}}, {{1, 2}, {3, 4}}, {{1}, {2}, {3}, {4}}};
    CHECK(Partition::generatePartitions(list, partitionSizes) == expectedPartitions);

    list = {1, 2, 3, 4, 5, 6};
    partitionSizes = {6, 3, 2, 1};
    expectedPartitions = {{{1, 2, 3, 4, 5, 6}},
                          {{1, 2, 3}, {4, 5, 6}},
                          {{1, 2}, {3, 4}, {5, 6}},
                          {{1}, {2}, {3}, {4}, {5}, {6}}};
    CHECK(Partition::generatePartitions(list, partitionSizes) == expectedPartitions);
  }
}
