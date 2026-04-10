#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "janet.h"

static JanetAbstractType dummy_type = {
    .name = "dummy",
    .gc = NULL,
    .gcmark = NULL,
    .get = NULL,
    .put = NULL,
    .marshal = NULL,
    .unmarshal = NULL,
    .tostring = NULL,
    .compare = NULL,
    .hash = NULL,
    .next = NULL,
    .call = NULL,
    .length = NULL,
    .bytes = NULL,
    .gcperthread = NULL
};

static void prepare_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_1418(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(size_t)) {
        return 0;
    }

    // Ensure Janet VM is initialized before using Janet functions
    janet_init();

    size_t input_size = *((size_t *)Data);
    const JanetAbstractType *type = &dummy_type;

    // Avoid excessive memory allocation
    if (input_size > 1024 * 1024) {
        input_size = 1024 * 1024;
    }

    // Fuzz janet_abstract
    JanetAbstract abstract_obj = janet_abstract(type, input_size);

    // Fuzz janet_abstract_threaded
    void *threaded_obj = janet_abstract_threaded(type, input_size);

    // Fuzz janet_abstract_begin
    void *begin_obj = janet_abstract_begin(type, input_size);

    // Fuzz janet_register_abstract_type
    janet_register_abstract_type(type);

    // Fuzz janet_get_abstract_type
    Janet key;
    key.u64 = 0; // Initialize with dummy data
    const JanetAbstractType *retrieved_type = janet_get_abstract_type(key);

    // Fuzz janet_abstract_begin_threaded
    void *begin_threaded_obj = janet_abstract_begin_threaded(type, input_size);

    // Prepare dummy file if needed
    prepare_dummy_file(Data, Size);

    // Deinitialize Janet VM after use
    janet_deinit();

    // Cleanup and return
    // Note: Janet's garbage collector will handle deallocation
    return 0;
}