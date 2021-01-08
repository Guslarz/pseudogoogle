#include "server/server.h"

#include <iostream>

#include "website/website.h"

namespace pseudogoogle {

void Server::Run() const {
  // TODO
  // Run server
  // Decide how to request data from it and what response is
  // Implement everything
  std::cout << storage_.ToString() << std::endl;
}

}  // namespace pseudogoogle