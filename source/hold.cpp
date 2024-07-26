#include <fmt/format.h>
#include <hold/hold.h>
#include <hold/numberoperations.h>

#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <unordered_map>

VirtualMemory::VirtualMemory(std::size_t size) : memorySize(size) {
  memory = std::malloc(size);
  if (memory == nullptr) {
    throw std::bad_alloc();
  }
  freeList = static_cast<Block*>(memory);
  freeList->next = nullptr;
  freeList->free = true;
  freeList->size = size - sizeof(Block);
  usedList = nullptr;
}

VirtualMemory::~VirtualMemory() { std::free(memory); }

VirtualMemory::Block* VirtualMemory::findFreeBlock(std::size_t size) {
  Block* current = freeList;
  while (current != nullptr) {
    if (current->free && current->size >= size) {
      return current;
    }
    current = current->next;
  }
  return nullptr;
}

VirtualMemory::Block* VirtualMemory::requestBlock(std::size_t size) {
  Block* block = findFreeBlock(size);
  if (block != nullptr) {
    if (block->size > size + sizeof(Block)) {
      Block* newBlock
          = reinterpret_cast<Block*>(reinterpret_cast<char*>(block) + sizeof(Block) + size);
      newBlock->size = block->size - size - sizeof(Block);
      newBlock->free = true;
      newBlock->next = block->next;
      block->size = size;
      block->next = newBlock;
    }
    block->free = false;
    return block;
  }
  return nullptr;
}

void* VirtualMemory::malloc(std::size_t size) {
  Block* block = requestBlock(size);
  if (block == nullptr) {
    return nullptr;
  }
  return block->data;
}

void* VirtualMemory::calloc(std::size_t num, std::size_t size) {
  std::size_t totalSize = num * size;
  void* allocatedMemory = this->malloc(totalSize);
  if (allocatedMemory) {
    std::memset(allocatedMemory, 0, totalSize);
  }
  return allocatedMemory;
}

void* VirtualMemory::realloc(void* ptr, std::size_t size) {
  if (ptr == nullptr) {
    return this->malloc(size);
  }

  Block* block = reinterpret_cast<Block*>(reinterpret_cast<char*>(ptr) - offsetof(Block, data));
  if (block->size >= size) {
    return ptr;
  }

  void* newPtr = this->malloc(size);
  if (newPtr) {
    std::memcpy(newPtr, ptr, block->size);
    this->free(ptr);
  }
  return newPtr;
}

void VirtualMemory::free(void* ptr) {
  if (ptr == nullptr) {
    return;
  }

  Block* block = reinterpret_cast<Block*>(reinterpret_cast<char*>(ptr) - offsetof(Block, data));
  block->free = true;

  // Coalesce free blocks
  Block* current = freeList;
  while (current != nullptr) {
    if (current->free && current->next != nullptr && current->next->free) {
      current->size += current->next->size + sizeof(Block);
      current->next = current->next->next;
    } else {
      current = current->next;
    }
  }
}

void Hold::write(const void* value, size_t size) {
  const uint8_t* bytes = reinterpret_cast<const uint8_t*>(value);
  data.insert(data.end(), bytes, bytes + size);
}

const uint8_t* Hold::read() const { return data.data(); }

size_t Hold::size() const { return data.size(); }

double Hold::entropy() const {
  if (data.empty()) return 0.0;

  std::unordered_map<uint8_t, size_t> frequency;
  for (uint8_t byte : data) {
    ++frequency[byte];
  }

  double entropy = 0.0;
  // TODO maybe don't use c++17 here?
  for (const auto& [byte, count] : frequency) {
    double p = static_cast<double>(count) / data.size();
    entropy -= p * std::log2(p);
  }

  return entropy;
}
double Hold::theoreticalMaxCompression() {
  double t = Hold::entropy() * Hold::size();
  return t / 8;
}
// FIXME: this is not particularly great code
std::vector<int> Hold::maxSlices() { return Partition::n_findPartitionSizes(Hold::size()); }
