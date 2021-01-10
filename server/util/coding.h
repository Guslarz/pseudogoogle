#ifndef PSEUDOGOOGLE_UTIL_CODING_H
#define PSEUDOGOOGLE_UTIL_CODING_H

#include <cstdint>

namespace pseudogoogle {

inline void EncodeFixed32(char* dst, const std::uint32_t& value) {
  std::uint8_t* const buffer = reinterpret_cast<std::uint8_t*>(dst);

  buffer[0] = static_cast<std::uint8_t>(value);
  buffer[1] = static_cast<std::uint8_t>(value >> 8);
  buffer[2] = static_cast<std::uint8_t>(value >> 16);
  buffer[3] = static_cast<std::uint8_t>(value >> 24);
}

inline std::uint32_t DecodeFixed32(const char* src) {
  const std::uint8_t* const buffer = reinterpret_cast<const std::uint8_t*>(src);

  return (static_cast<std::uint32_t>(buffer[0])) |
         (static_cast<std::uint32_t>(buffer[1]) << 8) |
         (static_cast<std::uint32_t>(buffer[2]) << 16) |
         (static_cast<std::uint32_t>(buffer[3]) << 24);
}

}  // namespace pseudogoogle

#endif  // PSEUDOGOOGLE_UTIL_CODING_H