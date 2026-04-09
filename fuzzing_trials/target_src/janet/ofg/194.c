#include <stdint.h>
#include <stddef.h>
#include <janet.h>

// Function to safely extract an integer from the data
static int32_t extract_int32(const uint8_t *data, size_t size, size_t offset) {
    if (offset + sizeof(int32_t) <= size) {
        return *(const int32_t *)(data + offset);
    }
    return 0; // Default value if out of bounds
}

// Function to safely extract a JanetAbstractType from the data
static const JanetAbstractType *extract_abstract_type(const uint8_t *data, size_t size, size_t offset) {
    if (offset + sizeof(JanetAbstractType) <= size) {
        return (const JanetAbstractType *)(data + offset);
    }
    return NULL; // Default value if out of bounds
}

int LLVMFuzzerTestOneInput_194(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to extract necessary data
    if (size < sizeof(Janet) + sizeof(int32_t) + sizeof(JanetAbstractType)) {
        return 0;
    }

    // Initialize variables
    const Janet *janet_ptr = (const Janet *)data;
    int32_t index = extract_int32(data, size, sizeof(Janet));
    const JanetAbstractType *abstract_type = extract_abstract_type(data, size, sizeof(Janet) + sizeof(int32_t));

    // Validate the Janet pointer
    if (!janet_checktype(*janet_ptr, JANET_ABSTRACT)) {
        return 0;
    }

    // Ensure abstract_type is not NULL
    if (abstract_type == NULL) {
        return 0;
    }

    // Call the function-under-test
    void *result = janet_getabstract(janet_ptr, index, abstract_type);

    // Prevent unused variable warning
    (void)result;

    return 0;
}