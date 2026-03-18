#include <ares.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

// Dummy callback function for ares_getaddrinfo
static void dummy_callback(void *arg, int status, int timeouts, struct ares_addrinfo *res) {
  (void)arg; // Suppress unused parameter warning
  (void)status; // Suppress unused parameter warning
  (void)timeouts; // Suppress unused parameter warning
  // Free the result if it's not NULL
  if (res) {
    ares_freeaddrinfo(res);
  }
}

int LLVMFuzzerTestOneInput_14(const uint8_t *data, size_t size) {
  // Initialize ares library
  ares_library_init(ARES_LIB_INIT_ALL);

  ares_channel channel;
  int status = ares_init(&channel);
  if (status != ARES_SUCCESS) {
    return 0;
  }

  // Prepare input data
  const char *name = "example.com";
  const char *service = "http";
  struct ares_addrinfo_hints hints;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;

  // Call the function under test
  ares_getaddrinfo(channel, name, service, &hints, dummy_callback, NULL);

  // Cleanup
  ares_destroy(channel);
  ares_library_cleanup();

  return 0;
}