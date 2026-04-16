#include <sys/stat.h>
#include <string.h>
#include "ucl.h"
#include <stdint.h>
#include <stddef.h>

int LLVMFuzzerTestOneInput_2(const uint8_t *data, size_t size) {
  // If size is 0, there's no data to process
  if (size == 0) {
    return 0;
  }

  // Create a new UCL parser
  // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of ucl_parser_new
  struct ucl_parser *parser = ucl_parser_new(size);
  // End mutation: Producer.REPLACE_ARG_MUTATOR
  if (parser == NULL) {
    return 0;
  }

  // Add data to the parser
  ucl_parser_add_string(parser, (const char *)data, size);

  // Call the function-under-test

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_add_string to ucl_parser_register_context_macro
  struct ucl_emitter_functions* ret_ucl_object_emit_fd_funcs_yzojy = ucl_object_emit_fd_funcs(1);
  if (ret_ucl_object_emit_fd_funcs_yzojy == NULL){
  	return 0;
  }
  bool ret_ucl_parser_register_context_macro_czcch = ucl_parser_register_context_macro(parser, (const char *)"w", NULL, (void *)ret_ucl_object_emit_fd_funcs_yzojy);
  if (ret_ucl_parser_register_context_macro_czcch == 0){
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

    LLVMFuzzerTestOneInput_2(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
