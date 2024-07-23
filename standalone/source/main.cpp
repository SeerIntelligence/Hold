#include <hold/hold.h>
#include <hold/memoryOP.h>
#include <hold/version.h>

#include <cxxopts.hpp>
#include <iostream>
#include <string>
#include <unordered_map>

auto main() -> int {
  std::size_t memorySize = 1024;  // 1 KB of virtual memory
  VirtualMemory vm(memorySize);

  // Allocate 256 bytes
  void* ptr1 = vm.malloc(256);
  if (ptr1) {
    std::cout << "Allocated 256 bytes." << std::endl;
  } else {
    std::cout << "Failed to allocate 256 bytes." << std::endl;
  }

  // Allocate 128 bytes
  void* ptr2 = vm.malloc(128);
  if (ptr2) {
    std::cout << "Allocated 128 bytes." << std::endl;
  } else {
    std::cout << "Failed to allocate 128 bytes." << std::endl;
  }

  // Free the first 256 bytes
  vm.free(ptr1);
  std::cout << "Freed 256 bytes." << std::endl;

  // Reallocate the second block to 512 bytes
  void* ptr3 = vm.realloc(ptr2, 512);
  if (ptr3) {
    std::cout << "Reallocated 128 bytes to 512 bytes." << std::endl;
  } else {
    std::cout << "Failed to reallocate 128 bytes to 512 bytes." << std::endl;
  }

  // Allocate 64 zero-initialized bytes
  void* ptr4 = vm.calloc(64, sizeof(char));
  if (ptr4) {
    std::cout << "Allocated 64 zero-initialized bytes." << std::endl;
  } else {
    std::cout << "Failed to allocate 64 zero-initialized bytes." << std::endl;
  }

  // Free all remaining allocations
  vm.free(ptr3);
  std::cout << "Freed 512 bytes." << std::endl;
  vm.free(ptr4);
  std::cout << "Freed 64 zero-initialized bytes." << std::endl;

  ShuffleArray shuffler;

  std::vector<uint8_t> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::cout << "Original data: ";
  for (const auto& byte : data) {
    std::cout << static_cast<int>(byte) << " ";
  }
  std::cout << std::endl;

  std::vector<int> code = shuffler.shuffle(data);
  std::cout << "Shuffled data: ";
  for (const auto& byte : data) {
    std::cout << static_cast<int>(byte) << " ";
  }
  std::cout << std::endl;

  shuffler.reassemble(data, code);
  std::cout << "Reassembled data: ";
  for (const auto& byte : data) {
    std::cout << static_cast<int>(byte) << " ";
  }
  std::cout << std::endl;

  return 0;
}
