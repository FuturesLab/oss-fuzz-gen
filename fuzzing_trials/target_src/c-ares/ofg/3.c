#include <ares.h>
#include <stdlib.h>
#include <stdint.h> // Include for uint8_t
#include <stddef.h> // Include for size_t

int LLVMFuzzerTestOneInput_3(const uint8_t *data, size_t size) {
  ares_channel src = NULL; // Correct type is ares_channel, not ares_channel_t*
  ares_channel dest = NULL; // Correct type is ares_channel, not ares_channel_t*
  int status;

  /* Initialize the ares library */
  if (ares_library_init(ARES_LIB_INIT_ALL) != ARES_SUCCESS) {
    return 0;
  }

  /* Create a source channel for duplication */
  status = ares_init(&src);
  if (status != ARES_SUCCESS) {
    ares_library_cleanup();
    return 0;
  }

  /* Call the function-under-test */
  ares_dup(&dest, src);

  /* Clean up resources */
  if (src) {
    ares_destroy(src);
  }
  if (dest) {
    ares_destroy(dest);
  }

  ares_library_cleanup();

  return 0;
}