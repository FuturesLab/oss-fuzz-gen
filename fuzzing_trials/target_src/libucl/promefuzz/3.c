// This fuzz driver is generated for library libucl, aiming to fuzz the following functions:
// ucl_parser_new at ucl_parser.c:2804:1 in ucl.h
// ucl_parser_add_chunk at ucl_parser.c:3109:6 in ucl.h
// ucl_object_new at ucl_util.c:2980:1 in ucl.h
// ucl_parser_get_comments at ucl_util.c:3915:1 in ucl.h
// ucl_parser_free at ucl_util.c:599:6 in ucl.h
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

static struct ucl_parser* create_parser(const uint8_t *data, size_t size) {
    struct ucl_parser *parser = ucl_parser_new(0);
    if (parser != NULL) {
        ucl_parser_add_chunk(parser, data, size);
    }
    return parser;
}

static ucl_object_t* create_ucl_object(const uint8_t *data, size_t size) {
    ucl_object_t *obj = ucl_object_new();
    if (obj != NULL) {
        obj->type = UCL_STRING;
        obj->value.sv = (const char *)data;
        obj->len = size;
    }
    return obj;
}

int LLVMFuzzerTestOneInput_3(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    struct ucl_parser *parser = create_parser(Data, Size);
    if (parser == NULL) return 0;

    const ucl_object_t *comments = ucl_parser_get_comments(parser);

    ucl_object_t *obj = create_ucl_object(Data, Size);
    if (obj == NULL) {
        ucl_parser_free(parser);
        return 0;
    }

    unsigned char *result;
    result = ucl_object_emit(obj, UCL_EMIT_JSON);
    if (result != NULL) {
        free(result);
    }

    result = ucl_object_emit(obj, UCL_EMIT_CONFIG);
    if (result != NULL) {
        free(result);
    }

    result = ucl_object_emit(obj, UCL_EMIT_YAML);
    if (result != NULL) {
        free(result);
    }

    result = ucl_object_emit(obj, UCL_EMIT_MSGPACK);
    if (result != NULL) {
        free(result);
    }

    void *mem = NULL;
    struct ucl_emitter_functions *funcs = ucl_object_emit_memory_funcs(&mem);
    if (funcs != NULL) {
        bool success = ucl_object_emit_full(obj, UCL_EMIT_JSON, funcs, comments);
        if (success && mem != NULL) {
            free(mem);
        }
        free(funcs);
    }

    ucl_object_unref(obj);
    ucl_parser_free(parser);
    return 0;
}