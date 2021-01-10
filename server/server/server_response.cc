#include "server/server_response.h"

#include <unistd.h>

#include <cstring>

#include "util/coding.h"

namespace pseudogoogle {

ServerResponse::ServerResponse(
    const std::set<Record, RecordOrderComparator>* result_set) {
  if (result_set == nullptr) {
    type_ = kNotFound;
    buffer_ = nullptr;
  } else {
    type_ = kOk;

    // set buffer length and allocate buffer
    buffer_length_ = 4;
    for (const auto& record : *result_set) {
      buffer_length_ += 4 + record.Url().size();
    }
    buffer_ = new char[buffer_length_];

    // fill buffer
    char* buffer_ptr = buffer_;
    EncodeFixed32(buffer_ptr, result_set->size());
    buffer_ptr += 4;
    for (const auto& record : *result_set) {
      EncodeFixed32(buffer_ptr, record.Url().size());
      buffer_ptr += 4;
      memcpy(buffer_ptr, record.Url().c_str(), record.Url().size());
      buffer_ptr += record.Url().size();
    }
  }
}

ServerResponse::~ServerResponse() {
  if (buffer_ != nullptr) {
    delete buffer_;
  }
}

void ServerResponse::Send(int socket_fd) const {
  while (write(socket_fd, &type_, 1) == 0) {
    continue;
  }

  if (type_ == kOk) {
    size_t write_count = 0;
    while (write_count != buffer_length_) {
      write_count +=
          write(socket_fd, buffer_ + write_count, buffer_length_ - write_count);
    }
  }
}

}  // namespace pseudogoogle
