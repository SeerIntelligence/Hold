#include "hold/numberoperations.h"

#include <iostream>

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

std::vector<int> Partition::findPartitionSizes(const std::vector<int>& list) {
  std::vector<int> partitionSizes;
  int n = list.size();

  for (int size = n; size > 0; --size) {
    if (n % size == 0) {
      partitionSizes.push_back(size);
    }
  }

  return partitionSizes;
}

std::vector<int> Partition::n_findPartitionSizes(int listlength) {
  std::vector<int> partitionSizes;
  for (int size = listlength; size > 0; --size) {
    if (listlength % size == 0) {
      partitionSizes.push_back(size);
    }
  }

  return partitionSizes;
}
std::vector<std::vector<std::vector<int>>> Partition::generatePartitions(
    const std::vector<int>& list, const std::vector<int>& partitionSizes) {
  std::vector<std::vector<std::vector<int>>> partitions;
  int n = list.size();

  for (int size : partitionSizes) {
    std::vector<std::vector<int>> partition;
    for (int i = 0; i < n; i += size) {
      partition.push_back(std::vector<int>(list.begin() + i, list.begin() + i + size));
    }
    partitions.push_back(partition);
  }

  return partitions;
}

void Partition::printPartitions(const std::vector<std::vector<std::vector<int>>>& partitions) {
  for (const auto& partition : partitions) {
    std::cout << "[ ";
    for (const auto& sublist : partition) {
      std::cout << "[ ";
      for (int elem : sublist) {
        std::cout << elem << " ";
      }
      std::cout << "] ";
    }
    std::cout << "]" << std::endl;
  }
}
