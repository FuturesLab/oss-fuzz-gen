// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_init at vm.c:1652:5 in janet.h
// janet_var_sm at janet.c:34110:6 in janet.h
// janet_def_sm at janet.c:34099:6 in janet.h
// janet_cfuns_ext at janet.c:34249:6 in janet.h
// janet_cfuns_ext_prefix at janet.c:34272:6 in janet.h
// janet_core_env at janet.c:7992:13 in janet.h
// janet_env_lookup_into at marsh.c:104:6 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
// janet_table at janet.c:33121:13 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <janet.h>

static JanetTable *initialize_table() {
    JanetTable *table = janet_table(0);
    return table;
}

static Janet create_janet_value(const uint8_t *data, size_t size) {
    Janet value;
    if (size >= sizeof(uint64_t)) {
        value.u64 = *((uint64_t *)data);
    } else {
        value.u64 = 0;
    }
    return value;
}

int LLVMFuzzerTestOneInput_216(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize Janet VM
    janet_init();

    JanetTable *env = initialize_table();
    Janet val = create_janet_value(Data, Size);

    const char *name = "fuzz_var";
    const char *documentation = "Fuzz documentation";
    const char *source_file = "./dummy_file";
    int32_t source_line = 42;

    // Fuzz janet_var_sm
    janet_var_sm(env, name, val, documentation, source_file, source_line);

    // Fuzz janet_def_sm
    janet_def_sm(env, name, val, documentation, source_file, source_line);

    // Prepare JanetRegExt for janet_cfuns_ext and janet_cfuns_ext_prefix
    JanetRegExt cfuns[] = {
        { "fuzz_cfun", NULL, "Fuzz cfun documentation", source_file, source_line },
        { NULL, NULL, NULL, NULL, 0 }
    };

    // Fuzz janet_cfuns_ext
    janet_cfuns_ext(env, "fuzz_prefix", cfuns);

    // Fuzz janet_cfuns_ext_prefix
    janet_cfuns_ext_prefix(env, "fuzz_prefix", cfuns);

    // Fuzz janet_core_env
    JanetTable *core_env = janet_core_env(NULL);

    // Fuzz janet_env_lookup_into
    janet_env_lookup_into(env, core_env, "prefix_", 1);

    // Clean up
    // Do not manually deinitialize tables returned by janet_core_env or janet_table
    // Janet handles the cleanup of its own memory
    janet_deinit();

    return 0;
}