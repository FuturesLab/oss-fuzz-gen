#include <ares.h>
#include <ares_dns.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Dummy callback function
static void dummy_callback(void *arg, int status, int timeouts, unsigned char *abuf, int alen) {
  (void)arg; // Suppress unused parameter warning
  (void)status; // Suppress unused parameter warning
  (void)timeouts; // Suppress unused parameter warning
  (void)abuf; // Suppress unused parameter warning
  (void)alen; // Suppress unused parameter warning
}

int LLVMFuzzerTestOneInput_27(const uint8_t *data, size_t size) {
  // Initialize ares library
  if (ares_library_init(ARES_LIB_INIT_ALL) != ARES_SUCCESS) {
    return 0;
  }

  ares_channel channel;
  if (ares_init(&channel) != ARES_SUCCESS) {
    ares_library_cleanup();
    return 0;
  }

  // Allocate and initialize buffer for DNS query
  unsigned char *query = (unsigned char *)malloc(size);
  if (!query) {
    ares_destroy(channel);
    ares_library_cleanup();
    return 0;
  }
  memcpy(query, data, size);

  // Initialize other parameters
  unsigned short qid = 0;
  void *arg = NULL;

  // Call the function-under-test
  ares_send(channel, query, size, dummy_callback, arg);

  // Clean up
  free(query);
  ares_destroy(channel);
  ares_library_cleanup();

  return 0;
}