// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_parser_new at ucl_parser.c:2804:1 in ucl.h
// ucl_parser_add_file at ucl_util.c:2054:6 in ucl.h
// ucl_parser_get_comments at ucl_util.c:3915:1 in ucl.h
// ucl_parser_get_object at ucl_util.c:590:1 in ucl.h
// ucl_object_emit at ucl_emitter.c:661:1 in ucl.h
// ucl_object_emit at ucl_emitter.c:661:1 in ucl.h
// ucl_object_emit at ucl_emitter.c:661:1 in ucl.h
// ucl_object_emit at ucl_emitter.c:661:1 in ucl.h
// ucl_object_emit_memory_funcs at ucl_emitter_utils.c:378:1 in ucl.h
// ucl_object_emit_full at ucl_emitter.c:694:6 in ucl.h
// ucl_object_unref at ucl_util.c:3697:6 in ucl.h
// ucl_parser_free at ucl_util.c:599:6 in ucl.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ucl.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static void write_to_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_8(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Initialize parser and parse input data
    struct ucl_parser *parser = ucl_parser_new(0);
    if (!parser) return 0;

    // Write data to dummy file
    write_to_dummy_file(Data, Size);

    // Load data into parser
    ucl_parser_add_file(parser, "./dummy_file");

    // Get comments from parser
    const ucl_object_t *comments = ucl_parser_get_comments(parser);

    // Get the top object
    ucl_object_t *top = ucl_parser_get_object(parser);

    if (top) {
        // Emit object in different formats
        unsigned char *emitted = ucl_object_emit(top, UCL_EMIT_JSON);
        if (emitted) {
            free(emitted);
        }

        emitted = ucl_object_emit(top, UCL_EMIT_CONFIG);
        if (emitted) {
            free(emitted);
        }

        emitted = ucl_object_emit(top, UCL_EMIT_YAML);
        if (emitted) {
            free(emitted);
        }

        emitted = ucl_object_emit(top, UCL_EMIT_MSGPACK);
        if (emitted) {
            free(emitted);
        }

        // Emit object using memory functions
        void *pmem = NULL;
        struct ucl_emitter_functions *emitter_funcs = ucl_object_emit_memory_funcs(&pmem);
        if (emitter_funcs) {
            bool success = ucl_object_emit_full(top, UCL_EMIT_JSON, emitter_funcs, comments);
            if (success && pmem) {
                free(pmem);
            }
            if (emitter_funcs->ucl_emitter_free_func) {
                emitter_funcs->ucl_emitter_free_func(emitter_funcs->ud);
            }
            free(emitter_funcs);
        }

        ucl_object_unref(top);
    }

    ucl_parser_free(parser);
    return 0;
}