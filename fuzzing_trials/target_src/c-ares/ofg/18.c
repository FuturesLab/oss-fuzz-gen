#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "ares.h"

int LLVMFuzzerTestOneInput_18(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }

  /* Split the input data into two parts: encoded and abuf */
  size_t encoded_size = size / 2;
  size_t abuf_size = size - encoded_size;

  const unsigned char *encoded = data;
  const unsigned char *abuf = data + encoded_size;

  /* Allocate memory for the output string and enclen */
  unsigned char *s = NULL;
  long enclen = 0;

  /* Call the function-under-test */
  ares_expand_string(encoded, abuf, (int)abuf_size, &s, &enclen);

  /* Free the allocated memory for the output string if it was allocated */
  if (s != NULL) {
    free(s);
  }

  return 0;
}