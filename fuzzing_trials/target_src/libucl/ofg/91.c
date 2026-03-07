#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_91(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  ucl_parser_add_string(parser, (const char *)data, size);
  const ucl_object_t *obj = ucl_parser_get_object(parser);

  if (obj != NULL) {
    // Call the function-under-test
    unsigned int priority = ucl_object_get_priority(obj);
  }

  ucl_object_unref(obj);
  ucl_parser_free(parser);

  return 0;
}