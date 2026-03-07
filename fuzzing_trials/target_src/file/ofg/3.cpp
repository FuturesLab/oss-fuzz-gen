#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <magic.h>

extern "C" int LLVMFuzzerTestOneInput_3(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    struct magic_set *ms;
    int param_type;
    const void *param_value;

    // Initialize the magic_set structure
    ms = magic_open(MAGIC_NONE);
    if (ms == NULL) {
        return 0;
    }

    // Load the default magic database
    if (magic_load(ms, NULL) != 0) {
        magic_close(ms);
        return 0;
    }

    // Ensure the data size is sufficient for fuzzing
    if (size < sizeof(int) + 1) {
        magic_close(ms);
        return 0;
    }

    // Extract the parameter type from the input data
    memcpy(&param_type, data, sizeof(int));
    data += sizeof(int);
    size -= sizeof(int);

    // Use the remaining data as the parameter value
    param_value = static_cast<const void *>(data);

    // Call the function-under-test and check for errors
    // We will attempt to use a valid param_type for better coverage
    if (param_type < 0 || param_type > MAGIC_PARAM_INDIR_MAX) {
        param_type = MAGIC_PARAM_INDIR_MAX; // Use a valid parameter type
    }

    if (magic_setparam(ms, param_type, param_value) != 0) {
        // Handle error if needed, e.g., logging, but for fuzzing we just continue
    }

    // Optionally, perform additional operations to increase coverage
    // For example, we can use magic_file or magic_buffer with the remaining data
    if (size > 0) {
        magic_buffer(ms, data, size);
    }

    // Clean up
    magic_close(ms);

    return 0;
}