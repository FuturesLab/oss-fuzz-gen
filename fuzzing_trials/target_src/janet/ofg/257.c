#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <janet.h>

int LLVMFuzzerTestOneInput_257(const uint8_t *data, size_t size) {
    // Ensure there is enough data for the test
    if (size < sizeof(JanetKV) + sizeof(int32_t) + sizeof(Janet)) {
        return 0;
    }

    // Initialize Janet environment
    janet_init();

    // Extract JanetKV pointer from the data
    const JanetKV *dict = (const JanetKV *)data;

    // Extract int32_t from the data
    int32_t index = *(int32_t *)(data + sizeof(JanetKV));

    // Extract Janet key from the data
    Janet key;
    memcpy(&key, data + sizeof(JanetKV) + sizeof(int32_t), sizeof(Janet));

    // Ensure the index is within a reasonable range
    // Assuming a maximum dictionary size for safety; adjust as needed
    int32_t max_index = size / sizeof(JanetKV);
    if (index < 0 || index >= max_index) {
        janet_deinit();
        return 0;
    }

    // Call the function-under-test
    Janet result = janet_dictionary_get(dict, index, key);

    // Clean up Janet environment
    janet_deinit();

    return 0;
}