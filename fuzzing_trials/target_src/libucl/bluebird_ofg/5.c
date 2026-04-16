#include <sys/stat.h>
#include "ucl.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_5(const uint8_t *data, size_t size) {
  // Ensure the size is sufficient to split into two parts
  if (size < 2) {
    return 0;
  }

  // Split the input data into two parts for two ucl_object_t objects
  size_t mid = size / 2;

  // Create two ucl_parser objects
  struct ucl_parser *parser1 = ucl_parser_new(0);
  struct ucl_parser *parser2 = ucl_parser_new(0);

  // Add string data to the parsers
  ucl_parser_add_string(parser1, (const char *)data, mid);
  ucl_parser_add_string(parser2, (const char *)(data + mid), size - mid);

  // Get ucl_object_t objects from the parsers
  // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of ucl_parser_get_object
  const ucl_object_t *obj1 = ucl_parser_get_object(parser2);
  // End mutation: Producer.REPLACE_ARG_MUTATOR
  const ucl_object_t *obj2 = ucl_parser_get_object(parser2);

  // Ensure both objects are not NULL before comparison
  if (obj1 != NULL && obj2 != NULL) {
    // Call the function-under-test
    int result = ucl_object_compare(obj1, obj2);
  }

  // Free the parsers
  ucl_parser_free(parser1);
  ucl_parser_free(parser2);

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

    LLVMFuzzerTestOneInput_5(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
