#ifndef PSEUDOGOOGLE_SERVER_SERVER_H
#define PSEUDOGOOGLE_SERVER_SERVER_H

#include "storage/storage.h"

namespace pseudogoogle {

class Server {
 public:
  Server(const Storage& storage) : storage_(storage) {}

  // non copyable
  Server(const Server&) = delete;
  Server& operator=(const Server&) = delete;

  ~Server() = default;

  void Run() const;

 private:
  const Storage& storage_;
};

}  // namespace pseudogoogle

#endif  // PSEUDOGOOGLE_SERVER_SERVER_H