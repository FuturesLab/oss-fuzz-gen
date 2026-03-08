#include "ares.h"
#include <stdlib.h>
#include <string.h>
#include <arpa/nameser.h> // For C_IN and T_A

int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size);

static void dummy_callback(void *arg, int status, int timeouts, unsigned char *abuf, int alen) {
  /* Dummy callback function to satisfy ares_query requirements. */
  (void)arg;
  (void)status;
  (void)timeouts;
  (void)abuf;
  (void)alen;
}

int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
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

  /* Create a null-terminated string from the data to use as the domain name. */
  char *name = (char *)malloc(size + 1);
  if (!name) {
    ares_destroy(channel);
    ares_library_cleanup();
    return 0;
  }
  memcpy(name, data, size);
  name[size] = '\0';

  /* Use some arbitrary values for dnsclass and type. */
  int dnsclass = C_IN;
  int type = T_A;

  /* Call the function under test. */
  ares_query(channel, name, dnsclass, type, dummy_callback, NULL);

  /* Clean up. */
  free(name);
  ares_destroy(channel);
  ares_library_cleanup();

  return 0;
}