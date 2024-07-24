#pragma once

#include <cstddef>
#include <string>
#include <vector>

class VirtualMemory {
public:
  VirtualMemory(std::size_t size);
  ~VirtualMemory();

  void* malloc(std::size_t size);
  void* calloc(std::size_t num, std::size_t size);
  void* realloc(void* ptr, std::size_t size);
  void free(void* ptr);

private:
  struct Block {
    Block* next;
    bool free;
    std::size_t size;
    char data[1];  // Flexible array member for block data
  };

  Block* findFreeBlock(std::size_t size);
  Block* requestBlock(std::size_t size);

  void* memory;
  std::size_t memorySize;
  Block* freeList;
  Block* usedList;

  // Disable copy constructor and assignment operator
  VirtualMemory(const VirtualMemory&) = delete;
  VirtualMemory& operator=(const VirtualMemory&) = delete;
};
class Hold {
private:
  std::vector<uint8_t> data;

  double entropy() const;

public:
  template <typename T> void write(const T& value);

  void write(const void* value, size_t size);

  const uint8_t* read() const;

  size_t size() const;
  double theoreticalMaxCompression();
};

template <typename T> void Hold::write(const T& value) {
  const uint8_t* bytes = reinterpret_cast<const uint8_t*>(&value);
  data.insert(data.end(), bytes, bytes + sizeof(T));
}
