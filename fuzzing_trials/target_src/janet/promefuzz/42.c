// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_init at vm.c:1652:5 in janet.h
// janet_getboolean at janet.c:4523:1 in janet.h
// janet_hash at value.c:309:9 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "janet.h"

static void prepare_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_42(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet) + sizeof(int32_t) + sizeof(int) + sizeof(JanetType)) {
        return 0;
    }

    // Initialize Janet runtime
    janet_init();

    // Prepare dummy file
    prepare_dummy_file(Data, Size);

    // Initialize Janet values
    Janet argv[1];
    memcpy(&argv[0], Data, sizeof(Janet));
    int32_t n = *(int32_t *)(Data + sizeof(Janet));

    // Fuzz janet_getboolean
    if (n >= 0 && n < 1) {
        int boolean_result = janet_getboolean(argv, n);
        (void)boolean_result;
    }

    // Fuzz janet_checktypes
    int typeflags = *(int *)(Data + sizeof(Janet) + sizeof(int32_t));
    int checktypes_result = janet_checktypes(argv[0], typeflags);
    (void)checktypes_result;

    // Fuzz janet_truthy
    int truthy_result = janet_truthy(argv[0]);
    (void)truthy_result;

    // Fuzz janet_checktype
    JanetType janetType = *(JanetType *)(Data + sizeof(Janet) + sizeof(int32_t) + sizeof(int));
    int checktype_result = janet_checktype(argv[0], janetType);
    (void)checktype_result;

    // Fuzz janet_hash
    int32_t hash_result = janet_hash(argv[0]);
    (void)hash_result;

    // Cleanup Janet runtime
    janet_deinit();

    return 0;
}