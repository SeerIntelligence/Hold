#include <fmt/format.h>
#include <hold/hold.h>

#include <cstdlib>
#include <cstring>
#include <stdexcept>

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
