// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_parser_new at ucl_parser.c:2804:1 in ucl.h
// ucl_set_include_path at ucl_parser.c:3180:6 in ucl.h
// ucl_array_append at ucl_util.c:3131:6 in ucl.h
// ucl_array_prepend at ucl_util.c:3163:6 in ucl.h
// ucl_array_replace_index at ucl_util.c:3378:1 in ucl.h
// ucl_array_delete at ucl_util.c:3231:1 in ucl.h
// ucl_object_iterate_new at ucl_util.c:2794:1 in ucl.h
// ucl_object_iterate_safe at ucl_util.c:2839:1 in ucl.h
// ucl_object_iterate_free at ucl_util.c:2903:6 in ucl.h
// ucl_parser_free at ucl_util.c:599:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "ucl.h"

static ucl_object_t* create_random_ucl_object(const uint8_t *Data, size_t Size) {
    ucl_object_t *obj = malloc(sizeof(ucl_object_t));
    if (obj) {
        obj->value.sv = (const char *)Data;
        obj->len = Size;
    }
    return obj;
}

int LLVMFuzzerTestOneInput_78(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize a parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (!parser) return 0;

    // Create a UCL_ARRAY of paths
    ucl_object_t *paths = create_random_ucl_object(Data, Size);
    if (paths) {
        // Fuzz ucl_set_include_path
        ucl_set_include_path(parser, paths);
    }

    // Create a UCL array object
    ucl_object_t *ucl_array = create_random_ucl_object(Data, Size);
    ucl_object_t *new_element = create_random_ucl_object(Data, Size);

    if (ucl_array && new_element) {
        // Fuzz ucl_array_append
        ucl_array_append(ucl_array, new_element);

        // Fuzz ucl_array_prepend
        ucl_array_prepend(ucl_array, new_element);

        // Fuzz ucl_array_replace_index
        ucl_array_replace_index(ucl_array, new_element, 0);

        // Fuzz ucl_array_delete
        ucl_array_delete(ucl_array, new_element);

        // Initialize a valid iterator for safe iteration
        ucl_object_iter_t iter = ucl_object_iterate_new(ucl_array);
        if (iter) {
            // Fuzz ucl_object_iterate_safe
            ucl_object_iterate_safe(iter, true);
            ucl_object_iterate_free(iter);
        }
    }

    // Clean up
    ucl_parser_free(parser);
    if (paths) free(paths);
    if (ucl_array) free(ucl_array);
    if (new_element) free(new_element);

    return 0;
}