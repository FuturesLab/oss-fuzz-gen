#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_5(const uint8_t *data, size_t size) {
    // Initialize a ucl_object_t object
    ucl_object_t *ucl_obj = ucl_object_fromstring("test");

    // Initialize the ucl_emitter variable
    ucl_emitter_t emitter = UCL_EMIT_JSON;

    // Initialize a size_t variable
    size_t len = 0;

    // Call the function-under-test
    unsigned char *result = ucl_object_emit_len(ucl_obj, emitter, &len);

    // Free the result if it's not NULL
    if (result != NULL) {
        free(result);
    }

    // Clean up the ucl_object_t object
    ucl_object_unref(ucl_obj);

    return 0;
}