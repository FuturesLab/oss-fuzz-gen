// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_object_typed_new at ucl_util.c:2986:1 in ucl.h
// ucl_object_typed_new at ucl_util.c:2986:1 in ucl.h
// ucl_object_typed_new at ucl_util.c:2986:1 in ucl.h
// ucl_object_typed_new at ucl_util.c:2986:1 in ucl.h
// ucl_object_typed_new at ucl_util.c:2986:1 in ucl.h
// ucl_object_insert_key at ucl_util.c:2533:6 in ucl.h
// ucl_object_insert_key at ucl_util.c:2533:6 in ucl.h
// ucl_object_insert_key at ucl_util.c:2533:6 in ucl.h
// ucl_object_insert_key at ucl_util.c:2533:6 in ucl.h
// ucl_object_emit_len at ucl_emitter.c:667:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_parser_new at ucl_parser.c:2804:1 in ucl.h
// ucl_parser_add_chunk_full at ucl_parser.c:2974:6 in ucl.h
// ucl_parser_get_error at ucl_util.c:665:1 in ucl.h
// ucl_parser_get_object at ucl_util.c:590:1 in ucl.h
// ucl_object_emit_len at ucl_emitter.c:667:1 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_parser_free at ucl_util.c:599:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ucl.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_7(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Step 1: Prepare environment
    ucl_object_t *obj = ucl_object_typed_new(UCL_OBJECT);
    if (!obj) {
        return 0;
    }

    // Insert keys into the UCL object
    ucl_object_t *elt1 = ucl_object_typed_new(UCL_STRING);
    ucl_object_t *elt2 = ucl_object_typed_new(UCL_INT);
    ucl_object_t *elt3 = ucl_object_typed_new(UCL_BOOLEAN);
    ucl_object_t *elt4 = ucl_object_typed_new(UCL_FLOAT);

    if (elt1) ucl_object_insert_key(obj, elt1, "key1", 4, true);
    if (elt2) ucl_object_insert_key(obj, elt2, "key2", 4, true);
    if (elt3) ucl_object_insert_key(obj, elt3, "key3", 4, true);
    if (elt4) ucl_object_insert_key(obj, elt4, "key4", 4, true);

    // Emit object to string
    size_t emit_len;
    unsigned char *emitted = ucl_object_emit_len(obj, UCL_EMIT_JSON, &emit_len);
    if (emitted) {
        free(emitted);
    }

    // Unref the object
    ucl_object_unref(obj);

    // Step 2: Create a parser and add chunk
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser) {
        ucl_parser_add_chunk_full(parser, Data, Size, 0, UCL_DUPLICATE_APPEND, UCL_PARSE_UCL);

        // Retrieve the error if any
        const char *error = ucl_parser_get_error(parser);
        if (error) {
            // Handle error
        }

        // Get the top object from parser
        ucl_object_t *parsed_obj = ucl_parser_get_object(parser);
        if (parsed_obj) {
            // Emit parsed object to string
            unsigned char *parsed_emitted = ucl_object_emit_len(parsed_obj, UCL_EMIT_JSON, &emit_len);
            if (parsed_emitted) {
                free(parsed_emitted);
            }

            // Unref parsed object
            ucl_object_unref(parsed_obj);
        }

        // Free the parser
        ucl_parser_free(parser);
    }

    return 0;
}