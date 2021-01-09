#ifndef PSEUDOGOOGLE_SERVER_SERVER_H
#define PSEUDOGOOGLE_SERVER_SERVER_H

#include "options.h"
#include "storage/storage.h"

namespace pseudogoogle {

class Server {
 public:
  Server(const Options& options, const Storage& storage)
      : port_(options.port), storage_(storage) {}

  // non copyable
  Server(const Server&) = delete;
  Server& operator=(const Server&) = delete;

  ~Server() = default;

  void Run() const;

 private:
  const int port_;
  // server can't modify storage = no need to synchronize access between threads
  const Storage& storage_;

  int OpenServerSocket() const;
};

}  // namespace pseudogoogle

#endif  // PSEUDOGOOGLE_SERVER_SERVER_H