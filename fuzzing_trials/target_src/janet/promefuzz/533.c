// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_init at vm.c:1652:5 in janet.h
// janet_nanbox_from_bits at janet.c:37716:7 in janet.h
// janet_string at string.c:49:16 in janet.h
// janet_string at string.c:49:16 in janet.h
// janet_get_abstract_type at janet.c:34303:26 in janet.h
// janet_register_abstract_type at janet.c:34292:6 in janet.h
// janet_abstract at janet.c:1343:7 in janet.h
// janet_abstract_threaded at janet.c:1374:7 in janet.h
// janet_abstract_begin at janet.c:1330:7 in janet.h
// janet_abstract_begin_threaded at janet.c:1353:7 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "janet.h"

static const JanetAbstractType dummyType = {
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

int LLVMFuzzerTestOneInput_533(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet)) {
        return 0;
    }

    // Initialize Janet VM
    janet_init();

    // Initialize key with a valid Janet type
    Janet key = janet_wrap_nil();
    
    // Ensure the key is a valid string if possible
    if (Size > sizeof(Janet) && janet_checktype(janet_wrap_string(janet_string(Data, Size)), JANET_STRING)) {
        key = janet_wrap_string(janet_string(Data, Size));
    }

    // Call janet_get_abstract_type
    const JanetAbstractType *abstractType = janet_get_abstract_type(key);
    if (abstractType) {
        // If found, register the abstract type
        janet_register_abstract_type(abstractType);
    }

    // Use the second part of Data to determine size for abstract creation
    size_t size = (Size - sizeof(Janet)) / 2;
    if (size > 0) {
        // Call janet_abstract
        JanetAbstract abstractInstance = janet_abstract(&dummyType, size);

        // Call janet_abstract_threaded
        void *threadedInstance = janet_abstract_threaded(&dummyType, size);

        // Call janet_abstract_begin
        void *beginInstance = janet_abstract_begin(&dummyType, size);

        // Call janet_abstract_begin_threaded
        void *beginThreadedInstance = janet_abstract_begin_threaded(&dummyType, size);
    }

    // Deinitialize Janet VM
    janet_deinit();

    return 0;
}