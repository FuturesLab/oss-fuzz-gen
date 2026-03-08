// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_parser_new at ucl_parser.c:2804:1 in ucl.h
// ucl_parser_free at ucl_util.c:599:6 in ucl.h
// ucl_parser_add_string at ucl_parser.c:3169:6 in ucl.h
// ucl_parser_get_error at ucl_util.c:665:1 in ucl.h
// ucl_parser_get_error at ucl_util.c:665:1 in ucl.h
// ucl_parser_get_object at ucl_util.c:590:1 in ucl.h
// ucl_parser_free at ucl_util.c:599:6 in ucl.h
// ucl_object_iterate_with_error at ucl_util.c:2717:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ucl.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

int LLVMFuzzerTestOneInput_15(const uint8_t *Data, size_t Size) {
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        return 0;
    }

    // Ensure the data is null-terminated if Size is zero, to avoid overflows
    char *data_copy = NULL;
    if (Size > 0) {
        data_copy = (char *)malloc(Size + 1);
        if (data_copy == NULL) {
            ucl_parser_free(parser);
            return 0;
        }
        memcpy(data_copy, Data, Size);
        data_copy[Size] = '\0';
    }

    // Attempt to add string to the parser
    bool success = ucl_parser_add_string(parser, data_copy, Size);

    // Retrieve errors if any
    const char *error1 = ucl_parser_get_error(parser);
    const char *error2 = ucl_parser_get_error(parser); // Call it twice as per task

    // Get the top-level object from the parser
    ucl_object_t *top_obj = ucl_parser_get_object(parser);

    // Free the parser
    ucl_parser_free(parser);

    // If a top-level object was retrieved, iterate over it
    if (top_obj != NULL) {
        ucl_object_iter_t it = NULL;
        int err = 0;
        const ucl_object_t *cur;

        while ((cur = ucl_object_iterate_with_error(top_obj, &it, true, &err)) != NULL) {
            // Do something with each object (cur), if needed
        }

        // Decrease the reference count of the object
        ucl_object_unref(top_obj);
    }

    // Free the allocated memory for data_copy
    if (data_copy != NULL) {
        free(data_copy);
    }

    return 0;
}