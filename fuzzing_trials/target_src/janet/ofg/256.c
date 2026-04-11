#include <stdint.h>
#include <stddef.h>
#include <janet.h>
#include <string.h>

int LLVMFuzzerTestOneInput_256(const uint8_t *data, size_t size) {
    // Ensure there is enough data to work with
    if (size < sizeof(JanetKV) + sizeof(int32_t) + sizeof(Janet)) {
        return 0;
    }

    // Initialize Janet if not already done
    janet_init();

    // Prepare the JanetKV pointer
    JanetKV kv;
    memcpy(&kv, data, sizeof(JanetKV));

    // Prepare the index
    int32_t index;
    memcpy(&index, data + sizeof(JanetKV), sizeof(int32_t));

    // Prepare the Janet key
    Janet key;
    memcpy(&key, data + sizeof(JanetKV) + sizeof(int32_t), sizeof(Janet));

    // Ensure the key is a valid Janet type
    if (!janet_checktype(key, JANET_NIL) && !janet_checktype(key, JANET_STRING) && 
        !janet_checktype(key, JANET_SYMBOL) && !janet_checktype(key, JANET_KEYWORD)) {
        janet_deinit();
        return 0;
    }

    // Call the function-under-test
    Janet result = janet_dictionary_get(&kv, index, key);

    // Cleanup Janet
    janet_deinit();

    return 0;
}