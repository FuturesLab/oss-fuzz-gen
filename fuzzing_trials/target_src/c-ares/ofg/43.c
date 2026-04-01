#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ares.h>

static void dummy_callback(void *arg, int status, int timeouts, unsigned char *abuf, int alen) {
  (void)arg; // Suppress unused parameter warning
  (void)status; // Suppress unused parameter warning
  (void)timeouts; // Suppress unused parameter warning
  (void)abuf; // Suppress unused parameter warning
  (void)alen; // Suppress unused parameter warning
  /* Dummy callback function for testing purposes */
}

int LLVMFuzzerTestOneInput_43(const uint8_t *data, size_t size) {
  ares_channel channel;
  struct ares_options options;
  int optmask = 0;

  // Initialize the ares library
  if (ares_library_init(ARES_LIB_INIT_ALL) != ARES_SUCCESS) {
    return 0;
  }

  // Initialize the ares channel
  if (ares_init_options(&channel, &options, optmask) != ARES_SUCCESS) {
    ares_library_cleanup();
    return 0;
  }

  // Prepare the query buffer
  unsigned char *qbuf = (unsigned char *)malloc(size);
  if (!qbuf) {
    ares_destroy(channel);
    ares_library_cleanup();
    return 0;
  }
  memcpy(qbuf, data, size);

  // Call the function-under-test
  ares_send(channel, qbuf, (int)size, dummy_callback, NULL);

  // Clean up
  free(qbuf);
  ares_destroy(channel);
  ares_library_cleanup();

  return 0;
}