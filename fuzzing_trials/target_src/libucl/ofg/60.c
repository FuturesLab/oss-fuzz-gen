#include <stdint.h>
#include <stddef.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_60(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  struct ucl_parser *parser = ucl_parser_new(0);
  ucl_object_t *obj = NULL;
  ucl_object_iter_t iter = NULL;

  // Parse the input data
  ucl_parser_add_chunk(parser, data, size);

  if (ucl_parser_get_error(parser) == NULL) {
    // Get the root object
    obj = ucl_parser_get_object(parser);

    // Initialize the iterator
    iter = ucl_object_iterate_new(obj);

    // Iterate over the object (this is just an example, actual iteration logic can vary)
    const ucl_object_t *cur;
    while ((cur = ucl_object_iterate_safe(iter, true)) != NULL) {
      // Do something with the current object
    }

    // Free the iterator
    ucl_object_iterate_free(iter);

    // Free the object
    ucl_object_unref(obj);
  }

  // Free the parser
  ucl_parser_free(parser);

  return 0;
}