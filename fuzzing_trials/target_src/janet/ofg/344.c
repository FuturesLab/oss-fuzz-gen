#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <janet.h>

// Function to safely create a Janet value from raw data
Janet safe_create_janet_value(const uint8_t **data, size_t *size) {
    if (*size < sizeof(Janet)) {
        return janet_wrap_nil(); // Return a nil value if not enough data
    }
    Janet value;
    memcpy(&value, *data, sizeof(Janet));
    *data += sizeof(Janet);
    *size -= sizeof(Janet);
    return value;
}

int LLVMFuzzerTestOneInput_344(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract two Janet values and an int32_t index
    if (size < sizeof(Janet) * 2 + sizeof(int32_t)) {
        return 0;
    }

    // Extract the first Janet value from the data
    Janet value1 = safe_create_janet_value(&data, &size);

    // Extract the index from the data
    if (size < sizeof(int32_t)) {
        return 0; // Not enough data for the index
    }
    int32_t index;
    memcpy(&index, data, sizeof(int32_t));
    data += sizeof(int32_t);
    size -= sizeof(int32_t);

    // Extract the second Janet value from the data
    Janet value2 = safe_create_janet_value(&data, &size);

    // Check if value1 is a valid Janet array before calling janet_putindex
    if (janet_checktype(value1, JANET_ARRAY)) {
        // Call the function-under-test
        janet_putindex(value1, index, value2);
    }

    return 0;
}