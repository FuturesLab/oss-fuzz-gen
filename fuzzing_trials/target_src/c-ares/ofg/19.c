#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "ares.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_19(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }

  /* Split the input data into two parts for encoded and abuf */
  size_t half_size = size / 2;
  const unsigned char *encoded = data;
  const unsigned char *abuf = data + half_size;
  int alen = (int)(size - half_size);

  unsigned char *s = NULL;
  long enclen = 0;

  /* Call the function under test */
  int result = ares_expand_string(encoded, abuf, alen, &s, &enclen);

  /* Free the allocated string if the function was successful */
  if (result == ARES_SUCCESS && s != NULL) {
    ares_free_string(s);
  }

  return 0;
}

#ifdef __cplusplus
}
#endif