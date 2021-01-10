#include "server/server_request.h"

#include <unistd.h>

#include "util/coding.h"

constexpr size_t kLengthSize = sizeof(std::uint32_t);

namespace pseudogoogle {

ServerRequest::ServerRequest(int socket_fd) {
  char length_buffer[kLengthSize];
  ReadToBuffer(socket_fd, length_buffer, kLengthSize);
  std::uint32_t length = DecodeFixed32(length_buffer);

  char* word_buffer = new char[length];
  ReadToBuffer(socket_fd, word_buffer, length);
  word_ = std::string(word_buffer, length);
}

void ServerRequest::ReadToBuffer(int socket_fd, char* buffer,
                                 size_t buffer_size) {
  size_t read_count = 0;
  while (read_count != buffer_size) {
    read_count += read(socket_fd, buffer, buffer_size - read_count);
  }
}

}  // namespace pseudogoogle
