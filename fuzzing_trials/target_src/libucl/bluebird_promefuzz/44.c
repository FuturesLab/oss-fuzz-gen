#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "stdio.h"
#include "ucl.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "stdio.h"
#include <string.h>

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *f = fopen("./dummy_file", "wb");
    if (f) {
        fwrite(Data, 1, Size, f);
        fclose(f);
    }
}

int LLVMFuzzerTestOneInput_44(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Step 1: Create a new UCL object
    ucl_object_t *top_obj = ucl_object_typed_new(UCL_OBJECT);
    if (top_obj == NULL) {
        return 0;
    }

    // Step 2: Insert keys into the UCL object
    ucl_object_t *int_obj = ucl_object_typed_new(UCL_INT);
    ucl_object_t *str_obj = ucl_object_typed_new(UCL_STRING);
    ucl_object_t *bool_obj = ucl_object_typed_new(UCL_BOOLEAN);
    ucl_object_t *null_obj = ucl_object_typed_new(UCL_NULL);

    if (int_obj && str_obj && bool_obj && null_obj) {
        ucl_object_insert_key(top_obj, int_obj, "int_key", 7, true);
        ucl_object_insert_key(top_obj, str_obj, "str_key", 7, true);
        ucl_object_insert_key(top_obj, bool_obj, "bool_key", 8, true);

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from ucl_object_insert_key to ucl_object_set_priority
        unsigned int ret_ucl_parser_get_linenum_qapcc = ucl_parser_get_linenum(NULL);
        if (ret_ucl_parser_get_linenum_qapcc < 0){
        	return 0;
        }

        ucl_object_set_priority(int_obj, ret_ucl_parser_get_linenum_qapcc);

        // End mutation: Producer.APPEND_MUTATOR

        ucl_object_insert_key(top_obj, null_obj, "null_key", 8, true);
    } else {
        if (int_obj) {
                ucl_object_unref(int_obj);
        }
        if (str_obj) {
                ucl_object_unref(str_obj);
        }
        if (bool_obj) {
                ucl_object_unref(bool_obj);
        }
        if (null_obj) {
                ucl_object_unref(null_obj);
        }
        ucl_object_unref(top_obj);
        return 0;
    }

    // Step 3: Emit the object
    size_t emitted_len = 0;
    unsigned char *emitted_str = ucl_object_emit_len(top_obj, UCL_EMIT_JSON, &emitted_len);
    if (emitted_str) {
        // Use the emitted string in some way if needed
        free(emitted_str);
    }

    // Step 4: Create a new UCL parser
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser == NULL) {
        ucl_object_unref(top_obj);
        return 0;
    }

    // Step 5: Add chunk to parser
    if (!ucl_parser_add_chunk_full(parser, Data, Size, 0, UCL_DUPLICATE_APPEND, UCL_PARSE_UCL)) {
        const char *error = ucl_parser_get_error(parser);
        if (error) {
            // Handle the error if needed
        }
    }

    // Step 6: Retrieve the object from parser
    ucl_object_t *parsed_obj = ucl_parser_get_object(parser);
    if (parsed_obj) {
        size_t parsed_emitted_len = 0;
        unsigned char *parsed_emitted_str = ucl_object_emit_len(parsed_obj, UCL_EMIT_JSON, &parsed_emitted_len);
        if (parsed_emitted_str) {
            // Use the emitted string in some way if needed
            free(parsed_emitted_str);
        }
        ucl_object_unref(parsed_obj);
    }

    // Step 7: Clean up
    ucl_parser_free(parser);
    ucl_object_unref(top_obj);

    return 0;
}