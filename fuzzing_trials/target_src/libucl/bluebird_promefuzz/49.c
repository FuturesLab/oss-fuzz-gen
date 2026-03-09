#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "stdio.h"
#include "ucl.h"

int LLVMFuzzerTestOneInput_49(const uint8_t *Data, size_t Size) {
    // Initialize a UCL parser
    struct ucl_parser *parser = ucl_parser_new(UCL_PARSER_DEFAULT);

    // Create a dummy file and write the input data to it
    FILE *file = fopen("./dummy_file", "wb");
    if (file == NULL) {
        ucl_parser_free(parser);
        return 0;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Parse the dummy file
    if (!ucl_parser_add_file(parser, "./dummy_file")) {
        // Handle parsing error
        ucl_parser_get_error_code(parser);
        ucl_parser_clear_error(parser);
    }

    // Call the target functions in the specified order

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_parser_add_file to ucl_set_include_path
    ucl_object_t* ret_ucl_object_fromstring_mptoc = ucl_object_fromstring(NULL);
    if (ret_ucl_object_fromstring_mptoc == NULL){
    	return 0;
    }

    bool ret_ucl_set_include_path_sccfi = ucl_set_include_path(parser, ret_ucl_object_fromstring_mptoc);
    if (ret_ucl_set_include_path_sccfi == 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    unsigned column = ucl_parser_get_column(parser);
    unsigned linenum = ucl_parser_get_linenum(parser);
    ucl_parser_clear_error(parser);
    int error_code = ucl_parser_get_error_code(parser);
    ucl_object_t *obj = ucl_parser_get_object(parser);

    // If obj is not NULL, unref it once before freeing the parser
    if (obj != NULL) {
        ucl_object_unref(obj);
    }

    ucl_parser_free(parser);

    // Clean up the dummy file
    remove("./dummy_file");

    return 0;
}