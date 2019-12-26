#include <iomanip>
#include <iostream>
#include <sstream>

extern "C" {
#include <openssl/evp.h>
}

# define SM3_DIGEST_LENGTH 32

std::string to_hex(const uint8_t* str, size_t n) {
  std::ostringstream oss;
  oss << std::hex << std::setfill('0'); // << std::uppercase;
  for (auto i = 0; i < n; ++i) {
    oss << std::setw(2) << (unsigned int)str[i];
  }
  return oss.str();
}

int main(int argc, const char * argv[]) {
  if (argc < 2) {
    return -1;
  }

  const EVP_MD* sm3 = EVP_sm3();  // EVP_get_digestbynid(NID_sm3)
  assert(sm3 != nullptr);
  EVP_MD_CTX* sm3_ctx = EVP_MD_CTX_new();
  assert(sm3_ctx != nullptr);

  for (int i = 1; i < argc; ++i) {
    EVP_DigestInit_ex(sm3_ctx, sm3, nullptr);
    EVP_DigestUpdate(sm3_ctx, argv[i], strlen(argv[i]));
    uint8_t hash[SM3_DIGEST_LENGTH] = {};
    uint32_t size = sizeof (hash);
    EVP_DigestFinal_ex(sm3_ctx, hash, &size);
    std::cout << "SM3(\"" << argv[i] << "\") = " << to_hex(hash, sizeof (hash))
      << '\n';
  }
  EVP_MD_CTX_free(sm3_ctx);
  return 0;
}
