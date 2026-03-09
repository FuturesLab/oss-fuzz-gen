#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_67(const uint8_t *data, size_t size) {
    if (size < 1) return 0;

    // Initialize ucl_object_t pointers
    ucl_object_t *obj1 = ucl_object_fromstring("test_object_1");
    ucl_object_t *obj2 = ucl_object_fromstring("test_object_2");

    // Initialize ucl_emitter
    enum ucl_emitter emitter_type = UCL_EMIT_JSON;

    // Initialize ucl_emitter_functions
    struct ucl_emitter_functions emitter_functions;
    emitter_functions.ud = NULL;
    emitter_functions.ucl_emitter_append_character = NULL;
    emitter_functions.ucl_emitter_append_len = NULL;
    emitter_functions.ucl_emitter_free_func = NULL;

    // Call the function-under-test
    bool result = ucl_object_emit_full(obj1, emitter_type, &emitter_functions, obj2);

    // Clean up
    ucl_object_unref(obj1);
    ucl_object_unref(obj2);

    return 0;
}