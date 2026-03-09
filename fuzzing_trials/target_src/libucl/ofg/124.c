#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_124(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }

  // Split the input data into two parts for two ucl_object_t objects
  size_t mid = size / 2;
  const uint8_t *data1 = data;
  size_t size1 = mid;
  const uint8_t *data2 = data + mid;
  size_t size2 = size - mid;

  // Create and initialize two ucl_parser instances
  struct ucl_parser *parser1 = ucl_parser_new(0);
  struct ucl_parser *parser2 = ucl_parser_new(0);

  // Add the data to the parsers
  ucl_parser_add_chunk(parser1, data1, size1);
  ucl_parser_add_chunk(parser2, data2, size2);

  // Get the ucl_object_t from the parsers
  const ucl_object_t *obj1 = ucl_parser_get_object(parser1);
  const ucl_object_t *obj2 = ucl_parser_get_object(parser2);

  // Ensure the objects are not NULL before comparing
  if (obj1 != NULL && obj2 != NULL) {
    // Call the function-under-test
    int result = ucl_object_compare(obj1, obj2);
  }

  // Free the parsers
  ucl_parser_free(parser1);
  ucl_parser_free(parser2);

  return 0;
}