// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_parser_new at ucl_parser.c:2804:1 in ucl.h
// ucl_parser_free at ucl_util.c:599:6 in ucl.h
// ucl_parser_add_file at ucl_util.c:2054:6 in ucl.h
// ucl_parser_get_error_code at ucl_util.c:678:5 in ucl.h
// ucl_parser_clear_error at ucl_util.c:707:6 in ucl.h
// ucl_parser_get_column at ucl_util.c:688:1 in ucl.h
// ucl_parser_get_linenum at ucl_util.c:698:1 in ucl.h
// ucl_parser_clear_error at ucl_util.c:707:6 in ucl.h
// ucl_parser_get_error_code at ucl_util.c:678:5 in ucl.h
// ucl_parser_get_object at ucl_util.c:590:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_parser_free at ucl_util.c:599:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_1(const uint8_t *Data, size_t Size) {
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