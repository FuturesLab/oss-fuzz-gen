#include <ares.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>  // For struct in_addr
#include <netdb.h>       // For struct hostent

static void dummy_callback(void *arg, int status, int timeouts, struct hostent *host) {
  /* Dummy callback function to satisfy the ares_gethostbyaddr signature */
  (void)arg;
  (void)status;
  (void)timeouts;
  (void)host;
}

int LLVMFuzzerTestOneInput_2(const uint8_t *data, size_t size) {
  ares_channel channel;
  int init_status = ares_library_init(ARES_LIB_INIT_ALL);
  if (init_status != ARES_SUCCESS) {
    return 0;
  }

  if (ares_init(&channel) != ARES_SUCCESS) {
    ares_library_cleanup();
    return 0;
  }

  // Ensure that the input data is large enough to be used as an address
  if (size < sizeof(struct in_addr)) {
    ares_destroy(channel);
    ares_library_cleanup();
    return 0;
  }

  // Use the input data as an IPv4 address
  struct in_addr addr;
  memcpy(&addr, data, sizeof(struct in_addr));

  // Call the function-under-test
  ares_gethostbyaddr(channel, &addr, sizeof(struct in_addr), AF_INET, dummy_callback, NULL);

  // Clean up
  ares_destroy(channel);
  ares_library_cleanup();

  return 0;
}