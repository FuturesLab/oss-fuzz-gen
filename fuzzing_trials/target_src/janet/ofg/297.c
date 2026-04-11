#include <stdint.h>
#include <janet.h>

extern JanetTable * janet_env_lookup(JanetTable *);

int LLVMFuzzerTestOneInput_297(const uint8_t *data, size_t size) {
    // Initialize the Janet runtime
    janet_init();

    // Create a new JanetTable
    JanetTable *table = janet_table(10);

    // Populate the table with some dummy data from the input
    for (size_t i = 0; i < size; i++) {
        Janet key = janet_wrap_integer(i);
        Janet value = janet_wrap_integer(data[i]);
        janet_table_put(table, key, value);
    }

    // Call the function-under-test
    JanetTable *result = janet_env_lookup(table);

    // Clean up the Janet runtime
    janet_deinit();

    return 0;
}