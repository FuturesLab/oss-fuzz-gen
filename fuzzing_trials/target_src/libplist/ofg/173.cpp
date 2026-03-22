#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <plist/plist.h>

extern "C" {
    plist_err_t plist_from_bin(const char *, uint32_t, plist_t *);
}

extern "C" int LLVMFuzzerTestOneInput_173(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Ensure the input data is null-terminated
    char *bin_data = (char *)malloc(size + 1);
    if (!bin_data) {
        return 0;
    }
    memcpy(bin_data, data, size);
    bin_data[size] = '\0';

    plist_t plist = NULL;

    // Call the function-under-test
    plist_err_t result = plist_from_bin(bin_data, (uint32_t)size, &plist);

    // Clean up
    if (plist) {
        plist_free(plist);
    }
    free(bin_data);

    return 0;
}