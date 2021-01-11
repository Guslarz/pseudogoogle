#ifndef PSEUDOGOOGLE_SERVER_SERVER_RESPONSE_H
#define PSEUDOGOOGLE_SERVER_SERVER_RESPONSE_H

#include <util/record.h>

#include <set>

namespace pseudogoogle {

enum ResponseType { kOk = 0, kNotFound = 1 };

/**
 * Response is:
 *  - type (1 byte), end if kNotFound, else:
 *    - record count (4 bytes)
 *    - records where each record is:
 *      - url length (4 bytes)
 *      - url (url length bytes)
 */
class ServerResponse {
 public:
  ServerResponse(const std::set<Record, RecordOrderComparator>* result_set);

  // non copyable
  ServerResponse(const ServerResponse&) = delete;
  ServerResponse& operator=(const ServerResponse&) = delete;

  ~ServerResponse();

  void Send(int socket_fd) const;

 private:
  ResponseType type_;
  size_t buffer_length_;
  char* buffer_;
};

}  // namespace pseudogoogle

#endif  // PSEUDOGOOGLE_SERVER_SERVER_RESPONSE_H