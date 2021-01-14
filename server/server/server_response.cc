#include "server/server_response.h"

#include <unistd.h>

#include <cstring>
#include <set>
#include <unordered_set>

#include "util/coding.h"

namespace pseudogoogle {

ServerResponse::ServerResponse(
    const std::unordered_set<std::string>& words,
    const std::set<Record, RecordOrderComparator>& result) {
  // set buffer length and allocate buffer
  buffer_length_ = 8;
  for (const auto& word : words) {
    buffer_length_ += 4 + word.size();
  }
  for (const auto& record : result) {
    buffer_length_ += 4 + record.Url().size();
  }
  buffer_ = new char[buffer_length_];

  // fill buffer
  char* buffer_ptr = buffer_;
  EncodeFixed32(buffer_ptr, words.size());
  buffer_ptr += 4;
  for (const auto& word : words) {
    EncodeFixed32(buffer_ptr, word.size());
    buffer_ptr += 4;
    memcpy(buffer_ptr, word.c_str(), word.size());
    buffer_ptr += word.size();
  }

  EncodeFixed32(buffer_ptr, result.size());
  buffer_ptr += 4;
  for (const auto& record : result) {
    EncodeFixed32(buffer_ptr, record.Url().size());
    buffer_ptr += 4;
    memcpy(buffer_ptr, record.Url().c_str(), record.Url().size());
    buffer_ptr += record.Url().size();
  }
}

ServerResponse::~ServerResponse() {
  if (buffer_ != nullptr) {
    delete buffer_;
  }
}

void ServerResponse::Send(int socket_fd) const {
  size_t write_count = 0;
  while (write_count != buffer_length_) {
    write_count +=
        write(socket_fd, buffer_ + write_count, buffer_length_ - write_count);
  }
}

}  // namespace pseudogoogle
