#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ares.h>

int LLVMFuzzerTestOneInput_23(const uint8_t *data, size_t size) {
  /* Ensure that the size is sufficient to extract meaningful data for options */
  if (size < sizeof(struct ares_options)) {
    return 0;
  }

  /* Allocate memory for the options and copy data into it */
  struct ares_options options;
  memcpy(&options, data, sizeof(struct ares_options));

  /* Extract optmask from the remaining data, if available */
  int optmask = 0;
  if (size >= sizeof(struct ares_options) + sizeof(int)) {
    memcpy(&optmask, data + sizeof(struct ares_options), sizeof(int));
  }

  /* Initialize channel pointer */
  ares_channel channelptr = NULL;

  /* Call the function-under-test */
  int result = ares_init_options(&channelptr, &options, optmask);

  /* Clean up if the channel was successfully initialized */
  if (result == ARES_SUCCESS && channelptr != NULL) {
    ares_destroy(channelptr);
  }

  return 0;
}