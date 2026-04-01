#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_18(const uint8_t *data, size_t size) {
  // Ensure that the input data is not empty
  if (size == 0) {
    return 0;
  }

  // Create a ucl_parser to parse the input data
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Parse the input data
  if (!ucl_parser_add_chunk(parser, data, size)) {
    ucl_parser_free(parser);
    return 0;
  }

  // Get the root object from the parser
  const ucl_object_t *obj = ucl_parser_get_object(parser);
  if (obj == NULL) {
    ucl_parser_free(parser);
    return 0;
  }

  // Call the function-under-test
  char *key_copy = ucl_copy_key_trash(obj);

  // Free the copied key if it was successfully allocated
  if (key_copy != NULL) {
    free(key_copy);
  }

  // Clean up
  ucl_object_unref(obj);
  ucl_parser_free(parser);

  return 0;
}

#ifdef __cplusplus
}
#endif