#include "hold/numberoperations.h"

// Constructor
NumberOperations::NumberOperations(int num) : number(num) {}

// Getters and Setters
int NumberOperations::getNumber() const { return number; }

void NumberOperations::setNumber(int num) { number = num; }

// Number Operations
bool NumberOperations::isEven() const { return number % 2 == 0; }

bool NumberOperations::isOdd() const { return !isEven(); }

bool NumberOperations::isPositive() const { return number > 0; }

bool NumberOperations::isNegative() const { return number < 0; }

bool NumberOperations::isZero() const { return number == 0; }

int NumberOperations::factorial() const {
  if (number < 0) return -1;  // Factorial of negative numbers is undefined
  int result = 1;
  for (int i = 1; i <= number; ++i) {
    result *= i;
  }
  return result;
}

bool NumberOperations::isPrime() const {
  if (number <= 1) return false;
  for (int i = 2; i <= number / 2; ++i) {
    if (number % i == 0) return false;
  }
  return true;
}

int NumberOperations::absoluteValue() const { return number < 0 ? -number : number; }

int NumberOperations::square() const { return number * number; }

int NumberOperations::cube() const { return number * number * number; }
