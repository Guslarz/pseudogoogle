#ifndef PSEUDOGOOGLE_SERVER_SERVER_RESPONSE_H
#define PSEUDOGOOGLE_SERVER_SERVER_RESPONSE_H

#include <util/record.h>

#include <set>
#include <unordered_set>

namespace pseudogoogle {

/**
 * Response is:
 *  - word count (4 bytes)
 *  - words where each word is:
 *    - word length (4 bytes)
 *    - word string (word length bytes)
 *  - record count (4 bytes)
 *  - records where each record is:
 *    - url length (4 bytes)
 *    - url (url length bytes)
 */
class ServerResponse {
 public:
  ServerResponse(const std::unordered_set<std::string>& words,
                 const std::set<Record, RecordOrderComparator>& result);

  // non copyable
  ServerResponse(const ServerResponse&) = delete;
  ServerResponse& operator=(const ServerResponse&) = delete;

  ~ServerResponse();

  void Send(int socket_fd) const;

 private:
  size_t buffer_length_;
  char* buffer_;
};

}  // namespace pseudogoogle

#endif  // PSEUDOGOOGLE_SERVER_SERVER_RESPONSE_H