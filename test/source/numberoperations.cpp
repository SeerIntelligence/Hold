
#include <doctest/doctest.h>
#include <hold/numberoperations.h>
TEST_CASE("Testing NumberOperations class") {
  NumberOperations numOp(5);
  // TODO: get a life
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
