#include <stddef.h>
#include <ares.h>

extern int LLVMFuzzerTestOneInput_4(const unsigned char *data, size_t size) {
  ares_channel src = NULL;
  ares_channel dest = NULL;
  int status;

  /* Initialize the ares library */
  if (ares_library_init(ARES_LIB_INIT_ALL) != ARES_SUCCESS) {
    return 0;
  }

  /* Initialize the source channel */
  status = ares_init(&src);
  if (status != ARES_SUCCESS) {
    ares_library_cleanup();
    return 0;
  }

  /* Call the function-under-test */
  ares_dup(&dest, src);

  /* Cleanup */
  if (src) {
    ares_destroy(src);
  }
  if (dest) {
    ares_destroy(dest);
  }

  ares_library_cleanup();

  return 0;
}