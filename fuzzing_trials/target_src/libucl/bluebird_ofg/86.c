#include "ucl.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_86(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  // Create a ucl_parser and parse the input data
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  ucl_parser_add_string(parser, (const char *)data, size);

  if (ucl_parser_get_error(parser) != NULL) {
    ucl_parser_free(parser);
    return 0;
  }

  // Get the root object from the parser
  const ucl_object_t *root = ucl_parser_get_object(parser);
  if (root == NULL) {
    ucl_parser_free(parser);
    return 0;
  }

  // Prepare a size_t variable to store the key length
  size_t key_length = 0;

  // Call the function-under-test

  // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of ucl_object_keyl
  const char *key = ucl_object_keyl(root, NULL);
  // End mutation: Producer.REPLACE_ARG_MUTATOR



  // Free resources
  ucl_object_unref(root);
  ucl_parser_free(parser);

  return 0;
}