#include <ares.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h> // Include for struct hostent
#include <sys/socket.h> // Include for AF_INET

static void dummy_callback(void *arg, int status, int timeouts, struct hostent *host) {
  /* Dummy callback function to satisfy the ares_gethostbyname signature */
  (void)arg;
  (void)status;
  (void)timeouts;
  (void)host;
}

int LLVMFuzzerTestOneInput_9(const uint8_t *data, size_t size) {
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

  char *name = (char *)malloc(size + 1);
  if (!name) {
    ares_destroy(channel);
    ares_library_cleanup();
    return 0;
  }

  memcpy(name, data, size);
  name[size] = '\0';

  int family = AF_INET;  // Use AF_INET as a default family

  ares_gethostbyname(channel, name, family, dummy_callback, NULL);

  // Process events to ensure the callback is called
  ares_process_fd(channel, ARES_SOCKET_BAD, ARES_SOCKET_BAD);

  free(name);
  ares_destroy(channel);
  ares_library_cleanup();

  return 0;
}