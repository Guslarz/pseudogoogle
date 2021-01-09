#include <cstdio>
#include <cstring>

#include "loader/loader.h"
#include "options.h"
#include "server/server.h"
#include "storage/storage.h"

constexpr int kDefualtMaxDepth = 5;

constexpr int kDefaultNodeLimit = 100;

/**
 * Print some help about program
 */
void ShowHelp() {
  std::printf("\n");
  std::printf("Pseudogoogle\n\n");
  std::printf("  --help\t\t\tPrint this message\n");
  std::printf("  --url=<string>\t\tSet root url (first visited website)\n");
  std::printf("  --max-depth=<int>\t\tSet max depth for indexing websites,");
  std::printf("\t-1 to disable, default %d\n", kDefualtMaxDepth);
  std::printf("  --node-limit=<int>\t\tSet node limit for indexing websites,");
  std::printf("\t-1 to disable, default %d\n", kDefaultNodeLimit);
  std::printf("--max-depth and --node-limit can't both be -1\n");
  std::printf("\n");
}

int main(int argc, char* argv[]) {
  // if no params then show help
  if (argc == 1) {
    ShowHelp();
    return EXIT_SUCCESS;
  }

  // load options
  pseudogoogle::Options options;
  options.max_depth = kDefualtMaxDepth;
  options.node_limit = kDefaultNodeLimit;
  for (int i = 1; i < argc; ++i) {
    int tmp;
    if (strncmp(argv[i], "--help", 6) == 0) {
      ShowHelp();
      return 0;
    } else if (strncmp(argv[i], "--url=", 6) == 0) {
      options.url = std::string(argv[i] + 6);
    } else if (sscanf(argv[i], "--max-depth=%d", &tmp)) {
      options.max_depth = tmp;
    } else if (sscanf(argv[i], "--node-limit=%d", &tmp)) {
      options.node_limit = tmp;
    } else {
      std::fprintf(stderr, "Invalid flag '%s'", argv[i]);
      return EXIT_FAILURE;
    }
  }

  // validate options
  if (options.max_depth < -1) {
    std::fprintf(stderr, "Invalid --max-depth value\n");
    return EXIT_FAILURE;
  } else if (options.node_limit < -1) {
    std::fprintf(stderr, "Invalid --node-limit value\n");
    return EXIT_FAILURE;
  } else if (options.max_depth == -1 && options.node_limit == -1) {
    std::fprintf(stderr, "--max-depth and --node-limit can't both be -1\n");
    return EXIT_FAILURE;
  }

  // load websites data into storage
  pseudogoogle::Storage storage;
  pseudogoogle::Loader loader(options);
  loader.LoadIntoStorage(storage);

  // run server
  pseudogoogle::Server server(storage);
  server.Run();

  return EXIT_SUCCESS;
}