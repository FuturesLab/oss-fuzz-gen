#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "janet.h"

// Dummy C function for registration
static Janet cfun_dummy(int32_t argc, Janet *argv) {
    return janet_wrap_nil();
}

// Dummy JanetReg array
static JanetReg dummy_cfuns[] = {
    {"dummy", cfun_dummy, "A dummy function"},
    {NULL, NULL, NULL} // Terminator
};

// Dummy JanetRegExt array
static JanetRegExt dummy_cfuns_ext[] = {
    {"dummy_ext", cfun_dummy, "A dummy ext function"},
    {NULL, NULL, NULL} // Terminator
};

// Write dummy data to a file
static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_496(const uint8_t *Data, size_t Size) {
    // Initialize Janet environment
    janet_init();

    // Prepare a dummy JanetTable
    JanetTable *env = janet_table(10);

    // Fuzz janet_cfuns
    janet_cfuns(env, "prefix_", dummy_cfuns);

    // Fuzz janet_env_lookup
    JanetTable *new_env = janet_env_lookup(env);

    // Fuzz janet_core_env
    JanetTable *core_env = janet_core_env(env);

    // Fuzz janet_cfuns_ext
    janet_cfuns_ext(env, "ext_prefix_", dummy_cfuns_ext);

    // Fuzz janet_core_lookup_table
    JanetTable *lookup_table = janet_core_lookup_table(env);

    // Fuzz janet_def
    Janet val = janet_wrap_integer(42);
    janet_def(env, "test_var", val, "A test variable");

    // Write dummy data to a file
    write_dummy_file(Data, Size);

    // Clean up the environments
    // Do not manually deinit tables returned by janet_env_lookup, janet_core_env, or janet_core_lookup_table
    // Remove janet_table_deinit call to avoid double free
    // janet_table_deinit(env);
    janet_deinit();

    return 0;
}