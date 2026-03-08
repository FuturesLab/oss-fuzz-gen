#include "stddef.h"
#include <stdlib.h>
#include <string.h>
#include "ares.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_31(const unsigned char *data, size_t size) {
  /* Ensure the input size is sufficient for the function parameters */
  if (size < 2) {
    return 0;
  }

  /* Split the input data for 'encoded' and 'abuf' */
  size_t half_size = size / 2;
  const unsigned char *encoded = data;
  const unsigned char *abuf = data + half_size;
  int alen = (int)(size - half_size);

  /* Initialize output parameters */
  char *s = NULL;
  long enclen = 0;

  /* Call the function-under-test */
  int result = ares_expand_name(encoded, abuf, alen, &s, &enclen);

  /* Free the allocated memory for the expanded name if successful */
  if (result == ARES_SUCCESS && s != NULL) {
    ares_free_string(s);
  }

  return 0;
}

#ifdef __cplusplus
}
#endif