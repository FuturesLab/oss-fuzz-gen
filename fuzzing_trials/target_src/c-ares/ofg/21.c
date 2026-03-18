#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "ares.h"

int LLVMFuzzerTestOneInput_21(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0; /* Not enough data to proceed */
  }

  // Split the input data into two parts for encoded and abuf
  size_t half_size = size / 2;
  const unsigned char *encoded = data;
  const unsigned char *abuf = data + half_size;
  int alen = (int)(size - half_size);

  char *s = NULL;
  long enclen = 0;

  // Call the function under test
  int result = ares_expand_name(encoded, abuf, alen, &s, &enclen);

  // Free the allocated memory if the function succeeded
  if (result == ARES_SUCCESS && s != NULL) {
    ares_free_string(s);
  }

  return 0;
}