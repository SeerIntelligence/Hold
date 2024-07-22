#include <doctest/doctest.h>
#include <hold/hold.h>
#include <hold/version.h>

#include <string>

TEST_CASE("VirtualMemory allocation and deallocation") {
  std::size_t memorySize = 1024;  // 1 KB of virtual memory
  VirtualMemory vm(memorySize);

  SUBCASE("Allocate 256 bytes") {
    void* ptr1 = vm.malloc(256);
    REQUIRE(ptr1 != nullptr);
  }

  SUBCASE("Allocate and free memory") {
    void* ptr1 = vm.malloc(256);
    REQUIRE(ptr1 != nullptr);
    vm.free(ptr1);
  }

  SUBCASE("Allocate more than available memory") {
    void* ptr1 = vm.malloc(2048);
    REQUIRE(ptr1 == nullptr);
  }

  SUBCASE("Reallocate memory to a larger size") {
    void* ptr1 = vm.malloc(128);
    REQUIRE(ptr1 != nullptr);
    void* ptr2 = vm.realloc(ptr1, 512);
    REQUIRE(ptr2 != nullptr);
  }

  SUBCASE("Reallocate memory to a smaller size") {
    void* ptr1 = vm.malloc(512);
    REQUIRE(ptr1 != nullptr);
    void* ptr2 = vm.realloc(ptr1, 128);
    REQUIRE(ptr2 != nullptr);
  }

  SUBCASE("Calloc initializes memory to zero") {
    void* ptr1 = vm.calloc(64, sizeof(char));
    REQUIRE(ptr1 != nullptr);
    bool isZero = true;
    for (std::size_t i = 0; i < 64; ++i) {
      if (static_cast<char*>(ptr1)[i] != 0) {
        isZero = false;
        break;
      }
    }
    REQUIRE(isZero);
  }

  SUBCASE("Free and reuse memory") {
    void* ptr1 = vm.malloc(256);
    REQUIRE(ptr1 != nullptr);
    vm.free(ptr1);

    void* ptr2 = vm.malloc(256);
    REQUIRE(ptr2 != nullptr);
    REQUIRE(ptr1 == ptr2);
  }

  SUBCASE("Coalesce free blocks") {
    void* ptr1 = vm.malloc(256);
    REQUIRE(ptr1 != nullptr);
    void* ptr2 = vm.malloc(256);
    REQUIRE(ptr2 != nullptr);

    vm.free(ptr1);
    vm.free(ptr2);

    void* ptr3 = vm.malloc(512);
    REQUIRE(ptr3 != nullptr);
    REQUIRE(ptr3 == ptr1);
  }
}
