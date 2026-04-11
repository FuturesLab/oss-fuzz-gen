// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_init at vm.c:1652:5 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
// janet_register_abstract_type at janet.c:34292:6 in janet.h
// janet_abstract_begin_threaded at janet.c:1353:7 in janet.h
// janet_abstract_end_threaded at janet.c:1369:7 in janet.h
// janet_abstract_begin at janet.c:1330:7 in janet.h
// janet_abstract_incref at janet.c:1488:9 in janet.h
// janet_abstract_decref at janet.c:1492:9 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
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

int LLVMFuzzerTestOneInput_681(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(size_t)) {
        return 0;
    }

    // Properly initialize Janet runtime
    janet_init();

    // Use the first part of Data to determine the size for abstract allocation
    size_t abstract_size = *((size_t *)Data);
    Data += sizeof(size_t);
    Size -= sizeof(size_t);

    // Ensure abstract_size is within a reasonable range to prevent out-of-memory errors
    if (abstract_size > 1024 * 1024) { // Limit size to 1MB for safety
        janet_deinit();
        return 0;
    }

    // Register a dummy abstract type
    janet_register_abstract_type(&dummy_type);

    // Begin and end a threaded abstract object
    void *abstract_object = janet_abstract_begin_threaded(&dummy_type, abstract_size);
    if (abstract_object) {
        janet_abstract_end_threaded(abstract_object);
    }

    // Begin a non-threaded abstract object
    void *abstract_object_non_threaded = janet_abstract_begin(&dummy_type, abstract_size);

    // Increment and decrement reference count
    if (abstract_object_non_threaded) {
        int32_t ref_count = janet_abstract_incref(abstract_object_non_threaded);
        ref_count = janet_abstract_decref(abstract_object_non_threaded);
    }

    // Properly deinitialize Janet runtime
    janet_deinit();

    return 0;
}