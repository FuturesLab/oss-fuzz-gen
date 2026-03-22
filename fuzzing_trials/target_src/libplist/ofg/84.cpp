#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <plist/plist.h>

extern "C" {
    plist_err_t plist_from_json(const char *json, uint32_t length, plist_t *plist);
}

extern "C" int LLVMFuzzerTestOneInput_84(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Ensure the data is null-terminated for JSON parsing
    char *json_data = (char *)malloc(size + 1);
    if (!json_data) {
        return 0;
    }
    memcpy(json_data, data, size);
    json_data[size] = '\0';

    plist_t plist = NULL;
    plist_err_t result = plist_from_json(json_data, (uint32_t)size, &plist);

    // Clean up
    if (plist) {
        plist_free(plist);
    }
    free(json_data);

    return 0;
}