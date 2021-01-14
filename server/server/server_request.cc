#include "server/server_request.h"

#include <unistd.h>

#include <algorithm>
#include <regex>

#include "util/coding.h"
#include "util/word_splitter.h"

constexpr size_t kLengthSize = sizeof(std::uint32_t);

namespace pseudogoogle {

ServerRequest::ServerRequest(int socket_fd) {
  char length_buffer[kLengthSize];
  ReadToBuffer(socket_fd, length_buffer, kLengthSize);
  std::uint32_t length = DecodeFixed32(length_buffer);

  char* query_string_buffer = new char[length];
  ReadToBuffer(socket_fd, query_string_buffer, length);
  query_string_ = std::string(query_string_buffer, length);
  std::transform(query_string_.begin(), query_string_.end(),
                 query_string_.begin(), [](char c) { return std::tolower(c); });

  SplitQueryString();
}

void ServerRequest::SplitQueryString() {
  for (std::smatch match : WordSplitter(query_string_)) {
    std::string word = match.str();
    words_.insert(word);
  }
}

void ServerRequest::ReadToBuffer(int socket_fd, char* buffer,
                                 size_t buffer_size) {
  size_t read_count = 0;
  while (read_count != buffer_size) {
    read_count += read(socket_fd, buffer, buffer_size - read_count);
  }
}

}  // namespace pseudogoogle
