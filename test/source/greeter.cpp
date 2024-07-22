#include <doctest/doctest.h>
#include <hold/hold.h>
#include <hold/version.h>

#include <string>

TEST_CASE("Greeter") {
  using namespace hold;

  Hold hold("Tests");

  CHECK(hold.greet(LanguageCode::EN) == "Hello, Tests!");
  CHECK(hold.greet(LanguageCode::DE) == "Hallo Tests!");
  CHECK(hold.greet(LanguageCode::ES) == "¡Hola Tests!");
  CHECK(hold.greet(LanguageCode::FR) == "Bonjour Tests!");
}
