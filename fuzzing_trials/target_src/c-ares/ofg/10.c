#include <ares.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/nameser.h> // For C_IN and T_A

// Callback function for ares_search
static void query_callback(void *arg, int status, int timeouts, unsigned char *abuf, int alen) {
  (void)arg;
  (void)status;
  (void)timeouts;
  (void)abuf;
  (void)alen;
  // For the purpose of this fuzzing harness, we do nothing with the callback
}

int LLVMFuzzerTestOneInput_10(const uint8_t *data, size_t size) {
  ares_channel channel;
  int status = ares_library_init(ARES_LIB_INIT_ALL);
  if (status != ARES_SUCCESS) {
    return 0;
  }

  status = ares_init(&channel);
  if (status != ARES_SUCCESS) {
    ares_library_cleanup();
    return 0;
  }

  // Allocate memory for the name and ensure it's null-terminated
  char *name = (char *)malloc(size + 1);
  if (!name) {
    ares_destroy(channel);
    ares_library_cleanup();
    return 0;
  }
  memcpy(name, data, size);
  name[size] = '\0';

  // Use some fixed values for dnsclass and type for simplicity
  int dnsclass = C_IN; // Internet class
  int type = T_A;      // A record

  // Call ares_search
  ares_search(channel, name, dnsclass, type, query_callback, NULL);

  // Process any pending queries
  ares_process_fd(channel, ARES_SOCKET_BAD, ARES_SOCKET_BAD);

  // Clean up
  free(name);
  ares_destroy(channel);
  ares_library_cleanup();

  return 0;
}