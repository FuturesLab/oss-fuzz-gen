#include <ares.h>
#include <ares_nameser.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* Fuzzing entry point */
int LLVMFuzzerTestOneInput_29(const uint8_t *data, size_t size) {
  ares_channel channel;
  int status;

  /* Initialize the ares library */
  if (ares_library_init(ARES_LIB_INIT_ALL) != ARES_SUCCESS) {
    return 0;
  }

  /* Initialize the channel */
  if (ares_init(&channel) != ARES_SUCCESS) {
    ares_library_cleanup();
    return 0;
  }

  /* Ensure the data is null-terminated for ares_query */
  char *query_name = (char *)malloc(size + 1);
  if (!query_name) {
    ares_destroy(channel);
    ares_library_cleanup();
    return 0;
  }
  memcpy(query_name, data, size);
  query_name[size] = '\0';

  /* Call the function-under-test */
  ares_query(channel, query_name, ns_c_in, ns_t_a, NULL, NULL);

  /* Clean up */
  free(query_name);
  ares_destroy(channel);
  ares_library_cleanup();

  return 0;
}