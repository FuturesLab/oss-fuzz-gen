#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_107(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Attempt to parse the input data into a UCL object
  ucl_parser_add_string(parser, (const char *)data, size);
  if (ucl_parser_get_error(parser) != NULL) {
    ucl_parser_free(parser);
    return 0;
  }

  // Get the parsed object
  ucl_object_t *original_obj = ucl_parser_get_object(parser);
  if (original_obj == NULL) {
    ucl_parser_free(parser);
    return 0;
  }

  // Call the function-under-test
  ucl_object_t *copied_obj = ucl_object_copy(original_obj);

  // Clean up
  ucl_object_unref(original_obj);
  ucl_object_unref(copied_obj);
  ucl_parser_free(parser);

  return 0;
}