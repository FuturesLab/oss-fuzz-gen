// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_table at janet.c:33121:13 in janet.h
// janet_init at vm.c:1652:5 in janet.h
// janet_table at janet.c:33121:13 in janet.h
// janet_var_sm at janet.c:34110:6 in janet.h
// janet_var at janet.c:34118:6 in janet.h
// janet_dobytes at run.c:31:5 in janet.h
// janet_dostring at run.c:139:5 in janet.h
// janet_def_sm at janet.c:34099:6 in janet.h
// janet_table at janet.c:33121:13 in janet.h
// janet_env_lookup_into at marsh.c:104:6 in janet.h
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

// Helper function to initialize a JanetTable
static void initialize_janet_table(JanetTable *table) {
    // Proper initialization using Janet's internal functions
    *table = *janet_table(0);
}

// Helper function to create a dummy Janet value
static Janet create_dummy_janet_value() {
    Janet val;
    val.u64 = 0;
    return val;
}

// Helper function to create a null-terminated string from input data
static const char *create_string_from_input(const uint8_t *Data, size_t Size) {
    static char buffer[256];
    size_t copy_size = Size < 255 ? Size : 255;
    memcpy(buffer, Data, copy_size);
    buffer[copy_size] = '\0';
    return buffer;
}

int LLVMFuzzerTestOneInput_789(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize Janet VM
    janet_init();

    // Initialize Janet environment
    JanetTable *env = janet_table(0);

    // Create dummy Janet value
    Janet dummy_val = create_dummy_janet_value();

    // Create strings from input
    const char *name = create_string_from_input(Data, Size);
    const char *doc = "Documentation";
    const char *source_file = "./dummy_file";

    // Call janet_var_sm
    janet_var_sm(env, name, dummy_val, doc, source_file, 1);

    // Call janet_var
    janet_var(env, name, dummy_val, doc);

    // Prepare dummy byte array for janet_dobytes
    Janet out;
    janet_dobytes(env, Data, (int32_t)Size, source_file, &out);

    // Call janet_dostring
    janet_dostring(env, name, source_file, &out);

    // Call janet_def_sm
    janet_def_sm(env, name, dummy_val, doc, source_file, 1);

    // Initialize another environment for janet_env_lookup_into
    JanetTable *renv = janet_table(0);
    janet_env_lookup_into(renv, env, "prefix_", 1);

    // Cleanup Janet VM
    janet_deinit();

    return 0;
}