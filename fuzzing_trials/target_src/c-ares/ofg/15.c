#include <ares.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <sys/socket.h> // Include for AF_UNSPEC and SOCK_STREAM

// Callback function to be used with ares_getaddrinfo
static void my_callback(void *arg, int status, int timeouts, struct ares_addrinfo *res) {
  // Handle the callback result (e.g., free resources)
  (void)arg; // Suppress unused parameter warning
  (void)status; // Suppress unused parameter warning
  (void)timeouts; // Suppress unused parameter warning
  if (res) {
    ares_freeaddrinfo(res);
  }
}

int LLVMFuzzerTestOneInput_15(const uint8_t *data, size_t size) {
  ares_channel channel;
  struct ares_addrinfo_hints hints;
  int status;
  void *arg = NULL;

  // Initialize the ares library
  status = ares_library_init(ARES_LIB_INIT_ALL);
  if (status != ARES_SUCCESS) {
    return 0;
  }

  // Initialize the channel
  status = ares_init(&channel);
  if (status != ARES_SUCCESS) {
    ares_library_cleanup();
    return 0;
  }

  // Prepare the name and service strings
  const char *name = "example.com";
  const char *service = "http";

  // Initialize hints
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  // Call the function-under-test
  ares_getaddrinfo(channel, name, service, &hints, my_callback, arg);

  // Clean up
  ares_destroy(channel);
  ares_library_cleanup();

  return 0;
}