#include "stddef.h"
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "ares.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_53(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  /* Initialize ares library */
  if (ares_library_init(ARES_LIB_INIT_ALL) != ARES_SUCCESS) {
    return 0;
  }

  ares_channel channel;
  int status = ares_init(&channel);
  if (status != ARES_SUCCESS) {
    ares_library_cleanup();
    return 0;
  }

  /* Allocate memory for the CSV string and ensure it's null-terminated */
  char *csv = (char *)malloc(size + 1);
  if (!csv) {
    ares_destroy(channel);
    ares_library_cleanup();
    return 0;
  }
  memcpy(csv, data, size);
  csv[size] = '\0';

  /* Call the function under test */

  // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function ares_set_servers_ports_csv with ares_set_servers_csv
  ares_set_servers_csv(channel, csv);
  // End mutation: Producer.REPLACE_FUNC_MUTATOR



  /* Clean up */
  free(csv);
  ares_destroy(channel);
  ares_library_cleanup();

  return 0;
}
#ifdef __cplusplus
}
#endif