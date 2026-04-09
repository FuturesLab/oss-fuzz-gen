#include <stdint.h>
#include <stddef.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_119(const uint8_t *data, size_t size) {
    // Initialize Janet
    janet_init();

    // Create a JanetTable
    JanetTable *table = janet_table(10);

    // Ensure there is at least some data to work with
    if (size < sizeof(Janet)) {
        janet_deinit();
        return 0;
    }

    // Use the first part of the data as a key
    Janet key = janet_wrap_integer(data[0]);

    // Insert a dummy value into the table with the key
    Janet value = janet_wrap_integer(42);
    janet_table_put(table, key, value);

    // Call the function-under-test
    Janet result = janet_table_rawget(table, key);

    // Optionally, perform some checks or operations with 'result'
    // ...

    // Cleanup
    janet_deinit();

    return 0;
}