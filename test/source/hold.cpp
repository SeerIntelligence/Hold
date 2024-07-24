#include <doctest/doctest.h>
#include <hold/hold.h>
#include <hold/version.h>

#include <cstring>
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
TEST_CASE("Testing Hold class") {
  Hold h;

  SUBCASE("Write and read int") {
    int x = 42;
    h.write(x);
    CHECK(h.size() == sizeof(int));
    const int* ptr = reinterpret_cast<const int*>(h.read());
    CHECK(*ptr == x);
  }

  SUBCASE("Write and read double") {
    double d = 3.14159;
    h.write(d);
    CHECK(h.size() == sizeof(double));
    const double* ptr = reinterpret_cast<const double*>(h.read());
    CHECK(*ptr == d);
  }

  SUBCASE("Write and read raw bytes") {
    const char* str = "Hello, World!";
    size_t len = strlen(str) + 1;  // +1 for null terminator
    h.write(str, len);
    CHECK(h.size() == len);
    const char* ptr = reinterpret_cast<const char*>(h.read());
    CHECK(strcmp(ptr, str) == 0);
  }
}
TEST_CASE("Testing theoreticalMaxCompression calculation") {
  Hold h;

  SUBCASE("TheoreticalMaxCompression of empty data") {
    CHECK(h.theoreticalMaxCompression() == 0.0);
  }

  SUBCASE("TheoreticalMaxCompression of single byte data") {
    uint8_t byte = 0xFF;
    h.write(byte);
    CHECK(h.theoreticalMaxCompression() == 0.0);
  }

  SUBCASE("TheoreticalMaxCompression of multiple different bytes") {
    uint8_t bytes[] = {0x00, 0xFF, 0x00, 0xFF};
    h.write(bytes, sizeof(bytes));
    CHECK(h.theoreticalMaxCompression() > 0.0);
  }

  SUBCASE("TheoreticalMaxCompression of multiple identical bytes") {
    uint8_t bytes[] = {0xAA, 0xAA, 0xAA, 0xAA};
    h.write(bytes, sizeof(bytes));
    CHECK(h.theoreticalMaxCompression() == 0.0);
  }
  // TODO TESTCASE for pre-calculated entropies (accuracy)
}
