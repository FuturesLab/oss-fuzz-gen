#include <stdint.h>
#include <stddef.h>

extern "C" {
    // Include the necessary header for libplist_version
    #include <plist/plist.h>
}

extern "C" int LLVMFuzzerTestOneInput_127(const uint8_t *data, size_t size) {
    // Since libplist_version does not take any input, we can call it directly
    const char *version = libplist_version();
    
    // Optionally, you can print the version to ensure it's being called, but in fuzzing, this is not necessary
    // printf("libplist version: %s\n", version);

    // No further processing needed for this function
    return 0;
}