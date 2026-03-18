#include "ucl.h"
#include <stddef.h>
#include <stdint.h>

int LLVMFuzzerTestOneInput_56(const uint8_t *data, size_t size) {
  // If size is 0 we need a null-terminated string.
  // We don't null-terminate the string and by the design
  // of the API passing 0 as size with non null-terminated string
  // gives undefined behavior.
  if (size == 0) {
    return 0;
  }

  // Call the function-under-test
  ucl_object_t *obj = ucl_object_fromlstring((const char *)data, size);

  // Clean up
  if (obj != NULL) {
    ucl_object_unref(obj);
  }

  return 0;
}