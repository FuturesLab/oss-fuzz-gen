#include <ares.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h> // Include for struct in_addr
#include <netdb.h>     // Include for struct hostent

// Callback function for ares_gethostbyaddr
static void host_callback(void *arg, int status, int timeouts, struct hostent *host) {
  // This is a simple callback function that does nothing with the results.
  (void)arg;
  (void)status;
  (void)timeouts;
  (void)host;
}

int LLVMFuzzerTestOneInput_1(const uint8_t *data, size_t size) {
  // Initialize ares library
  ares_library_init(ARES_LIB_INIT_ALL);

  ares_channel channel;
  struct ares_options options;
  int optmask = 0;

  // Initialize ares channel
  if (ares_init_options(&channel, &options, optmask) != ARES_SUCCESS) {
    ares_library_cleanup();
    return 0;
  }

  // Ensure the address is not NULL and has a minimum length
  if (size < sizeof(struct in_addr)) {
    ares_destroy(channel);
    ares_library_cleanup();
    return 0;
  }

  // Use the first few bytes of data as the address
  struct in_addr addr;
  memcpy(&addr, data, sizeof(struct in_addr));

  // Call the function-under-test
  ares_gethostbyaddr(channel, &addr, sizeof(struct in_addr), AF_INET, host_callback, NULL);

  // Clean up
  ares_destroy(channel);
  ares_library_cleanup();

  return 0;
}