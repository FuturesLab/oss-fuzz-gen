#include <ares.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>

// Callback function for ares_getnameinfo
static void nameinfo_callback(void *arg, int status, int timeouts, char *node, char *service) {
  // Use parameters to avoid unused parameter warnings
  (void)arg;
  (void)status;
  (void)timeouts;
  (void)node;
  (void)service;
}

int LLVMFuzzerTestOneInput_16(const uint8_t *data, size_t size) {
  if (size < sizeof(struct sockaddr_in)) {
    return 0; // Not enough data to fill sockaddr_in
  }

  ares_channel channel;
  struct ares_options options;
  int optmask = 0;

  // Initialize ares library
  if (ares_library_init(ARES_LIB_INIT_ALL) != ARES_SUCCESS) {
    return 0;
  }

  // Initialize ares channel
  if (ares_init_options(&channel, &options, optmask) != ARES_SUCCESS) {
    ares_library_cleanup();
    return 0;
  }

  // Prepare sockaddr_in structure
  struct sockaddr_in sa;
  memcpy(&sa, data, sizeof(struct sockaddr_in));
  sa.sin_family = AF_INET; // Ensure the family is set to AF_INET

  // Use the remaining data for flags and arg
  int flags_int = 0;
  void *arg = NULL;
  if (size > sizeof(struct sockaddr_in)) {
    flags_int = *(int *)(data + sizeof(struct sockaddr_in));
  }
  if (size > sizeof(struct sockaddr_in) + sizeof(int)) {
    arg = (void *)(data + sizeof(struct sockaddr_in) + sizeof(int));
  }

  // Call the function-under-test
  ares_getnameinfo(channel, (struct sockaddr *)&sa, sizeof(sa), flags_int, nameinfo_callback, arg);

  // Clean up
  ares_destroy(channel);
  ares_library_cleanup();

  return 0;
}