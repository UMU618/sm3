#include <iostream>
#include <string>

#include <boost/assert.hpp>

#include <fast_io.h>

extern "C" {
#include <openssl/evp.h>
}

constexpr size_t kBlake2b512DigestLength{64};

std::string ToHex(std::span<const uint8_t> bytes) {
  std::string hex;
  hex.resize(bytes.size() * 2);
  for (size_t pos = 0; const auto& b : bytes) {
    std::memcpy(
        hex.data() + pos,
        fast_io::concat(fast_io::mnp::right(fast_io::mnp::hex(b), 2, '0'))
            .data(),
        2);
    pos += 2;
  }
  return hex;
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    return -1;
  }

  const EVP_MD* b2b = EVP_blake2b512();
  BOOST_ASSERT(b2b);
  EVP_MD_CTX* b2b_ctx = EVP_MD_CTX_new();
  BOOST_ASSERT(b2b_ctx);

  for (int i = 1; i < argc; ++i) {
    EVP_DigestInit_ex(b2b_ctx, b2b, nullptr);
    EVP_DigestUpdate(b2b_ctx, argv[i], strlen(argv[i]));
    uint8_t hash[kBlake2b512DigestLength] = {};
    uint32_t size = sizeof(hash);
    EVP_DigestFinal_ex(b2b_ctx, hash, &size);
    std::cout << "blake2b512(\"" << argv[i]
              << "\") = " << ToHex({hash, sizeof(hash)}) << '\n';
  }
  EVP_MD_CTX_free(b2b_ctx);
}
