#ifndef PSEUDOGOOGLE_SERVER_CLIENT_DATA_H
#define PSEUDOGOOGLE_SERVER_CLIENT_DATA_H

#include <netinet/in.h>

#include "storage/storage.h"

namespace pseudogoogle {

struct ClientData {
  int socket_fd;
  sockaddr_in clientaddr;
  const Storage* storage;
};

}  // namespace pseudogoogle

#endif  // PSEUDOGOOGLE_SERVER_CLIENT_DATA_H