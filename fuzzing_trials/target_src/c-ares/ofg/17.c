#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <ares.h>

// Callback function to be used with ares_getnameinfo
static void nameinfo_callback(void *arg, int status, int timeouts, char *node, char *service) {
  // Handle the callback results here
  (void)arg;      // Unused parameter
  (void)status;   // Unused parameter
  (void)timeouts; // Unused parameter
  (void)node;     // Unused parameter
  (void)service;  // Unused parameter
}

int LLVMFuzzerTestOneInput_17(const uint8_t *data, size_t size) {
  ares_channel channel;
  struct sockaddr_in sa;
  ares_socklen_t salen = sizeof(sa);
  int flags = 0; // You can change this to other valid flag values for more testing
  void *arg = NULL;

  // Initialize ares library
  if (ares_library_init(ARES_LIB_INIT_ALL) != ARES_SUCCESS) {
    return 0;
  }

  // Initialize ares channel
  if (ares_init(&channel) != ARES_SUCCESS) {
    ares_library_cleanup();
    return 0;
  }

  // Ensure the size is sufficient for sockaddr_in
  if (size >= sizeof(struct sockaddr_in)) {
    // Copy data into sockaddr_in structure
    memcpy(&sa, data, sizeof(struct sockaddr_in));

    // Call the function under test
    ares_getnameinfo(channel, (const struct sockaddr *)&sa, salen, flags, nameinfo_callback, arg);
  }

  // Clean up ares channel
  ares_destroy(channel);

  // Clean up ares library
  ares_library_cleanup();

  return 0;
}