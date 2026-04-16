#include <sys/stat.h>
#include "ucl.h"
#include <stddef.h>
#include <stdint.h>
#include <string.h>

int LLVMFuzzerTestOneInput_35(const uint8_t *data, size_t size) {
  // Ensure there is enough data to split for key and value
  if (size < 2) {
    return 0;
  }

  // Initialize a ucl_parser
  // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of ucl_parser_new
  struct ucl_parser *parser = ucl_parser_new(size);
  // End mutation: Producer.REPLACE_ARG_MUTATOR
  if (parser == NULL) {
    return 0;
  }

  // Add data to the parser
  ucl_parser_add_chunk(parser, data, size);

  // Get the top object from the parser
  ucl_object_t *top_obj = ucl_parser_get_object(parser);

  // Ensure top_obj is not NULL
  if (top_obj == NULL) {
    ucl_parser_free(parser);
    return 0;
  }

  // Use the first byte of data as the length of the key
  size_t key_len = data[0] % size;
  if (key_len == 0) {
    key_len = 1; // Ensure key length is at least 1
  }

  // Extract the key from the data
  char key[key_len + 1];
  memcpy(key, data + 1, key_len);
  key[key_len] = '\0'; // Null-terminate the key

  // Call the function-under-test
  ucl_object_t *popped_obj = ucl_object_pop_key(top_obj, key);

  // Free the popped object if it exists
  if (popped_obj != NULL) {
    ucl_object_unref(popped_obj);
  }

  // Clean up
  ucl_object_unref(top_obj);
  ucl_parser_free(parser);

  return 0;
}
#ifdef INC_MAIN
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main(int argc, char *argv[])
{
    FILE *f;
    uint8_t *data = NULL;
    long size;

    if(argc < 2)
        exit(0);

    f = fopen(argv[1], "rb");
    if(f == NULL)
        exit(0);

    fseek(f, 0, SEEK_END);

    size = ftell(f);
    rewind(f);

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_35(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
