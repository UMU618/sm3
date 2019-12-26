#include <iomanip>
#include <iostream>
#include <sstream>

extern "C" {
#include "internal/sm3.h"
}

std::string to_hex(const uint8_t* str, size_t n) {
  std::ostringstream oss;
  oss << std::hex << std::setfill('0'); // << std::uppercase;
  for (auto i = 0; i < n; ++i) {
    oss << std::setw(2) << (unsigned int)str[i];
  }
  return oss.str();
}

int main(int argc, const char * argv[]) {
  for (int i = 1; i < argc; ++i) {
    SM3_CTX sm3_ctx = {};
    uint8_t hash[SM3_DIGEST_LENGTH] = {};
    sm3_init(&sm3_ctx);
    sm3_update(&sm3_ctx, argv[i], strlen(argv[i]));
    sm3_final(hash, &sm3_ctx);
    std::cout << "SM3(\"" << argv[i] << "\") = " << to_hex(hash, sizeof (hash))
      << '\n';
  }
  return 0;
}
