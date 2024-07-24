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
