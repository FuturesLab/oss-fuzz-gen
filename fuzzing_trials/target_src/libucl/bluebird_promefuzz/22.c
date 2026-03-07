#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "stdio.h"
#include <stdlib.h>
#include <stdint.h>
#include "ucl.h"

static void initialize_parser(struct ucl_parser **parser) {
    *parser = ucl_parser_new(UCL_PARSER_NO_FILEVARS);
    if (*parser) {
        ucl_parser_add_string(*parser, "key: value\n", 11);
    }
}

static void cleanup_parser(struct ucl_parser *parser) {
    if (parser) {
        ucl_parser_free(parser);
    }
}

int LLVMFuzzerTestOneInput_22(const uint8_t *Data, size_t Size) {
    struct ucl_parser *parser = NULL;
    initialize_parser(&parser);

    if (parser) {
        // Fuzz ucl_parser_get_linenum
        unsigned line_num = ucl_parser_get_linenum(parser);
        
        // Fuzz ucl_parser_get_comments
        const ucl_object_t *comments = ucl_parser_get_comments(parser);
        
        // Fuzz ucl_parser_get_current_stack_object
        unsigned int depth = (Size > 0) ? Data[0] : 0;
        ucl_object_t *stack_object = ucl_parser_get_current_stack_object(parser, depth);
        
        // Fuzz ucl_parser_get_object
        ucl_object_t *top_object = ucl_parser_get_object(parser);
        
        // Fuzz ucl_parser_clear_error
        ucl_parser_clear_error(parser);
        
        // Fuzz ucl_parser_get_column
        unsigned column_num = ucl_parser_get_column(parser);

        // Clean up references
        if (stack_object) {
            ucl_object_unref(stack_object);
        }
        if (top_object) {
            ucl_object_unref(top_object);
        }
    }

    cleanup_parser(parser);
    return 0;
}