#include <sys/stat.h>
#include <string.h>
#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_12(const uint8_t *data, size_t size) {
  // If size is 0, there's no data to process
  if (size == 0) {
    return 0;
  }

  // Create a new UCL parser
  struct ucl_parser *parser = ucl_parser_new(0);
  if (parser == NULL) {
    return 0;
  }

  // Add data to the parser
  ucl_parser_add_string(parser, (const char *)data, size);

  // Call the function-under-test

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_add_string to ucl_parser_insert_chunk
  unsigned int ret_ucl_array_size_hiyuq = ucl_array_size(NULL);
  if (ret_ucl_array_size_hiyuq < 0){
  	return 0;
  }
  bool ret_ucl_parser_insert_chunk_zxveq = ucl_parser_insert_chunk(parser, (const unsigned char *)data, (size_t )ret_ucl_array_size_hiyuq);
  if (ret_ucl_parser_insert_chunk_zxveq == 0){
  	return 0;
  }
  // End mutation: Producer.APPEND_MUTATOR
  
  int priority = ucl_parser_get_default_priority(parser);

  // Free the parser
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

    LLVMFuzzerTestOneInput_12(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
