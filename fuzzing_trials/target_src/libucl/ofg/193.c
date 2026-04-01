#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>

// A simple comparison function for sorting
int ucl_object_compare_func(const void *a, const void *b) {
  const ucl_object_t *obj_a = *(const ucl_object_t **)a;
  const ucl_object_t *obj_b = *(const ucl_object_t **)b;
  
  // Example comparison based on object key
  return strcmp(ucl_object_key(obj_a), ucl_object_key(obj_b));
}

int LLVMFuzzerTestOneInput_193(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  // Create a new UCL parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Add the input data to the parser
  if (!ucl_parser_add_string(parser, (const char *)data, size)) {
    ucl_parser_free(parser);
    return 0;
  }

  // Get the root UCL object
  ucl_object_t *root = ucl_parser_get_object(parser);
  if (root == NULL) {
    ucl_parser_free(parser);
    return 0;
  }

  // Call the function-under-test
  ucl_object_array_sort(root, ucl_object_compare_func);

  // Clean up
  ucl_object_unref(root);
  ucl_parser_free(parser);

  return 0;
}