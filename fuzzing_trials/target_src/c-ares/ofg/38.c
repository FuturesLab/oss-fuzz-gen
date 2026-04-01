#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "ares.h"

int LLVMFuzzerTestOneInput_38(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  /* Allocate memory and copy data to simulate a string */
  void *str = malloc(size + 1);
  if (str == NULL) {
    return 0;
  }
  memcpy(str, data, size);
  ((char*)str)[size] = '\0';  /* Null-terminate the string */

  /* Call the function-under-test */
  ares_free_string(str);

  return 0;
}