#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ares.h>

int LLVMFuzzerTestOneInput_39(const uint8_t *data, size_t size) {
  /* Allocate memory for the string to be freed */
  void *str = malloc(size + 1);
  if (str == NULL) {
    return 0;
  }

  /* Copy data into the allocated memory */
  memcpy(str, data, size);
  ((char *)str)[size] = '\0'; /* Null-terminate the string */

  /* Call the function-under-test */
  ares_free_string(str);

  return 0;
}