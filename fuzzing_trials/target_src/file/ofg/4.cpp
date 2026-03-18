#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <magic.h>

extern "C" int LLVMFuzzerTestOneInput_4(const uint8_t *data, size_t size) {
    // Declare and initialize the parameters for magic_setparam
    struct magic_set *ms;
    int param;
    const void *value;

    // Initialize the magic_set
    ms = magic_open(MAGIC_NONE);
    if (ms == NULL) {
        return 0; // If magic_open fails, exit early
    }

    // Load some magic database, using a default one
    if (magic_load(ms, NULL) != 0) {
        magic_close(ms);
        return 0; // If magic_load fails, exit early
    }

    // Choose a valid parameter to set, for example, MAGIC_PARAM_INDIR_MAX
    param = MAGIC_PARAM_INDIR_MAX;

    // Ensure the size is appropriate for the value we want to set
    if (size >= sizeof(int)) {
        // Use the data as the value
        int intValue;
        memcpy(&intValue, data, sizeof(int));
        value = &intValue;

        // Call the function-under-test
        magic_setparam(ms, param, value);
    }

    // Clean up
    magic_close(ms);

    return 0;
}