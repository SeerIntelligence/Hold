#include <vector>
class NumberOperations {
private:
  int number;

public:
  // Constructor
  NumberOperations(int num);

  // Getters and Setters
  int getNumber() const;
  void setNumber(int num);

  // Number Operations
  bool isEven() const;
  bool isOdd() const;
  bool isPositive() const;
  bool isNegative() const;
  bool isZero() const;
  int factorial() const;
  bool isPrime() const;
  int absoluteValue() const;
  int square() const;
  int cube() const;
};

class Partition {
public:
  static std::vector<int> findPartitionSizes(const std::vector<int>& list);
  static std::vector<int> n_findPartitionSizes(int listlength);
  static std::vector<std::vector<std::vector<int>>> generatePartitions(
      const std::vector<int>& list, const std::vector<int>& partitionSizes);
  static void printPartitions(const std::vector<std::vector<std::vector<int>>>& partitions);
};
