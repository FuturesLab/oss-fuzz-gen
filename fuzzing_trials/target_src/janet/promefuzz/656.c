// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_init at vm.c:1652:5 in janet.h
// janet_abstract at janet.c:1343:7 in janet.h
// janet_abstract_threaded at janet.c:1374:7 in janet.h
// janet_abstract_begin at janet.c:1330:7 in janet.h
// janet_register_abstract_type at janet.c:34292:6 in janet.h
// janet_get_abstract_type at janet.c:34303:26 in janet.h
// janet_abstract_begin_threaded at janet.c:1353:7 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "janet.h"

static JanetAbstractType sampleType = {
    .name = "sample",
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

int LLVMFuzzerTestOneInput_656(const uint8_t *Data, size_t Size) {
    // Ensure that the Janet environment is initialized
    janet_init();

    // Fuzz janet_abstract
    if (Size > 0) {
        size_t abstract_size = Data[0] % 256;  // Limit size for safe allocation
        JanetAbstract abstract_instance = janet_abstract(&sampleType, abstract_size);
        (void)abstract_instance; // Suppress unused variable warning
    }

    // Fuzz janet_abstract_threaded
    if (Size > 1) {
        size_t threaded_size = Data[1] % 256;  // Limit size for safe allocation
        void *threaded_instance = janet_abstract_threaded(&sampleType, threaded_size);
        (void)threaded_instance; // Suppress unused variable warning
    }

    // Fuzz janet_abstract_begin
    if (Size > 2) {
        size_t begin_size = Data[2] % 256;  // Limit size for safe allocation
        void *begin_instance = janet_abstract_begin(&sampleType, begin_size);
        (void)begin_instance; // Suppress unused variable warning
    }

    // Fuzz janet_register_abstract_type
    if (sampleType.name != NULL) {
        janet_register_abstract_type(&sampleType);
    }

    // Fuzz janet_get_abstract_type
    if (Size >= sizeof(Janet)) {
        Janet key;
        memcpy(&key, Data, sizeof(Janet));
        // Ensure key is valid and within expected range for janet_get_abstract_type
        if (key.pointer != NULL && (key.u64 & 0xFFFFFFFF) == key.u64) {
            const JanetAbstractType *retrieved_type = janet_get_abstract_type(key);
            (void)retrieved_type; // Suppress unused variable warning
        }
    }

    // Fuzz janet_abstract_begin_threaded
    if (Size > 3) {
        size_t begin_threaded_size = Data[3] % 256;  // Limit size for safe allocation
        void *begin_threaded_instance = janet_abstract_begin_threaded(&sampleType, begin_threaded_size);
        (void)begin_threaded_instance; // Suppress unused variable warning
    }

    // Cleanup Janet environment
    janet_deinit();

    return 0;
}