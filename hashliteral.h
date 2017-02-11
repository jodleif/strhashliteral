#pragma once
/*
 * Fnv-1a constexpr implementation
 * SEE: http://isthe.com/chongo/tech/comp/fnv/#FNV-1a
 * */
#include <cstdint>
#include <string>
namespace hash {
constexpr static uint32_t fnv_32_prime{16'777'619u};
constexpr static uint32_t fnv_32_offset_basis{2'166'136'261u};

/*
 * 	Hash until null-termination
 * 		*/
inline constexpr uint32_t fnv_32_hash(const char *to_hash) {
  uint32_t hash{fnv_32_offset_basis};
  const char *hashit{to_hash};
  for (;; hashit++) {
    if (*hashit == 0)
      break;
    hash *= fnv_32_prime;
    hash ^= *hashit;
  }
  return hash;
}
/*
 * 	Hash until length
 * 		*/
inline constexpr uint32_t fnv_32_hash(const char *to_hash, size_t length) {
  uint32_t hash{fnv_32_offset_basis};
  const char *hashit{to_hash};

  for (size_t i{0}; i < length; i++, hashit++) {
    hash *= fnv_32_prime;
    hash ^= *hashit;
  }
  return hash;
}

inline uint32_t fnv_32_hash(const std::string &to_hash) {
  return fnv_32_hash(to_hash.c_str(), to_hash.length());
}

constexpr static uint64_t fnv_64_prime{1'099'511'628'211ull};
constexpr static uint64_t fnv_64_offset_basis{14'695'981'039'346'656'037ull};

/*
 * 	Hash until null-termination
 * 		*/
inline constexpr uint64_t fnv_64_hash(const char *to_hash) {
  uint64_t hash{fnv_64_offset_basis};
  const char *hashit{to_hash};
  for (;; hashit++) {
    if (*hashit == 0)
      break;
    hash = hash * fnv_64_prime;
    hash = hash ^ *hashit;
  }
  return hash;
}

inline constexpr uint64_t fnv_64_hash(const char *to_hash, size_t len) {
  uint64_t hash{fnv_64_offset_basis};
  const char *hashit{to_hash};

  for (size_t i{0}; i < len; i++, hashit++) {
    hash = hash * fnv_64_prime;
    hash = hash ^ *hashit;
  }
  return hash;
}

namespace literals {
inline constexpr uint32_t operator"" _f32(const char *string, size_t len) {
  return hash::fnv_32_hash(string, len);
}

inline constexpr uint64_t operator""_f64(const char *string, size_t len) {
  return hash::fnv_64_hash(string, len);
}
} // namespace literals end

} // namespace hash end
