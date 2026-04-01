#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "ares.h"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_30(const uint8_t *data, size_t size) {
  if (size < sizeof(ares_dns_rr_key_t) + sizeof(unsigned short)) {
    return 0;
  }

  ares_dns_rr_key_t key;
  unsigned short opt;

  /* Copy data into key and opt ensuring they are properly initialized */
  memcpy(&key, data, sizeof(ares_dns_rr_key_t));
  memcpy(&opt, data + sizeof(ares_dns_rr_key_t), sizeof(unsigned short));

  /* Call the function-under-test */
  char *result = ares_dns_opt_get_name(key, opt);

  /* Free the result if it's not NULL */
  if (result) {
    free(result);
  }

  return 0;
}

#ifdef __cplusplus
}
#endif